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
 * Copyright 2010-2012 Intel Corporation All Rights Reserved.
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

#ifndef __TEST_UTIL_H
#define __TEST_UTIL_H

#if TARGET_LINUX
#include <unistd.h>
#endif

#define CACHE_LINE_SIZE 64
#define FOUR_MB (4*1024*1024)

#include "rtm_stdint.h"

#define ALIGN(p,n) ((p+((n)-1)) & ~((n)-1))

typedef int lock_t;
#define ALLOCATE_MULTIPLE_LOCKS(name) static lock_t ( name ) [3*CACHE_LINE_SIZE/sizeof(lock_t)]

__inline int* cache_line_base( int* p )
{
    return (int*) ((uintptr_t)p&~(CACHE_LINE_SIZE-1));
}

__inline char* align( const char* p, const size_t sz )
{
    return (char*) ((uintptr_t)(p+sz-1)&~(sz-1));
}

__inline int find_lock_at_the_bottom_of_a_cache_line( lock_t* locks )
{
    int i;
    for( i=0; i<2*CACHE_LINE_SIZE/sizeof(lock_t); ++i ) {
        if( (lock_t*) cache_line_base( (int*)(locks+i) )==(locks+i) )
            return i;
    }
    return -1;
}

__inline int TEST_EPILOGUE( int res )
{
    printf( "%s\n", res ? "PASSED" : "\n*************\n********** FAILED ********\n**********" );
    return res>0 ? 0 : 1;
}

#if _WIN32||_WIN64
// we are using the Intel compiler icl on Windows
#define __release_consistency_helper() __asm { __asm nop }
#else
#define __release_consistency_helper() __asm__ __volatile__ ( "" : : : "memory" )
#endif /* _WIN32||_WIN64 */

__inline int atomic_read( int const volatile* src )
{
    int temp = *src;
    __release_consistency_helper();
    return temp;
}

__inline void atomic_write( int volatile* dest, int val )
{
    __release_consistency_helper();
    *dest = val;
}

__inline void atomic_increment( int volatile* val )
{
#if TARGET_WINDOWS
#if TARGET_IA32
    __asm mov ecx, val
    __asm lock inc dword ptr[ecx]
#else
    __asm mov rcx, val
    __asm lock inc qword ptr[rcx]
#endif /* TARGET_IA32 */
#else /* on TARGET_LINUX */
#if TARGET_INTEL64
    __asm__ volatile ("lock\n\tincq %0" : "=m"(*val) : "m"(*val) : "memory");
#else
    __asm__ volatile ("lock\n\tincl %0" : "=m"(*val) : "m"(*val) : "memory");
#endif
#endif
}

__inline int atomic_compare_and_swap( int volatile* loc, const int val, const int comp )
{
#if TARGET_WINDOWS
#if TARGET_INTEL64
#define CMPXCHG _InterlockedCompareExchange64
#else
#define CMPXCHG _InterlockedCompareExchange
#endif
    return CMPXCHG ( (void*)loc, val, comp );
#else /* if TARGET_LINUX */
#define CMPXCHG "cmpxchgl"
    int result;
    __asm__ __volatile__("lock\n\t" CMPXCHG " %2,%1"
                         : "=a"(result), "=m"(*(volatile int *)loc)
                         : "q"(val), "0"(comp), "m"(*(volatile int *)loc)
                         : "memory");
    return result;
#endif /* TARGET_WINDOWS */
}

__inline int try_lock_normal( int volatile* val )
{
    return atomic_compare_and_swap( val, 1, 0 )==0;
}

__inline void lock_normal( int volatile* val )
{
    if( !try_lock_normal(val) ) {
        int count = 1;
        do {
            exp_backoff( &count );
        } while ( !try_lock_normal( val ) );
    }
}

__inline void unlock_normal( int volatile* val )
{
    atomic_write( val, 0 );
}

static void do_movsb( char* dest, const char* src, int len )
{
#if _WIN32||_WIN64
#if defined(_M_X64)
	__asm mov  rsi, src
	__asm mov  rdi, dest
	__asm mov  ecx, len
	__asm rep movsb
#else
	__asm mov  esi, src
	__asm mov  edi, dest
	__asm mov  ecx, len
	__asm rep movsb
#endif
#else /* on Linux */
    __asm__ volatile ("rep movsb" :: "S"(src),"D"(dest),"c"(len) : "memory");
#endif
}

#define lockedIncInt32(loc) lockedXAddInt32((loc), 1)

__inline int32_t lockedXAddInt32( volatile int32_t* loc, int32_t addend )
{
#if TARGET_WINDOWS
#if TARGET_IA32
    __asm mov ecx, loc
    __asm mov eax, addend
    __asm lock xadd dword ptr[ecx], eax
#else /* TARGET_INTEL64 */
    __asm mov rcx, loc
    __asm mov eax, addend
    __asm lock xadd dword ptr[rcx], eax
#endif /* TARGET_IA32 */
#else /* TARGET_LINUX */
    volatile int32_t val = addend;
    __asm__ __volatile__ ("lock; xadd %0,%1"
                          : "=r" (val), "=m" (*loc)
                          : "0" (val), "m" (*loc)
                          : "memory"
                          ); 
   return val;
#endif
}

/* Sleep */
void test_sleep( int sec ) {
#if TARGET_WINDOWS
    Sleep( sec*1000 );
#else
    sleep( sec );
#endif
}

#endif /* __TEST_UTIL_H */
