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
/* 
 * INTEL CONFIDENTIAL
 * Copyright 2008-2012 Intel Corporation All Rights Reserved. 
 *
 * The source code contained or described herein and all documents related to
 * the source code ("Material") are owned by Intel Corporation or its suppliers
 * or licensors. Title to the Material remains with Intel Corporation or its
 * suppliers and licensors. The Material contains trade secrets and proprietary
 * and confidential information of Intel or its suppliers and licensors. The
 * Material is protected by worldwide copyright and trade secret laws and
 * treaty provisions. No part of the Material may be used, copied, reproduced,
 * modified, published, uploaded, posted, transmitted, distributed, or
 * disclosed in any way without Intel's prior express written permission.
 *
 * No license under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or delivery
 * of the Materials, either expressly, by implication, inducement, estoppel or
 * otherwise. Any license under such intellectual property rights must be
 * express and approved by Intel in writing.
 */

/*
 * This file name was hle_rtm.h before is was renamed to test_rtm.h 
 * Inline functions for  RTM.
 * These are simple examples used for testing, they are not necessarily
 * of production quality...
 *
 * If you use this outside the testing system, then you need to ensure that
 * the correct symbols are defined to select the target cpu.
 */
#ifndef __TEST_RTM_H
#define __TEST_RTM_H

#define FUND_CPU_IA32    1
#define FUND_CPU_INTEL64 2

#define FUND_OS_WINDOWS  1
#define FUND_OS_LINUX    2

/* Instruction prefixes */
#define OP_XACQUIRE 0xF2
#define OP_XRELEASE 0xF3
#define OP_LOCK    0xF0

#define STRINGIZE_INTERNAL(arg) #arg
#define STRINGIZE(arg) STRINGIZE_INTERNAL(arg)

#if TARGET_WINDOWS
#ifndef _WINDEF_
// from msdn : Windows Data Types
#define WINAPI __stdcall
typedef unsigned long DWORD;
#if __cplusplus
extern "C"  {
#endif
void WINAPI Sleep( DWORD millisec );
long WINAPI SwitchToThread(void);
#if __cplusplus
}
#endif
#endif /* _WINDEF_ */
#endif /* TARGET_WINDOWS */

#if TARGET_WINDOWS
# define yield() SwitchToThread()
#else
# include <sched.h>
# define yield() sched_yield()
#endif

#include "rtm_stdint.h"


static __inline void pauseInstruction()
{
#if TARGET_WINDOWS
    __asm pause
#else
    __asm__ volatile ("pause");
#endif
}

static __inline void rtm_machine_pause( int delay ) {
    int i;
    for( i=0; i<delay; ++i ) {
        pauseInstruction();
    }
}

static __inline void exp_backoff( int* cp ) {
    if( *cp<=16 ) {
        rtm_machine_pause( *cp );
        /* Pause twice as long the next time. */
        *cp *= 2;
    } else {
        yield();
    }
}

/* RTM Functions */
/*! 
 * Enter speculative execution mode.
 */
static __inline int XBegin()
{
    int res = 1;
    
    /* Note that %eax must be noted as killed, because the XSR is returned
     * in %eax on abort. Other register values are restored, so don't need to be
     * killed.
     * We must also mark res as an input and an output, since otherwise the 
     * res=1 may be dropped as being dead, whereas we do need that on the
     * normal path.
     */
#if TARGET_WINDOWS
    __asm {
        // We need to save and restore eax\rax cause compiler uses it sometimes
#  if TARGET_IA32
        push eax
#  else
        push rax
# endif
        _emit 0xC7
        _emit 0xF8
        _emit 2
        _emit 0
        _emit 0
        _emit 0
        jmp   L2
        mov   res,  0
    L2:
#  if TARGET_IA32
        pop eax
#  else
        pop rax
#  endif
    }
#else
    __asm__ volatile ("1: .byte  0xC7; .byte 0xF8;\n"
                      "   .long  1f-1b-6\n"
                      "    jmp   2f\n"
                      "1:  xor   %0,%0\n"
                      "2:"
                      :"=r"(res):"0"(res):"memory","%eax");
#endif
    return res;
}

/*! 
 * Transaction end 
 */
static __inline void XEnd()
{
#if TARGET_WINDOWS
    __asm  {
        _emit 0x0f
        _emit 0x01
        _emit 0xd5
    }
#else
    __asm__ volatile (".byte 0x0f; .byte 0x01; .byte 0xd5" :::"memory");
#endif
}

