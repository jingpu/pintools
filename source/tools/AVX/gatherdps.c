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
#include "gsseemu.h"
static int res = 0;

static M256 old_dst, vind, mask, d, YMMDestBefore, YMMIndexBefore, YMMIndexAfter, YMMMaskBefore, YMMMaskAfter, expect;
static int scale;

static int arr[] = {0x12345678, 0x23456789, 0x076534af, 0x654234bc,
             0xf0367678, 0x82643618, 0x1e34b678, 0x1abcf6e8,
             0x19476678, 0x83356729, 0xf7f5f4ff, 0xe5e2e4ec,
             0xfb3c7a73, 0x8a6abc18, 0x1a3aba7a, 0x1aaca6e8};

char *ptr = (char *)arr;

#if defined(_M_X64) || defined(__x86_64__)
#define REG rax
#define ADDRPTR QWORD PTR
#else
#define REG eax
#define ADDRPTR DWORD PTR
#endif

void check_res(unsigned n)
{
    int i;
    for(i = 0; i < 8; i++){
        if(d.i[i] != expect.i[i]){
            printf("Case %d FAILED\n", n);
            printf("result[%d] %g, expected %g\n", i, d.f[i], expect.f[i]);
            printVf("old_dst:", 8, old_dst.f);
            printVi("vind:   ", vind.i);
            printVi("mask:   ", mask.i);
            printVf("expect:", 8, expect.f);
            printVf("d:     ", 8, d.f);
            printVl("expect_l:", expect.l);
            printVl("d_l:     ", d.l);
            printVl("mask_b_l:", YMMMaskBefore.l);
            printVl("mask_a_l:", YMMMaskAfter.l);
            res = 1;
            return;
        }
        if (YMMMaskAfter.i[i] != 0)  {
            printf("Failed: mask byte# %d expected 0 observed %x\n", i, YMMMaskAfter.i[i]);
            res = 1;
            return;
        }
    }
    PRINTF("Case %d passed\n", n);
}

