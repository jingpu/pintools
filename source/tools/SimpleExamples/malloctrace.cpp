/*BEGIN_LEGAL 
-Intel Open Source License 
-
-Copyright (c) 2002-2012 Intel Corporation. All rights reserved.
- 
-Redistribution and use in source and binary forms, with or without
-modification, are permitted provided that the following conditions are
-met:
-
-Redistributions of source code must retain the above copyright notice,
-this list of conditions and the following disclaimer.  Redistributions
-in binary form must reproduce the above copyright notice, this list of
-conditions and the following disclaimer in the documentation and/or
-other materials provided with the distribution.  Neither the name of
-the Intel Corporation nor the names of its contributors may be used to
-endorse or promote products derived from this software without
-specific prior written permission.
- 
-THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
-``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
-LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
-A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
-ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
-SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
-LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
-DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
-THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
-(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
-OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-END_LEGAL */
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
