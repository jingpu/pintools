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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pin.H"

BUFFER_ID bufId;

const int MAX_VGATHERS = 10;
const int NUM_BUF_PAGES = 64;
int numVgathers = 0;
int bufferFullCallbackReceived = 0;

PIN_MULTI_MEM_ACCESS_INFO vgathers[MAX_VGATHERS];

VOID PrintPinMemAccessInfo(UINT32 index, PIN_MEM_ACCESS_INFO* pinMemAccessInfo)
{
    printf ("  PinMemAccessInfo# %d   memoryAddress %p memopType %d bytesAccessed %d maskOn %d\n",
            index, (void *)(pinMemAccessInfo->memoryAddress), pinMemAccessInfo->memopType, pinMemAccessInfo->bytesAccessed, pinMemAccessInfo->maskOn);
}

VOID PrintPinMltiMemAccessInfo(PIN_MULTI_MEM_ACCESS_INFO* multiMemAccessInfo)
{
    printf ("PIN_MULTI_MEM_ACCESS_INFO numberOfMemops %d\n", multiMemAccessInfo->numberOfMemops);
    for (UINT32 i=0; i<MAX_MULTI_MEMOPS; i++)
    {
        PrintPinMemAccessInfo(i, &(multiMemAccessInfo->memop[i]));
    }
    fflush (stdout);
}

VOID EmuGather (PIN_MULTI_MEM_ACCESS_INFO* multiMemAccessInfo, PIN_REGISTER* ymmDest, PIN_REGISTER* ymmMask)
{
    PIN_MEM_ACCESS_INFO *pinMemAccessInfo = &(multiMemAccessInfo->memop[0]);
    int totalPossibleWriteSize = multiMemAccessInfo->numberOfMemops*pinMemAccessInfo->bytesAccessed;
    
    printf ("EmuGather multiMemAccessInfo->numberOfMemops %d\n", multiMemAccessInfo->numberOfMemops);
    fflush (stdout);
    printf ("          pinMemAccessInfo->bytesAccessed %d\n", pinMemAccessInfo->bytesAccessed);
    fflush (stdout);
    printf ("          numVgathers %d\n", numVgathers);
    fflush (stdout);
    ASSERTX(numVgathers<MAX_VGATHERS);
    vgathers[numVgathers] = *multiMemAccessInfo;

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
    numVgathers++;
    printf ("EmuGather finished\n");
    fflush (stdout);
}


/*!
 * Called when a buffer fills up, or the thread exits, so we can process it or pass it off
 * as we see fit.
 * @param[in] id		buffer handle
 * @param[in] tid		id of owning thread
 * @param[in] ctxt		application context when the buffer filled
 * @param[in] buf		actual pointer to buffer
 * @param[in] numElements	number of records
 * @param[in] v			callback value
 * @return  A pointer to the buffer to resume filling.
 */
VOID * BufferFull(BUFFER_ID id, THREADID tid, const CONTEXT *ctxt, VOID *buf,
                  UINT64 numElements, VOID *v)
{
    
    PIN_MULTI_MEM_ACCESS_INFO* reference=(PIN_MULTI_MEM_ACCESS_INFO*)buf;
    UINT64 i;

    bufferFullCallbackReceived = 1;
    printf ("BufferFull numElements %d numVgathers %d\n", numElements, numVgathers);
    fflush (stdout);

    // check that the PIN_MULTI_MEM_ACCESS_INFOs recorded in the buffer are identical to those
    // recorded in the vgathers[]
    if (numElements != numVgathers)
    {
        printf ("numElements %d numVgathers %d miscompare\n", numElements, numVgathers);
        fflush (stdout);
        exit (1);
    }
    for(i=0; i<numElements; i++){
        if (memcmp(reinterpret_cast<void *>(&reference[i]),  
                   reinterpret_cast<void *>(&vgathers[i]), 
                   sizeof(PIN_MULTI_MEM_ACCESS_INFO)))
        {
            printf ("PIN_MULTI_MEM_ACCESS_INFO miscompare on buffer element# %d %x %x\n", i,
                    (ADDRINT)(&reference[i]) - (ADDRINT)(reference),
                    (ADDRINT)(&vgathers[i]) - (ADDRINT)(vgathers));
            fflush (stdout);
            PrintPinMltiMemAccessInfo (&reference[i]);
            PrintPinMltiMemAccessInfo (&vgathers[i]);
            exit (1);
        }
    }
    
    return buf;
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

        INS_InsertFillBuffer(ins, IPOINT_BEFORE, bufId,
                                IARG_MULTI_MEMORYACCESS_EA, 0, IARG_END);

        INS_Delete(ins);
    }
}

VOID Fini(INT32 code, VOID *v)
{

    if (!bufferFullCallbackReceived)
    {
        fprintf (stderr, "Did not receive the BufferFull\n");
        exit (1);
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

    // Initialize the memory reference buffer
    bufId = PIN_DefineTraceBuffer(sizeof(PIN_MULTI_MEM_ACCESS_INFO), NUM_BUF_PAGES,
                                  BufferFull, 0);

    if(bufId == BUFFER_ID_INVALID)
    {
        fprintf (stderr, "Error allocating initial buffer\n");
        return 1;
    }

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    // Register function to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}