int main()
{
    int i;

    init_double(old_dst.d, 4, 3.14);	/* Initialize memory and the registers */

    vind.i[0] = 0;
    vind.i[1] = 2;
    vind.i[2] = 3;
    vind.i[3] = 1;
    vind.i[4] = 7;
    vind.i[5] = 11;
    vind.i[6] = 13;
    vind.i[7] = 10;

    mask.i[0] = 0x80ffffff;
    mask.i[1] = 0x00ffffff;
    mask.i[2] = 0x00ffffff;
    mask.i[3] = 0x80ffffff;
    mask.i[4] = 0x80ffffff;
    mask.i[5] = 0x00ffffff;
    mask.i[6] = 0x80ffffff;
    mask.i[7] = 0x80ffffff;

    for (i = 0; i < 8; i++) {
        expect.f[i] = (mask.i[i] & 0x80000000) ? *(float *)(ptr+(vind.i[i] * 4 + 0))
                                               : old_dst.f[i];
    }

    __asm {     /* VGATHERDPS ymm1, [rax + ymm2_vind*4], ymm3_mask */
        lea REG, ADDRPTR [arr]
        vmovups YMMa, [old_dst.ms];
        vmovups YMMb, [vind.ms];
        vmovups YMMc, [mask.ms];
        vmovups [YMMDestBefore.ms],  YMMa;
        vmovups [YMMIndexBefore.ms], YMMb;
        vmovups [YMMMaskBefore.ms],  YMMc;
        vgatherdps YMMa, [REG + YMMb*4], YMMc
        vmovups [d.ms], YMMa;
        vmovups [YMMIndexAfter.ms], YMMb;
        vmovups [YMMMaskAfter.ms],  YMMc;
    }
    printVl("YMM dest  before:     ", YMMDestBefore.l);
    printVl("YMM dest  after:      ", d.l);
    printVl("YMM index before:     ", YMMIndexBefore.l);
    printVl("YMM index after:      ", YMMIndexAfter.l);
    printVl("YMM mask  before:     ", YMMMaskBefore.l);
    printVl("YMM mask  after:      ", YMMMaskAfter.l);
    check_res(1);

    for (i = 4; i < 8; i++) {
        expect.f[i] = 0;
    }
    __asm {     /* VGATHERDPS xmm1, [rax + xmm2_vind*4], xmm3_mask */
        lea REG, ADDRPTR [arr]
        vmovups YMMa, [old_dst.ms];
        vmovups YMMb, [vind.ms];
        vmovups YMMc, [mask.ms];
        vmovups [YMMDestBefore.ms],  YMMa;
        vmovups [YMMIndexBefore.ms], YMMb;
        vmovups [YMMMaskBefore.ms],  YMMc;
        vgatherdps XMMa, [REG + XMMb*4], XMMc
        vmovups [d.ms], YMMa;
        vmovups [YMMIndexAfter.ms], YMMb;
        vmovups [YMMMaskAfter.ms],  YMMc;
    }
    printVl("YMM dest  before:     ", YMMDestBefore.l);
    printVl("YMM dest  after:      ", d.l);
    printVl("YMM index before:     ", YMMIndexBefore.l);
    printVl("YMM index after:      ", YMMIndexAfter.l);
    printVl("YMM mask  before:     ", YMMMaskBefore.l);
    printVl("YMM mask  after:      ", YMMMaskAfter.l);
    check_res(2);

    for (i = 0; i < 8; i++) {
        expect.f[i] = (mask.i[i] & 0x80000000) ? *(float *)(ptr+(vind.i[i] * 4 + 8))
                                               : old_dst.f[i];
    }
    __asm {     /* VGATHERDPS ymm1, [rax + ymm2_vind*4 + 8], ymm3_mask */
        lea REG, ADDRPTR [arr]
        vmovups YMMa, [old_dst.ms];
        vmovups YMMb, [vind.ms];
        vmovups YMMc, [mask.ms];
        vmovups [YMMDestBefore.ms],  YMMa;
        vmovups [YMMIndexBefore.ms], YMMb;
        vmovups [YMMMaskBefore.ms],  YMMc;
        vgatherdps YMMa, [REG + YMMb*4 + 8], YMMc
        vmovups [d.ms], YMMa;
        vmovups [YMMIndexAfter.ms], YMMb;
        vmovups [YMMMaskAfter.ms],  YMMc;
    }
    printVl("YMM dest  before:     ", YMMDestBefore.l);
    printVl("YMM dest  after:      ", d.l);
    printVl("YMM index before:     ", YMMIndexBefore.l);
    printVl("YMM index after:      ", YMMIndexAfter.l);
    printVl("YMM mask  before:     ", YMMMaskBefore.l);
    printVl("YMM mask  after:      ", YMMMaskAfter.l);
    check_res(3);

    for (i = 4; i < 8; i++) {
        expect.f[i] = 0;
    }
    __asm {     /* VGATHERDPS xmm1, [rax + xmm2_vind*4 + 8], xmm3_mask */
        lea REG, ADDRPTR [arr]
        vmovups YMMa, [old_dst.ms];
        vmovups YMMb, [vind.ms];
        vmovups YMMc, [mask.ms];
        vmovups [YMMDestBefore.ms],  YMMa;
        vmovups [YMMIndexBefore.ms], YMMb;
        vmovups [YMMMaskBefore.ms],  YMMc;
        vgatherdps XMMa, [REG + XMMb*4 + 8], XMMc
        vmovups [d.ms], YMMa;
        vmovups [YMMIndexAfter.ms], YMMb;
        vmovups [YMMMaskAfter.ms],  YMMc;
    }
    printVl("YMM dest  before:     ", YMMDestBefore.l);
    printVl("YMM dest  after:      ", d.l);
    printVl("YMM index before:     ", YMMIndexBefore.l);
    printVl("YMM index after:      ", YMMIndexAfter.l);
    printVl("YMM mask  before:     ", YMMMaskBefore.l);
    printVl("YMM mask  after:      ", YMMMaskAfter.l);
    check_res(4);

    if(!res) PRINTF("gatherdps passed\n");
    return res;
}
