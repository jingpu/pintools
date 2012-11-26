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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pin.H>

KNOB<BOOL>   KnobSetFirstThreeX87ToZeroInEmulateXrstor(KNOB_MODE_WRITEONCE, "pintool",
    "set_in_xrstor", "0", "SetFirstThreeX87ToZeroInEmulateXrstor");
KNOB<BOOL>   KnobRegsAll(KNOB_MODE_WRITEONCE, "pintool",
    "regs_all", "0", "RegsAll");
KNOB<BOOL>   KnobUseConstContextInXsaveEmulation(KNOB_MODE_WRITEONCE, "pintool",
    "use_const_context", "0", "UseConstContextInXsaveEmulation");

#ifdef TARGET_WINDOWS
namespace WIND
{
#include <windows.h>
}
#define EXPORT_CSYM extern "C" __declspec( dllexport )
#else
#define EXPORT_CSYM extern "C" 
#endif
#if defined( __GNUC__)

#include <stdint.h>


#define ALIGN16 __attribute__ ((aligned(16)))
#define ALIGN8  __attribute__ ((aligned(8)))

#elif defined(_MSC_VER)



#define ALIGN16 __declspec(align(16))
#define ALIGN8  __declspec(align(8))

#else
#error Expect usage of either GNU or MS compiler.
#endif

ADDRINT executeAtAddr = 0;

#ifdef TARGET_IA32E
#define NUM_XMM_REGS 16
#if defined( __GNUC__)
#define NUM_XMM_SCRATCH_REGS 16
#else
#define NUM_XMM_SCRATCH_REGS 5
#endif
typedef UINT64 reg_t;
#else
#define NUM_XMM_REGS 8
#define NUM_XMM_SCRATCH_REGS 8
typedef UINT32 reg_t;
#endif


extern "C" BOOL ProcessorSupportsAvx();
#if defined(__cplusplus)
extern "C"
#endif
VOID FldzToTop3();
#if defined(__cplusplus)
extern "C"
#endif
VOID Fld2tToTop3();
#if defined(__cplusplus)
extern "C"
#endif
VOID SetXmmRegsToZero();
#if defined(__cplusplus)
extern "C"
#endif
VOID SetIntRegsToZero();
#if defined(__cplusplus)
extern "C"
#endif
VOID AddToXmmRegs();
#if defined(__cplusplus)
extern "C"
#endif
void UnMaskZeroDivideInMxcsr();

#if defined(__cplusplus)
extern "C"
#endif
double var1=2.0;
#if defined(__cplusplus)
extern "C"
#endif
double var2=2.0;
#if defined(__cplusplus)
extern "C"
#endif
double var3=2.0;


#if defined(__cplusplus)
extern "C"
#endif
VOID DummyProc()
{
}

EXPORT_CSYM void TestIargPreserveInReplacement()
{
}

EXPORT_CSYM void TestIargPreserveInReplacement1()
{
}

EXPORT_CSYM void TestIargPreserveInReplacement2()
{
}

EXPORT_CSYM void TestIargPreserveInProbed()
{
}

EXPORT_CSYM void TestIargPreserveInProbed1()
{
}

EXPORT_CSYM void TestIargPreserveInProbed2()
{
}



VOID EmulateXsave(CONTEXT *ctxt, ADDRINT buffer)
{
    printf ("tool EmulateXsave buffer %p\n", buffer); fflush (stdout);
    unsigned char fpContext[sizeof (FPSTATE)+ FPSTATE_ALIGNMENT];
    FPSTATE *fpVerboseContext= 
		reinterpret_cast<FPSTATE *>
		(( reinterpret_cast<ADDRINT>(fpContext) + (FPSTATE_ALIGNMENT - 1)) & (-1*FPSTATE_ALIGNMENT));


    PIN_GetContextFPState(ctxt, fpVerboseContext);

    FPSTATE *fpVerboseContextToApp= 
		reinterpret_cast<FPSTATE *>(buffer);


    *fpVerboseContextToApp = *fpVerboseContext;
}

