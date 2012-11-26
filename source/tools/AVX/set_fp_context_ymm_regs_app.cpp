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
// this application is for use in the set_fp_context_ymm_regs.test, in conjunction with the
// set_fp_contest_ymm_regs tool
#if defined(TARGET_WINDOWS)
#include <windows.h>
#include <string>
#include <iostream>
#include <memory.h>
using namespace std;
#define EXPORT_CSYM extern "C" __declspec( dllexport )
#else
//Linux:
#include <ucontext.h>
#include <signal.h>
#include <stdio.h>
#include <setjmp.h>
#include <assert.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <memory.h>
#define EXPORT_CSYM extern "C"
#endif

#include <stdio.h>
#include "../threadlib/threadlib.h"



#if defined( __GNUC__)

#include <stdint.h>
typedef uint8_t  UINT8;   //LINUX HOSTS
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef int8_t  INT8;
typedef int16_t INT16;
typedef int32_t INT32;
typedef int64_t INT64;

#define ALIGN16 __attribute__ ((aligned(16)))
#define ALIGN8  __attribute__ ((aligned(8)))

#elif defined(_MSC_VER)

/*
typedef unsigned __int8 UINT8 ;
typedef unsigned __int16 UINT16;
typedef unsigned __int32 UINT32;
typedef unsigned __int64 UINT64;
typedef __int8 INT8;
typedef __int16 INT16;
typedef __int32 INT32;
typedef __int64 INT64;
*/
#define ALIGN16 __declspec(align(16))
#define ALIGN8  __declspec(align(8))

#else
#error Expect usage of either GNU or MS compiler.
#endif


#define MAX_BYTES_PER_YMM_REG 32
#define MAX_WORDS_PER_YMM_REG (MAX_BYTES_PER_YMM_REG/2)
#define MAX_DWORDS_PER_YMM_REG (MAX_WORDS_PER_YMM_REG/2)
#define MAX_QWORDS_PER_YMM_REG (MAX_DWORDS_PER_YMM_REG/2)
#define MAX_FLOATS_PER_YMM_REG (MAX_BYTES_PER_YMM_REG/sizeof(float))
#define MAX_DOUBLES_PER_YMM_REG (MAX_BYTES_PER_YMM_REG/sizeof(double))

union ALIGN16 ymm_reg_t
{
    UINT8  byte[MAX_BYTES_PER_YMM_REG];
    UINT16 word[MAX_WORDS_PER_YMM_REG];
    UINT32 dword[MAX_DWORDS_PER_YMM_REG];
    UINT64 qword[MAX_QWORDS_PER_YMM_REG];

    INT8   s_byte[MAX_BYTES_PER_YMM_REG];
    INT16  s_word[MAX_WORDS_PER_YMM_REG];
    INT32  s_dword[MAX_DWORDS_PER_YMM_REG];
    INT64  s_qword[MAX_QWORDS_PER_YMM_REG];

    float  flt[MAX_FLOATS_PER_YMM_REG];
    double dbl[MAX_DOUBLES_PER_YMM_REG];

};