/*!
 * Transaction abort, with immediate zero. 
 */
static __inline void XAbort()
{
#if (TARGET_WINDOWS)
    __asm  {
        _emit 0xc6
        _emit 0xf8
        _emit 0x00
    }
#else
    __asm__ volatile (".byte 0xC6; .byte 0xF8; .byte 0x00" :::"memory");
#endif
}

/*! 
 * Additional version of XBegin which returns -1 on speculation, 
 * and the value of EAX on an abort.
 */
static __inline int XBeginEax()
{
    int res = -1;
    
#if TARGET_WINDOWS
#if TARGET_INTEL64
    _asm {
        _emit 0xC7
        _emit 0xF8
        _emit 2
        _emit 0
        _emit 0
        _emit 0
        jmp   L2
        mov   res, eax
    L2:
    }
#else /* TARGET_IA32 */
    _asm {
        _emit 0xC7
        _emit 0xF8
        _emit 2
        _emit 0
        _emit 0
        _emit 0
        jmp   L2
        mov   res, eax
    L2:
    }
#endif /* TARGET_INTEL64 */
#else /* LINUX */
    /* Note that %eax must be noted as killed (clobbered), because 
     * the XSR is returned in %eax(%rax) on abort.  Other register 
     * values are restored, so don't need to be killed.
     *
     * We must also mark 'res' as an input and an output, since otherwise 
     * 'res=-1' may be dropped as being dead, whereas we do need the 
     * assignment on the successful (i.e., non-abort) path.
     */
#if TARGET_INTEL64
    __asm__ volatile ("1: .byte  0xC7; .byte 0xF8;\n"
                      "   .long  1f-1b-6\n"
                      "    jmp   2f\n"
                      "1:  movl  %%eax,%0\n"
                      "2:"
                      :"=r"(res):"0"(res):"memory","%eax");
#else /* if TARGET_IA32 */
    __asm__ volatile ("1: .byte  0xC7; .byte 0xF8;\n"
                      "   .long  1f-1b-6\n"
                      "    jmp   2f\n"
                      "1:  movl  %%eax,%0\n"
                      "2:"
                      :"=r"(res):"0"(res):"memory","%eax");
#endif /* TARGET_INTEL64 */
#endif /* TARGET_WINDOWS */
    return res;
}

/* This is a macro, the argument must be a single byte constant which
 * can be evaluated by the inline assembler, since it is emitted as a
 * byte into the assembly code.
 */
#if TARGET_WINDOWS
#define emitXAbort(ARG) \
    _asm _emit 0xc6     \
    _asm _emit 0xf8     \
    _asm _emit ARG
#else
#define emitXAbort(ARG) \
    __asm__ volatile (".byte 0xC6; .byte 0xF8; .byte " STRINGIZE(ARG) :::"memory");
#endif

/* Values of RTM bits in EAX after RTM abort */
/* XABORT bits in EAX */
enum XA_EAX_masks
{
    XA_mask_xabort   = (1<<0),
    XA_mask_retry    = (1<<1),
    XA_mask_conflict = (1<<2),
    XA_mask_capacity = (1<<3),
    XA_mask_debug    = (1<<4),
    XA_mask_nested   = (1<<5), /* added as of 2010 WW42 */
    XA_xabort_value_shift = 24,
    // bits 31:24
    XA_mask_xabort_value_mask = ( 0xff<<XA_xabort_value_shift )
};

typedef enum {
    EFLAGS_CARRY     = 0x1<<0,
    EFLAGS_PARITY    = 0x1<<2,
    EFLAGS_AUX_CARRY = 0x1<<4,
    EFLAGS_ZERO      = 0x1<<6,
    EFLAGS_SIGN      = 0x1<<7,
    EFLAGS_DIRECTION = 0x1<<10,
    EFLAGS_OVERFLOW  = 0x1<<11
} eflag_mask_t;

#if IDB_SUPPORT || INTEL_PRIVATE
#include "../Emulator/rtm_idb.h"
#endif

/* isintx */
#if TARGET_WINDOWS
#define emitXTEST() \
    _asm _emit 0x0F  \
    _asm _emit 0x01  \
    _asm _emit 0xD6