VOID EmulateXrstor(CONTEXT *ctxt, ADDRINT buffer)
{
    printf ("tool EmulateXrstor buffer %p\n", buffer); fflush (stdout);

    FPSTATE *fpVerboseContextFromApp= 
		reinterpret_cast<FPSTATE *>(buffer);

    // copy from apps buffer
    unsigned char fpContext[sizeof (FPSTATE)+ FPSTATE_ALIGNMENT];
    FPSTATE *fpVerboseContextCopy= 
		reinterpret_cast<FPSTATE *>
		(( reinterpret_cast<ADDRINT>(fpContext) + (FPSTATE_ALIGNMENT - 1)) & (-1*FPSTATE_ALIGNMENT));
    *fpVerboseContextCopy = *fpVerboseContextFromApp;

    if (KnobSetFirstThreeX87ToZeroInEmulateXrstor)
    {
        printf ("  tool EmulateXrstor setting first three x87 regs to 0.0\n"); fflush (stdout);
		for (int i=0; i< 3; i++)
		{
			fpVerboseContextCopy->fxsave_legacy._sts[i]._raw._lo = 0;
			fpVerboseContextCopy->fxsave_legacy._sts[i]._raw._hi = 0;
		}
    }
   
   PIN_SetContextFPState(ctxt, fpVerboseContextCopy);
}



BOOL havefldl2tSequence = FALSE;
BOOL haveXsave = FALSE;
VOID Trace (TRACE trace, VOID *v)
{
    if (!havefldl2tSequence)
    {   // identify the sequence in the app that results from the app call to Fld2tToTop3a
		for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl))
		{
			for (INS ins = BBL_InsHead(bbl); INS_Valid(ins); ins = INS_Next(ins))
			{
				xed_iclass_enum_t iclass1 = static_cast<xed_iclass_enum_t>(INS_Opcode(ins));
				if (iclass1 == XED_ICLASS_FLDL2T && INS_Valid(INS_Next(ins)))
				{
					xed_iclass_enum_t iclass2 = static_cast<xed_iclass_enum_t>(INS_Opcode(INS_Next(ins)));
					if (iclass2 == XED_ICLASS_FLDL2T && INS_Valid(INS_Next(INS_Next(ins))))
					{
						xed_iclass_enum_t iclass3 = static_cast<xed_iclass_enum_t>(INS_Opcode(INS_Next(INS_Next(ins))));
						if (iclass3 == XED_ICLASS_FLDL2T)
						{
							fflush (stdout);
							havefldl2tSequence = TRUE;
							return;
						}
					}
				}
			}
		}
        return;
    }
	for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl))
    {
        for (INS ins = BBL_InsHead(bbl); INS_Valid(ins); ins = INS_Next(ins))
        {
            xed_iclass_enum_t iclass1 = static_cast<xed_iclass_enum_t>(INS_Opcode(ins));
            if (iclass1 == XED_ICLASS_XSAVE)
            {
                if (!haveXsave)
                {
				    printf ("tool found first xsave at %x it will be left as is\n", INS_Address(ins)); fflush (stdout);
			        haveXsave = TRUE;
                }
                else
                {
                    printf ("tool found second xsave at %x it will be emulated\n", INS_Address(ins)); fflush (stdout);
					if (KnobUseConstContextInXsaveEmulation)
					{
						INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(EmulateXsave), IARG_CONST_CONTEXT, IARG_REG_VALUE, REG_GCX, IARG_END);
					}
					else
					{
						INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(EmulateXsave), IARG_CONTEXT, IARG_REG_VALUE, REG_GCX, IARG_END);
					}
                    INS_Delete(ins);
                }
                return;
			}
            if (iclass1 == XED_ICLASS_XRSTOR)
            {
				printf ("tool found xrstor at %x it will be emulated\n", INS_Address(ins)); fflush (stdout);
                REGSET regsIn;
                REGSET regsOut;
                if (KnobRegsAll)
                {
                    REGSET_AddAll(regsIn);
                    REGSET_AddAll(regsOut);
                }
                else
                {
					REGSET_Insert (regsIn, REG_X87);
					REGSET_Insert (regsOut, REG_X87);
					for( int i = REG_XMM0; i <= REG_XMM_LAST; i++) {
						REGSET_Insert (regsIn, (REG)i);
						REGSET_Insert (regsOut, (REG)i);
					}
					if (ProcessorSupportsAvx()) {
						printf ("  tool found ProcessorSupportsAvx\n"); fflush (stdout);
						for( int i = REG_YMM0; i <= REG_YMM_LAST; i++) {
							REGSET_Insert (regsIn, (REG)i);
							REGSET_Insert (regsOut, (REG)i);
						}
					}
                }

                INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(EmulateXrstor), IARG_PARTIAL_CONTEXT, &regsIn, &regsOut, IARG_REG_VALUE, REG_GCX, IARG_END);
                INS_Delete(ins);
                
                return;
			}
		}
    }

}



VOID Fini(INT32 code, VOID *v)
{
    
}

int main(int argc, char *argv[])
{

    PIN_Init(argc, argv);

    PIN_InitSymbols();

    TRACE_AddInstrumentFunction(Trace, 0);

    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}

