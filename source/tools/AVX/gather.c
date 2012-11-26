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
#include "gather.h"
#include "gsseemu.h"

__int32 arr[8] = {1,2,3,4,5,6,7,8};
__int64 vind[4] = {0,1,2,3};
int mask[8] = {0xFFFFFFFF, 0, 0xFFFFFFFF, 0, 0xFFFFFFFF, 0, 0xFFFFFFFF, 0};

__int32 expected[8] = {1,0,3,0, 0,0,0,0};

static M256 d, YMMDestBefore, YMMIndexBefore, YMMIndexAfter, YMMMaskBefore, YMMMaskAfter;

int main()
{
   int i;

   init_long(&d, 0xdeadbeef);
    __asm {     /* VGATHERDPS ymm1, [rax + ymm2_vind*4], ymm3_mask */
        lea GPR, QWORD PTR [arr]
        vxorps  ymm1, ymm1, ymm1;
        vmovups ymm2, [vind];
        vmovups ymm3, [mask];
        vmovups [YMMDestBefore.ms],  ymm1;
        vmovups [YMMIndexBefore.ms], ymm2;
        vmovups [YMMMaskBefore.ms],  ymm3;
        vgatherqps xmm1, [GPR + ymm2*4], xmm3
        vmovups [d], ymm1;
        vmovups [YMMIndexAfter.ms], ymm2;
        vmovups [YMMMaskAfter.ms],  ymm3;
    }
    printVl("YMM dest  before:     ", YMMDestBefore.l);
    printVl("YMM dest  after:      ", d.l);
    printVl("YMM index before:     ", YMMIndexBefore.l);
    printVl("YMM index after:      ", YMMIndexAfter.l);
    printVl("YMM mask  before:     ", YMMMaskBefore.l);
    printVl("YMM mask  after:      ", YMMMaskAfter.l);

        
  for (i=0; i < 8; i++) {
      if (d.i[i] != expected[i])  {
          printf("Failed: element %d expected %d observed %d\n", i, expected[i], d.i[i]);
          return 1;
      }
      if (YMMMaskAfter.i[i] != 0)  {
          printf("Failed: mask byte# %d expected 0 observed %x\n", i, YMMMaskAfter.i[i]);
          return 1;
      }
  }
  printf("PASSED\n");
  return 0;
}