extern "C" INT64 get_RDI();
extern "C" void set_ymm_reg0(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg0(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg1(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg1(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg2(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg2(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg3(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg3(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg4(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg4(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg5(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg5(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg6(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg6(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg7(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg7(ymm_reg_t& ymm_reg);
#ifdef TARGET_IA32E
extern "C" void set_ymm_reg8(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg8(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg9(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg9(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg10(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg10(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg11(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg11(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg12(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg12(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg13(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg13(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg14(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg14(ymm_reg_t& ymm_reg);
extern "C" void set_ymm_reg15(ymm_reg_t& ymm_reg);
extern "C" void get_ymm_reg15(ymm_reg_t& ymm_reg);
#endif
extern "C" void mmx_save(char* buf);
extern "C" void mmx_restore(char* buf);


static void
set_ymm_reg(ymm_reg_t& ymm_reg, UINT32 reg_no)
{

    switch (reg_no)
    {
    case 0:
        set_ymm_reg0(ymm_reg);
        break;
    case 1:
        set_ymm_reg1(ymm_reg);
        break;
    case 2:
        set_ymm_reg2(ymm_reg);
        break;
    case 3:
        set_ymm_reg3(ymm_reg);
        break;
    case 4:
        set_ymm_reg4(ymm_reg);
        break;
    case 5:
        set_ymm_reg5(ymm_reg);
        break;
    case 6:
        set_ymm_reg6(ymm_reg);
        break;
    case 7:
        set_ymm_reg7(ymm_reg);
        break;
#ifdef TARGET_IA32E
    case 8:
        set_ymm_reg8(ymm_reg);
        break;
    case 9:
        set_ymm_reg9(ymm_reg);
        break;
    case 10:
        set_ymm_reg10(ymm_reg);
        break;
    case 11:
        set_ymm_reg11(ymm_reg);
        break;
    case 12:
        set_ymm_reg12(ymm_reg);
        break;
    case 13:
        set_ymm_reg13(ymm_reg);
        break;
    case 14:
        set_ymm_reg14(ymm_reg);
        break;
    case 15:
        set_ymm_reg15(ymm_reg);
        break;
#endif
    }

} 
static void
get_ymm_reg(ymm_reg_t& ymm_reg, UINT32 reg_no)
{
    switch (reg_no)
    {
    case 0:
       get_ymm_reg0(ymm_reg);
       break;
    case 1:
        get_ymm_reg1(ymm_reg);
        break;
    case 2:
        get_ymm_reg2(ymm_reg);
        break;
    case 3:
        get_ymm_reg3(ymm_reg);
        break;
    case 4:
        get_ymm_reg4(ymm_reg);
        break;
    case 5:
        get_ymm_reg5(ymm_reg);
        break;
    case 6:
        get_ymm_reg6(ymm_reg);
        break;
    case 7:
        get_ymm_reg7(ymm_reg);
        break;
#ifdef TARGET_IA32E
    case 8:
        get_ymm_reg8(ymm_reg);
        break;
    case 9:
        get_ymm_reg9(ymm_reg);
        break;
    case 10:
        get_ymm_reg10(ymm_reg);
        break;
    case 11:
        get_ymm_reg11(ymm_reg);
        break;
    case 12:
        get_ymm_reg12(ymm_reg);
        break;
    case 13:
        get_ymm_reg13(ymm_reg);
        break;
    case 14:
        get_ymm_reg14(ymm_reg);
        break;
    case 15:
        get_ymm_reg15(ymm_reg);
        break;
#endif
    }

}


//////////////////////////////////////////////////////



void write_ymm_reg(UINT32 reg_no, UINT32 val)
{

    ymm_reg_t ymm;
    ymm.dword[0] = val;
    ymm.dword[1] = val;
    ymm.dword[2] = val;
    ymm.dword[3] = val;
	ymm.dword[4] = val;
    ymm.dword[5] = val;
    ymm.dword[6] = val;
    ymm.dword[7] = val;
    
    set_ymm_reg(ymm, reg_no); 
}

void read_ymm_reg(UINT32 reg_no, ymm_reg_t& ymm)
{

    ymm.dword[0] = 0;
    ymm.dword[1] = 0;
    ymm.dword[2] = 0;
    ymm.dword[3] = 0;
	ymm.dword[4] = 0;
    ymm.dword[5] = 0;
    ymm.dword[6] = 0;
    ymm.dword[7] = 0;
    
    get_ymm_reg(ymm, reg_no); 
}


#ifdef TARGET_IA32E

#define NUM_YMM_REGS 16
#else
#define NUM_YMM_REGS 8
#endif

/*
 Retrieve the ymm registers and print their contents
 */
void DumpYmmRegs()
{
    ymm_reg_t ymm_regs[NUM_YMM_REGS];
    for (UINT32 i=0; i<NUM_YMM_REGS; i++)
    {
        read_ymm_reg(i, ymm_regs[i]);
    }
    printf ("DumpYmmRegs\n");
    fflush (stdout);
    for (UINT32 i=0; i<NUM_YMM_REGS; i++)
    {
        printf ("ymm%d: ", i);
        fflush (stdout);
        for (INT32 j=MAX_DWORDS_PER_YMM_REG-1; j>=0; j--)
        {
            printf ("%x:", ymm_regs[i].dword[j]);
            fflush (stdout);
        }
        printf ("\n");
        fflush (stdout);
    } 
}


/*
 Retrieve the ymm registers and print their contents
 */
void SetYmmRegs(UINT32 val)
{
    ymm_reg_t ymm_regs[NUM_YMM_REGS];
    for (UINT32 i=0; i<NUM_YMM_REGS; i++)
    {
        write_ymm_reg(i, val);
    } 
}


/* when run with the set_fp_context_ymm_regs tool, the tool will have replac this
   function with a function that calls this original but first the tool 
   replacement function sets the ymm regs in the context used to 
   in the PIN_CallApplicationFunction used to call this original fnction
*/
EXPORT_CSYM void ReplacedYmmRegs()
{
    // just dump the contents of the ymm regs
    DumpYmmRegs();
}

/* when run with the set_fp_context_ymm_regs tool, the tool will call this
   function via the PIN_ExecuteAt, but first the tool will 
   sets the ymm regs in the context used to in the PIN_ExecuteAt call
*/
EXPORT_CSYM void ExecutedAtFunc()
{
    // just dump the contents of the ymm regs
    DumpYmmRegs();
}

// the tool's OnException function directs execution to here after changing the values in the ymm registers
EXPORT_CSYM void DumpYmmRegsAtException()
{
    // just dump the contents of the ymm regs
    DumpYmmRegs();
    // and exit OK
    exit (0);
}

/* when run with the set_fp_context_ymm_regs tool, the tool sets the ymm regs in the context used to 
   execute the thread - this is done in the thread creation callback received from Pin
*/
void *ThreadFunc(void * arg)
{
    ymm_reg_t ymm_regs[NUM_YMM_REGS];
    for (UINT32 i=0; i<NUM_YMM_REGS; i++)
    {
        read_ymm_reg(i, ymm_regs[i]);
    }
    printf ("DumpYmmRegs from Thread\n");
    fflush (stdout);
    for (UINT32 i=0; i<NUM_YMM_REGS; i++)
    {
        printf ("ymm%d: ", i);
        fflush (stdout);
        for (INT32 j=MAX_DWORDS_PER_YMM_REG-1; j>=0; j--)
        {
            printf ("%x:", ymm_regs[i].dword[j]);
            fflush (stdout);
        }
        printf ("\n");
        fflush (stdout);
    } 
    return (NULL);
}

#if !defined(TARGET_WINDOWS)

// Linux

// the segv exception handler will never be reached, because the tool OnException function redirects the
// continuation to the DumpYmmRegsAtException
void handle(int sig, siginfo_t* info, void* vctxt)
{
    printf ("Exception ocurred. Now in handler\n");
    fflush (stdout);
}
#endif

int main()
{
    int i;
    THREAD_HANDLE threadHandle;

    printf ("ymm regs at ReplacedYmmRegs\n");
    fflush(stdout);
    ReplacedYmmRegs();

    /* create a thread that dumps the values in the ymm regs 
    printf ("ymm regs at threads\n");
    fflush (stdout);
    CreateOneThread(&threadHandle, ThreadFunc, 0);
    JoinOneThread(threadHandle);
    */

#if !defined(TARGET_WINDOWS)
// Linux
    // define a handler so that the tool gets the  context change callback with the CONTEXT_CHANGE_REASON_SIGNAL
    // and a valid ctxtTo 
    struct sigaction sigact;

    sigact.sa_sigaction = handle;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = SA_SIGINFO;
    if (sigaction(SIGSEGV, &sigact, 0) == -1)
    {
        fprintf(stderr, "Unable to handle SIGSEGV signal\n");
        exit (-1);
    }
#endif

    printf ("ymm regs before exception\n");
    SetYmmRegs(0xa5a5a5a5);
    DumpYmmRegs();
    printf ("next print of ymm regs will be after the tool's OnException function has set their values\n");
    char * p = 0;
    p++;
    SetYmmRegs(0xa5a5a5a5);
    // the gpf here will cause the invocation of the tool's OnException function
    *p = 0;   
}



