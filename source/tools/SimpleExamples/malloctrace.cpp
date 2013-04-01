/*BEGIN_LEGAL 
The MIT License (MIT)
Copyright (c) 2012 Jing Pu

Permission is hereby granted, free of charge, to any person obtaining a 
copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the 
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
OTHER DEALINGS IN THE SOFTWARE. */
/* ===================================================================== */
/*
  @ORIGINAL_AUTHOR: Jing Pu
*/

/* ===================================================================== */
/*! @file
 *  This file contains an ISA-portable PIN tool for tracing calls to malloc
 */

#include "pin.H"
#include <iostream>
#include <fstream>

/* ===================================================================== */
/* Names of malloc and free */
/* ===================================================================== */
#if defined(TARGET_MAC)
#define MALLOC "_malloc"
#define FREE "_free"
#else
#define MALLOC "malloc"
#define FREE "free"
#endif

/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */

std::ofstream TraceFile;

/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "malloctrace.out", "specify trace file name");

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr <<
        "This tool produces a trace of calls to malloc.\n"
        "\n";

    cerr << KNOB_BASE::StringKnobSummary();

    cerr << endl;

    return -1;
}

/* ===================================================================== */

VOID FreeBefore(ADDRINT retIp, ADDRINT address)
{
  TraceFile << "(tool) call to free ("<< reinterpret_cast<void*>(address)<<")"<< endl;
  //	    <<")    will return to "<<reinterpret_cast<void*>(retIp)<< endl;
}
/* ===================================================================== */

void * MallocWrapper( CONTEXT * ctxt, AFUNPTR pf_malloc, size_t size)
{  // Simulate out-of-memory every so often
  void * res;
  PIN_CallApplicationFunction(ctxt, PIN_ThreadId(),
			      CALLINGSTD_DEFAULT,  pf_malloc,
			      PIN_PARG(void *),  &res, PIN_PARG(size_t), size, PIN_PARG_END());
  
  TraceFile << "(tool) call to malloc for "<<dec<<size<<" bytes"
	    << "    returns "<<res<< endl;
  return res;  
}

/* ===================================================================== */

VOID Image(IMG img, VOID *v)
{
    // Instrument the malloc() and free() functions.  Print the input argument
    // of each malloc() or free(), and the return value of malloc().
    
    RTN mallocRtn = RTN_FindByName(img, "malloc");  //  Find the malloc() function.
    if (RTN_Valid(mallocRtn))
      {
        PROTO protoMalloc = PROTO_Allocate( PIN_PARG(void *), CALLINGSTD_DEFAULT,
					    "malloc", PIN_PARG(size_t), PIN_PARG_END() );

	RTN_ReplaceSignature(mallocRtn, AFUNPTR(MallocWrapper),
			     IARG_PROTOTYPE, protoMalloc,
			     IARG_CONST_CONTEXT,
			     IARG_ORIG_FUNCPTR,
			     IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
			     IARG_END);
      }

    RTN freeRtn = RTN_FindByName(img, "free"); // Find the free() function.
    if (RTN_Valid(freeRtn))
    {
        RTN_Open(freeRtn);
        // Instrument free() to print the input argument value.
        RTN_InsertCall(freeRtn, IPOINT_BEFORE, (AFUNPTR)FreeBefore,
		       IARG_RETURN_IP, IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
		       IARG_END);
        RTN_Close(freeRtn);
    }

}

/* ===================================================================== */

VOID Fini(INT32 code, VOID *v)
{
    TraceFile.close();
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char *argv[])
{
    PIN_InitSymbols();

    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }
    

    TraceFile.open(KnobOutputFile.Value().c_str());

    TraceFile << hex;
    TraceFile.setf(ios::showbase);

    cout << hex;
    cout.setf(ios::showbase);
    
    IMG_AddInstrumentFunction(Image, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