#else
#define emitXTEST() \
    __asm__ volatile (".byte 0x0F; .byte 0x01; .byte 0xD6" :::"memory");
#endif

static __inline int IsInTx()
{
#if TARGET_WINDOWS
    int8_t res = 0;
    emitXTEST()
    __asm {
        setz ah
        mov  res, ah
    }
    return res==0;
#else
    int8_t res = 0;
    __asm__ __volatile__ (".byte 0x0F; .byte 0x01; .byte 0xD6;\n" 
                          "setz %0" : "=r"(res) : : "memory" );
#endif
    return res==0;
}

/* xnmov */
#if TARGET_WINDOWS
#define emitXNMOV() \
    _asm _emit 0x0F  \
    _asm _emit 0x38  \
    _asm _emit 0xF4
#define emitOperandModifier() _asm _emit 0x66
#define emitOperandModifierRexW() _asm _emit 0x48
#else
#define emitXNMOV() __asm__ volatile (".byte 0x0F; .byte 0x38; .byte 0xF4;" :::"memory")
#define emitOperandModifier66() __asm__ volatile (".byte 0x66;" :::"memory")
#define emitOperandModifierRexW() __asm__ volatile (".byte 0x48;" :::"memory")
#endif

#if TARGET_WINDOWS
#define EMIT_SIZE_MODIFIER_SIZE_MOD_16  _emit 0x66
#define EMIT_SIZE_MODIFIER_SIZE_MOD_64  _emit 0x48
#define EMIT_SIZE_MODIFIER_SIZE_MOD_NONE
/* datatype, addr width, addr reg, data width, data reg, size mod */
#define XNMOV_TEMPLATE(ADR,DT,AW,AR,DW,DR,SM) \
    DT v;                                     \
    _asm { mov AR , ADR  }                    \
    _asm    EMIT_SIZE_MODIFIER_##SM           \
    _asm    _emit 0x0F                        \
    _asm    _emit 0x38                        \
    _asm    _emit 0xF4                        \
    _asm    _emit 0x00                        \
    _asm {    mov v , DR       }              \
    return v;
#if TARGET_IA32
#define ADDR_WIDTH  l
#define RAX_EAX     eax 
#else /* TARGET_INTEL64 */
#define ADDR_WIDTH  q
#define RAX_EAX     rax 
#endif /* TARGET_IA32 */
#define SIZE_MOD_16 16
#define SIZE_MOD_64 64
#define SIZE_MOD_NONE NONE
#else /* TARGET_LINUX */
/* datatype, addr width, addr reg, data width, data reg, size mod */
#define XNMOV_TEMPLATE(ADR,DT,AW,AR,DW,DR,SM) \
    DT v; \
    __asm__ __volatile__ ("mov" STRINGIZE(AW) " %0, %%" STRINGIZE(AR) "\n" : : "r"(ADR) : "memory" ); \
    __asm__ __volatile__ (SM ".byte 0x0F; .byte 0x38; .byte 0xF4; .byte 0x00; \n" : : : "memory" ); \
    __asm__ __volatile__ ("mov" #DW " %%" #DR ", %0\n" : "=r"(v) : : "memory" );  \
    return v;
#if TARGET_IA32
#define ADDR_WIDTH  l
#define RAX_EAX     eax 
#else /* TARGET_INTEL64 */
#define ADDR_WIDTH  q
#define RAX_EAX     rax 
#endif /* TARGET_IA32 */
#define SIZE_MOD_16 ".byte 0x66; "
#define SIZE_MOD_64 ".byte 0x48; "
#define SIZE_MOD_NONE ""
#endif /* TARGET_WINDOWS */

static __inline int16_t read_nx_16( void* addr )
{
    XNMOV_TEMPLATE(addr,int16_t,ADDR_WIDTH,RAX_EAX,w,ax,SIZE_MOD_16);
}

static __inline int32_t read_nx_32( void* addr )
{
    XNMOV_TEMPLATE(addr,int32_t,ADDR_WIDTH,RAX_EAX,l,eax,SIZE_MOD_NONE);
}

#if TARGET_INTEL64
static __inline int64_t read_nx_64( void* addr )
{
    XNMOV_TEMPLATE(addr,int64_t,ADDR_WIDTH,RAX_EAX,q,rax,SIZE_MOD_64);
}
#endif /* TARGET_INTEL64 */

#endif /* __TEST_RTM_H */
