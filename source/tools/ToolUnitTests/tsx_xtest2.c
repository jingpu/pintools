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
 * Copyright 2011-2012 Intel Corporation All Rights Reserved.
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
 * @ORIGINAL_AUTHOR: Wooyoung Kim
 */

/*
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "test_rtm.h"
#include "test_util.h"

#define INIT_FLAGS(Z) ( EFLAGS_CARRY | EFLAGS_PARITY | EFLAGS_AUX_CARRY |\
                        EFLAGS_SIGN  | EFLAGS_OVERFLOW | Z )

void set_eflags( int16_t z )
{
    int16_t f = INIT_FLAGS(z);
#if TARGET_LINUX
    __asm__ __volatile__ (
            "push (%0)\n"
            "popf\n" : : "r"(&f) : "memory" );
#elif (TARGET_WINDOWS)
    __writeeflags(z);
#endif
}

int16_t read_eflags()
{
    int16_t f = 0;
#if TARGET_LINUX
#  if TARGET_INTEL64
    int64_t tmp_f = 0;
    __asm__ __volatile__ ( "pushfq\n" "pop (%0)\n" : : "r"(&tmp_f) : "memory" );
#  else
    int32_t tmp_f = 0;
    __asm__ __volatile__ ( "pushf\n" "pop (%0)\n" : : "r"(&tmp_f) : "memory" );
#endif
    f = (int16_t)tmp_f;
#elif (TARGET_WINDOWS)
    int32_t tmp_f = 0;
    tmp_f = __readeflags();
    f = (int16_t)tmp_f;
#endif
    return f;
}








int main (int argc, char ** argv)
{
    int16_t curFlags;
    int retVal;
    __asm {
        xor eax, eax
        add eax, 1
    }
    emitXTEST()
    curFlags = __readeflags();
    if ( curFlags &EFLAGS_ZERO )
    {
        printf ("zf set\n");
        return (0);
    }
    else
    {
        printf ("***ERROR zf NOT set\n");
        return (1);
    }
}

