/*BEGIN_LEGAL 
Intel Open Source License 

Copyright (c) 2002-2012 Intel Corporation. All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.  Neither the name of
the Intel Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without
specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */

#include "pin.H"
#include <iostream>
#include <fstream>

// void *memcpy(void *dest, const void *src, size_t n);
/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */

std::ofstream TraceFile;

static ADDRINT actual_memcpy_add = 0;

/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "ifuncmemcpytrace.out", "specify trace file name");

/* ===================================================================== */


/* ===================================================================== */
/* Analysis routines                                                     */
/* ===================================================================== */
 
VOID MemcpyBefore(CHAR * name, ADDRINT dst, ADDRINT src, ADDRINT size)
{
    TraceFile << name << "(" << dst << "," << src << "," << size << ")" << endl;
}

VOID IfuncMemcpyBefore(CHAR * name)
{
    TraceFile << name << endl;
}

// Capture the return address of the ifunc which is the address of the actual memcpy
VOID * IfuncMemcpyWrapper( CONTEXT * context, AFUNPTR orgFuncptr)
{
    VOID * ret;

    PIN_CallApplicationFunction( context, PIN_ThreadId(),
                                 CALLINGSTD_DEFAULT, orgFuncptr,
                                 PIN_PARG(void *), &ret,
                                 PIN_PARG_END() );

    actual_memcpy_add=(ADDRINT)ret;
    cout << "ifunc_memcpy(" << ") returns " << hex << ret << endl;
    return ret;
}

/* ===================================================================== */
/* Instrumentation routines                                              */
/* ===================================================================== */

VOID Trace(TRACE trace, VOID *v)
{
    // If current trace is the actual memcpy address insert memcpy instrumentation func
    if (TRACE_Address(trace) == actual_memcpy_add)
    {
        TRACE_InsertCall(trace, IPOINT_BEFORE, (AFUNPTR)MemcpyBefore,
                           IARG_ADDRINT, "memcpy (ifunc)",
                           IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                           IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                           IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                           IARG_END);
    }

}
   
VOID Image(IMG img, VOID *v)
{
    // Instrument the memcpy() function.  Print the input argument
    // of each memcpy().
    //
    //  Find the memcpy() function.
    RTN memcpyRtn = RTN_FindByName(img, "memcpy");
    if (RTN_Valid(memcpyRtn))
    {
        
        if (SYM_IFunc(RTN_Sym(memcpyRtn)))
        {
            TraceFile << "Ifunc memcpy" << endl;

            PROTO proto_ifunc_memcpy = PROTO_Allocate( PIN_PARG(void *), CALLINGSTD_DEFAULT,
                                                 "memcpy", PIN_PARG_END() );
        
            RTN_ReplaceSignature(
                memcpyRtn, AFUNPTR( IfuncMemcpyWrapper ),
                IARG_PROTOTYPE, proto_ifunc_memcpy,
                IARG_CONTEXT,
                IARG_ORIG_FUNCPTR,
                IARG_END);

            
        }
        else
        {
            RTN_Open(memcpyRtn);
            TraceFile << "Normal memcpy" << endl;
            // Instrument memcpy() to print the input argument value and the return value.
            RTN_InsertCall(memcpyRtn, IPOINT_BEFORE, (AFUNPTR)MemcpyBefore,
                           IARG_ADDRINT, "memcpy (normal)",
                           IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                           IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                           IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                           IARG_END);
            RTN_Close(memcpyRtn);
        }
        
    }

}

/* ===================================================================== */

VOID Fini(INT32 code, VOID *v)
{
    TraceFile.close();
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */
   
INT32 Usage()
{
    cerr << "This tool produces a trace of calls to normal and ifunc memcpy." << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char *argv[])
{
    // Initialize pin & symbol manager
    PIN_InitSymbolsAlt(SYMBOL_INFO_MODE(UINT32(IFUNC_SYMBOLS) | UINT32(DEBUG_OR_EXPORT_SYMBOLS)));
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }
    
    // Write to a file since cout and cerr maybe closed by the application
    TraceFile.open(KnobOutputFile.Value().c_str());
    TraceFile << hex;
    TraceFile.setf(ios::showbase);
    
    // Register Image to be called to instrument functions.
    IMG_AddInstrumentFunction(Image, 0);
    // Register Instruction to be called to instrument instructions
    TRACE_AddInstrumentFunction(Trace, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
