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
#ifdef _WIN32
#  include <mathimf.h>
#  ifndef NO_EMULATOR
#    include <windows.h>
#  endif
#endif

#if defined(__linux__)
#  include <stdlib.h>
#  include <string.h>
#endif
#if defined(_WIN32)
#  include <stdlib.h>
#  include <string.h>
#endif
 
#include <immintrin.h>
#include <stdio.h>
#include <math.h>

/* This is for DEBUG prints: */
#define PRINTF printf

void load_gsse()
{
#   if defined(_WIN32) && !defined(NO_EMULATOR)
    typedef int (*VERPROC)();
    HMODULE hModule;
    VERPROC pVerFunc;

    if ( !(hModule = LoadLibrary("niemudll.dll")) ){
        DWORD   errNum; 
        errNum = GetLastError();
        printf( "Emulator WAS NOT LOADED, ERROR CODE %X\n", errNum);
        exit(1);
    }
    pVerFunc = (VERPROC)GetProcAddress(hModule, "GetNiemuVersion");
    if(pVerFunc){
        int vN;
        vN = pVerFunc();
        printf( "Emulator version %d.%d\n", vN / 0x100, vN % 0x100);
    }
#   endif
}
/* ========================== */

#if defined(__GNUC__)
#  define ALIGN16  __attribute__ ((aligned(16)))
#else
#  define ALIGN16 __declspec(align(16))
#endif

typedef union {
    __m256d m256;
    __m256  ms;
    __m128d md[2];
    __m128 mi[2];
    signed char ch[32];
    unsigned char uch[32];
    signed short sh[16];
    unsigned short ush[16];
    int i[8];
    unsigned u[8];
    float f[8];
    long long l[4];
    double d[4];
} M256;

#define XMMa xmm2
#define XMMb xmm1
#define XMMc xmm7
#define XMMr xmm6

#define YMMa ymm2
#define YMMb ymm1
#define YMMc ymm7
#define YMMr ymm6

double const eps = 1.0e-6;
double const epsf = 1.0e-5;

void init_double(double x[], unsigned n, double s0)
{
    for(; n--; s0 = n - s0) x[n] = s0;
}

void init_float(float x[], unsigned n, float s0)
{
    for(; n--; s0 = n - s0) x[n] = s0;
}

void init_long(M256 *ptr, long value)
{
    ptr->l[0] = value;
    ptr->l[1] = value;
    ptr->l[2] = value;
    ptr->l[3] = value;
}

int gt_eps2(double x, double Eps)
{
    if(x < 0.0) x = -x;
    return x > Eps;
}
#define gt_eps(x) gt_eps2(x, eps)

int gt_eps3(double x, double y, double Eps)
{
    if(isnormal(x)) {
        if(isnormal(y)) return gt_eps2(x - y, Eps);
        return 1;
    }
    return isnormal(y);
}

void printVd(char *header, unsigned n, double vec[])
{
    unsigned i;
    printf(header);
    for(i = 0; i < n; i++){
        printf("\t%8g", vec[i]);
    }
    printf("\n");
}
void printVf(char *header, unsigned n, float vec[])
{
    unsigned i;
    printf(header);
    for(i = 0; i < n; i++){
        printf("\t%7g", vec[i]);
    }
    printf("\n");
}
void printVi(char *header, int vec[])
{
    unsigned i;
    printf("%s\t", header);
    for(i = 0; i < 8; i++){
        printf("%10x", vec[i]);
    }
    printf("\n");
}

void printVl(char *header, long long vec[])
{
    int i;
    printf("%s\t", header);
    for(i = 3; i >= 0; i--){
#ifdef _WIN32	
        printf("%18I64x", vec[i]);
#else
        printf("%18llx", vec[i]);
#endif
    }
    printf("\n");
}





