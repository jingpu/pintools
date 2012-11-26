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
#include "pin.H"

// simple vgather* emulator, using the IARG_MULTI_MEMORYACCESS_EA.

VOID EmuGather (PIN_MULTI_MEM_ACCESS_INFO* multiMemAccessInfo, PIN_REGISTER* ymmDest, PIN_REGISTER* ymmMask)
{
    PIN_MEM_ACCESS_INFO *pinMemAccessInfo = &(multiMemAccessInfo->memop[0]);
    int totalPossibleWriteSize = multiMemAccessInfo->numberOfMemops*pinMemAccessInfo->bytesAccessed;
    
    for (UINT32 i=0; i<multiMemAccessInfo->numberOfMemops; i++)
    {
        ASSERTX (pinMemAccessInfo->memopType == PIN_MEMOP_LOAD);
        
        if (pinMemAccessInfo->maskOn)
        {
            if (pinMemAccessInfo->bytesAccessed == 4)
            {
                ymmDest->dword[i] = *(reinterpret_cast<UINT32 *>(pinMemAccessInfo->memoryAddress));
            }
            else
            {
                ASSERTX(pinMemAccessInfo->bytesAccessed == 8);
                ymmDest->qword[i] = *(reinterpret_cast<UINT64 *>(pinMemAccessInfo->memoryAddress));
            }
        }
        pinMemAccessInfo++;
    }
    if (totalPossibleWriteSize<32)
    {
        ymmDest->qword[3] = 0;
        ymmDest->qword[2] = 0;
        if (totalPossibleWriteSize<16)
        {
            ymmDest->qword[1] = 0;
        }
    }
    ymmMask->qword[0] = 0;
    ymmMask->qword[1] = 0;
    ymmMask->qword[2] = 0;
    ymmMask->qword[3] = 0;
}

// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID *v)
{
    if (INS_IsVgather(ins))
    {
        REG ymmDest = INS_OperandReg(ins, 0), ymmMask = INS_OperandReg(ins, 2);
        if (!REG_is_ymm(ymmDest))
        {
            ymmDest = (REG)(ymmDest - REG_XMM0 + REG_YMM0);
        }
        if (!REG_is_ymm(ymmMask))
        {
            ymmMask = (REG)(ymmMask - REG_XMM0 + REG_YMM0);
        }
                
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)EmuGather, 
                        IARG_MULTI_MEMORYACCESS_EA,
                        IARG_REG_REFERENCE, ymmDest,
                        IARG_REG_REFERENCE, ymmMask,
                        IARG_END);

        INS_Delete(ins);
    }
}


/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */
/*   argc, argv are the entire command line: pin -t <toolname> -- ...    */
/* ===================================================================== */

int main(int argc, char * argv[])
{
    // Initialize pin
    PIN_Init(argc, argv);

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}
