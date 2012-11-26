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
#if defined(TARGET_WINDOWS)
#include "windows.h"
#define EXPORT_CSYM extern "C" __declspec( dllexport )
#else
#include<stdlib.h>
#define EXPORT_CSYM extern "C" 
#endif
#include <string.h>
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
void AddToXmmRegs ();



#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_a ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_b ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_c ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_d ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_e ();
#if defined(__cplusplus)
extern "C"
void Fld1Fstp_f1 ();
#endif
#if defined(__cplusplus)
extern "C"
void Fld1Fstp_f2 ();
#endif
#if defined(__cplusplus)
extern "C"
void Fld1Fstp_f ();
#endif
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_g ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_h ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_i ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_j ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_k ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_l ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_l1 ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_l2 ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_m (void (*pt2Function)());
#if defined(__cplusplus)
extern "C"
#endif
void Fld1Fstp_n (void (*pt2Function)());
#if defined(__cplusplus)
extern "C"
#endif
void Fld1_aa ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1_ab ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1_ac ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1_ad ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1_ae ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1_af ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1_ag ();
#if defined(__cplusplus)
extern "C"
#endif
unsigned int  GetFlags ();
extern "C" void SetFlags ();
#if defined(__cplusplus)
extern "C"
#endif
void Fstp3 ();
#if defined(__cplusplus)
extern "C"
#endif
void Fld1FstpSetXmmsMaskMxcsr ();


#if defined(__cplusplus)
extern "C"
#endif
void IntScratchFld1Fstp_a();

#if defined(__cplusplus)
extern "C"
#endif
void IntScratchFld1Fstp_b();

#if defined(__cplusplus)
extern "C"
#endif
void IntScratchFld1Fstp_c();

#if defined(__cplusplus)
extern "C"
#endif
void IntScratchFld1Fstp_d();



#if defined(__cplusplus)
extern "C"
#endif
void MaskZeroDivideInMxcsr();

#if defined(__cplusplus)
extern "C"
#endif
void UnMaskZeroDivideInMxcsr();



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

typedef unsigned __int8 UINT8 ;
typedef unsigned __int16 UINT16;
typedef unsigned __int32 UINT32;
typedef unsigned __int64 UINT64;


#define ALIGN16 __declspec(align(16))
#define ALIGN8  __declspec(align(8))

#else
#error Expect usage of either GNU or MS compiler.
#endif

#if defined(__cplusplus)
extern "C"
#endif
UINT64 GetMxcsr();

#define MAX_BYTES_PER_XMM_REG 16
#define MAX_WORDS_PER_XMM_REG (MAX_BYTES_PER_XMM_REG/2)
#define MAX_DWORDS_PER_XMM_REG (MAX_WORDS_PER_XMM_REG/2)
#define MAX_QWORDS_PER_XMM_REG (MAX_DWORDS_PER_XMM_REG/2)
#define MAX_FLOATS_PER_XMM_REG (MAX_BYTES_PER_XMM_REG/sizeof(float))
#define MAX_DOUBLES_PER_XMM_REG (MAX_BYTES_PER_XMM_REG/sizeof(double))

union ALIGN16 xmm_reg_t
{
    UINT8  byte[MAX_BYTES_PER_XMM_REG];
    UINT16 word[MAX_WORDS_PER_XMM_REG];
    UINT32 dword[MAX_DWORDS_PER_XMM_REG];
    UINT64 qword[MAX_QWORDS_PER_XMM_REG];

    INT8   s_byte[MAX_BYTES_PER_XMM_REG];
    INT16  s_word[MAX_WORDS_PER_XMM_REG];
    INT32  s_dword[MAX_DWORDS_PER_XMM_REG];
    INT64  s_qword[MAX_QWORDS_PER_XMM_REG];

    float  flt[MAX_FLOATS_PER_XMM_REG];
    double dbl[MAX_DOUBLES_PER_XMM_REG];

};



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


extern "C" void mmx_save (char* ptr);
extern "C" void mmx_restore (char* ptr);




extern "C" reg_t get_gax();
extern "C" reg_t get_gbx();
extern "C" reg_t get_gcx();
extern "C" reg_t get_gdx();
extern "C" reg_t get_gdi();
extern "C" reg_t get_gsi();
extern "C" reg_t get_gbp();
extern "C" void set_gax(reg_t regVal);
extern "C" void set_gbx(reg_t regVal);
extern "C" void set_gcx(reg_t regVal);
extern "C" void set_gdx(reg_t regVal);
extern "C" void set_gdi(reg_t regVal);
extern "C" void set_gsi(reg_t regVal);
extern "C" void set_gbp(reg_t regVal);
#if defined(TARGET_IA32E)
extern "C" reg_t get_r8();
extern "C" reg_t get_r9();
extern "C" reg_t get_r10();
extern "C" reg_t get_r11();
extern "C" reg_t get_r12();
extern "C" reg_t get_r13();
extern "C" reg_t get_r14();
extern "C" reg_t get_r15();
extern "C" void set_r8(reg_t regVal);
extern "C" void set_r9(reg_t regVal);
extern "C" void set_r10(reg_t regVal);
extern "C" void set_r11(reg_t regVal);
extern "C" void set_r12(reg_t regVal);
extern "C" void set_r13(reg_t regVal);
extern "C" void set_r14(reg_t regVal);
extern "C" void set_r15(reg_t regVal);
#endif

#if defined(__GNUC__)
#include <stdint.h>
static void get_xmm_regA(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm0,%0" : "=m" (xmm_reg)  );
}

static void set_xmm_reg0(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm0" :  : "m" (xmm_reg) : "%xmm0"  );
} 

static void get_xmm_reg0(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm0,%0" : "=m" (xmm_reg)  );
}


static void set_xmm_reg1(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm1" :  : "m" (xmm_reg) : "%xmm1"  );
} 

static void get_xmm_reg1(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm1, %0" : "=m" (xmm_reg)  );
}



static void set_xmm_reg2(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm2" :  : "m" (xmm_reg) : "%xmm2"  );
} 

static void get_xmm_reg2(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm2,%0" : "=m" (xmm_reg)  );
}

static void set_xmm_reg3(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm3" :  : "m" (xmm_reg) : "%xmm3"  );
} 

static void get_xmm_reg3(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm3,%0" : "=m" (xmm_reg)  );
}

static void set_xmm_reg4(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm4" :  : "m" (xmm_reg) : "%xmm4"  );
} 

static void get_xmm_reg4(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm4,%0" : "=m" (xmm_reg)  );
}

static void set_xmm_reg5(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm5" :  : "m" (xmm_reg) : "%xmm5"  );
} 

static void get_xmm_reg5(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm5,%0" : "=m" (xmm_reg)  );
}

static void set_xmm_reg6(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm6" :  : "m" (xmm_reg) : "%xmm6"  );
} 

static void get_xmm_reg6(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm6,%0" : "=m" (xmm_reg)  );
}

static void set_xmm_reg7(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm7" :  : "m" (xmm_reg) : "%xmm7"  );
} 

static void get_xmm_reg7(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm7,%0" : "=m" (xmm_reg)  );
}
#ifdef TARGET_IA32E
static void get_xmm_reg8(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm8,%0" : "=m" (xmm_reg)  );
}


static void get_xmm_reg9(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm9,%0" : "=m" (xmm_reg)  );
}

static void get_xmm_reg10(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm10,%0" : "=m" (xmm_reg)  );
}

static void get_xmm_reg11(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm11,%0" : "=m" (xmm_reg)  );
}

static void get_xmm_reg12(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm12,%0" : "=m" (xmm_reg)  );
}

static void get_xmm_reg13(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm13,%0" : "=m" (xmm_reg)  );
}

static void get_xmm_reg14(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm14,%0" : "=m" (xmm_reg)  );
}

static void get_xmm_reg15(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %%xmm15,%0" : "=m" (xmm_reg)  );
}

static void set_xmm_reg8(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm8" :  : "m" (xmm_reg) : "%xmm8"  );
}

static void set_xmm_reg9(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm9" :  : "m" (xmm_reg) : "%xmm9"  );
}

static void set_xmm_reg10(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm10" :  : "m" (xmm_reg) : "%xmm10"  );
}

static void set_xmm_reg11(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm11" :  : "m" (xmm_reg) : "%xmm11"  );
}

static void set_xmm_reg12(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm12" :  : "m" (xmm_reg) : "%xmm12"  );
}

static void set_xmm_reg13(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm13" :  : "m" (xmm_reg) : "%xmm13"  );
}

static void set_xmm_reg14(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm14" :  : "m" (xmm_reg) : "%xmm14"  );
}

static void set_xmm_reg15(xmm_reg_t& xmm_reg)
{
    asm volatile("movdqu %0, %%xmm15" :  : "m" (xmm_reg) : "%xmm15"  );
}
#endif

#else
extern "C" void set_xmm_reg0(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg0(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg1(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg1(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg2(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg2(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg3(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg3(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg4(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg4(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg5(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg5(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg6(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg6(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg7(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg7(xmm_reg_t& xmm_reg);
#ifdef TARGET_IA32E
extern "C" void set_xmm_reg8(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg8(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg9(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg9(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg10(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg10(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg11(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg11(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg12(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg12(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg13(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg13(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg14(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg14(xmm_reg_t& xmm_reg);
extern "C" void set_xmm_reg15(xmm_reg_t& xmm_reg);
extern "C" void get_xmm_reg15(xmm_reg_t& xmm_reg);

#endif
#endif




static void
set_xmm_reg(xmm_reg_t& xmm_reg, UINT32 reg_no)
{

    switch (reg_no)
    {
    case 0:
        set_xmm_reg0(xmm_reg);
        break;
    case 1:
        set_xmm_reg1(xmm_reg);
        break;
    case 2:
        set_xmm_reg2(xmm_reg);
        break;
    case 3:
        set_xmm_reg3(xmm_reg);
        break;
    case 4:
        set_xmm_reg4(xmm_reg);
        break;
    case 5:
        set_xmm_reg5(xmm_reg);
        break;
    case 6:
        set_xmm_reg6(xmm_reg);
        break;
    case 7:
        set_xmm_reg7(xmm_reg);
        break;
#ifdef TARGET_IA32E
    case 8:
        set_xmm_reg8(xmm_reg);
        break;
    case 9:
        set_xmm_reg9(xmm_reg);
        break;
    case 10:
        set_xmm_reg10(xmm_reg);
        break;
    case 11:
        set_xmm_reg11(xmm_reg);
        break;
    case 12:
        set_xmm_reg12(xmm_reg);
        break;
    case 13:
        set_xmm_reg13(xmm_reg);
        break;
    case 14:
        set_xmm_reg14(xmm_reg);
        break;
    case 15:
        set_xmm_reg15(xmm_reg);
        break;
#endif
    }

} 
static void
get_xmm_reg(xmm_reg_t& xmm_reg, UINT32 reg_no)
{
    switch (reg_no)
    {
    case 0:
       get_xmm_reg0(xmm_reg);
       break;
    case 1:
        get_xmm_reg1(xmm_reg);
        break;
    case 2:
        get_xmm_reg2(xmm_reg);
        break;
    case 3:
        get_xmm_reg3(xmm_reg);
        break;
    case 4:
        get_xmm_reg4(xmm_reg);
        break;
    case 5:
        get_xmm_reg5(xmm_reg);
        break;
    case 6:
        get_xmm_reg6(xmm_reg);
        break;
    case 7:
        get_xmm_reg7(xmm_reg);
        break;
#ifdef TARGET_IA32E
    case 8:
        get_xmm_reg8(xmm_reg);
        break;
    case 9:
        get_xmm_reg9(xmm_reg);
        break;
    case 10:
        get_xmm_reg10(xmm_reg);
        break;
    case 11:
        get_xmm_reg11(xmm_reg);
        break;
    case 12:
        get_xmm_reg12(xmm_reg);
        break;
    case 13:
        get_xmm_reg13(xmm_reg);
        break;
    case 14:
        get_xmm_reg14(xmm_reg);
        break;
    case 15:
        get_xmm_reg15(xmm_reg);
        break;
#endif
    }

}
void write_xmm_reg(UINT32 reg_no, UINT32 val)
{

    xmm_reg_t xmm;
    xmm.dword[0] = val;
    xmm.dword[1] = val;
    xmm.dword[2] = val;
    xmm.dword[3] = val;
    
    set_xmm_reg(xmm, reg_no); 
}

void read_xmm_reg(UINT32 reg_no, xmm_reg_t& xmm)
{

    xmm.dword[0] = 0;
    xmm.dword[1] = 0;
    xmm.dword[2] = 0;
    xmm.dword[3] = 0;
    
    get_xmm_reg(xmm, reg_no); 
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

EXPORT_CSYM void  TestIargPreserveInProbed()
{
}

EXPORT_CSYM void  TestIargPreserveInProbed1()
{
}

EXPORT_CSYM void  TestIargPreserveInProbed2()
{
}




struct XSAVE_HEADER
{
    UINT64 _mask;
    UINT64 _reserved[7];
};

/*!
 * An 80-bit X87 data register padded out to 128-bits.
 */
union /*<POD>*/ X87REG_PADDED
{
    struct
    {
        UINT64 _significand;  ///< The floating-point significand.
        UINT16 _exponent;     ///< The floating-point exponent, top bit is the sign bit.
        UINT16 _pad[3];
    } _fp;
    struct
    {
        UINT64 _lo;           ///< Least significant part of value.
        UINT64 _hi;           ///< Most significant part of value.
    } _raw;
};

/*!
 * A 128-bit XMM register value.
 */
union /*<POD>*/ XMMREG
{
    UINT8 _vec8[16];      ///< Vector of 16 8-bit elements.
    UINT16 _vec16[8];     ///< Vector of 8 16-bit elements.
    UINT32 _vec32[4];     ///< Vector of 4 32-bit elements.
    UINT64 _vec64[2];     ///< Vector of 2 64-bit elements.
};

/*!
 * The memory format written by the FXSAVE instruction for IA32.
 */
struct /*<POD>*/ FXSAVE
{
    UINT16 _fcw;          ///< X87 control word.
    UINT16 _fsw;          ///< X87 status word.
    UINT8 _ftw;           ///< Abridged X87 tag value.
    UINT8 _pad1;
    UINT16 _fop;          ///< Last X87 non-control instruction opcode.
    UINT32 _fpuip;        ///< Last X87 non-control instruction address.
    UINT16 _cs;           ///< Last X87 non-control instruction CS selector.
    UINT16 _pad2;
    UINT32 _fpudp;        ///< Last X87 non-control instruction operand address.
    UINT16 _ds;           ///< Last X87 non-control instruction operand DS selector.
    UINT16 _pad3;
    UINT32 _mxcsr;        ///< MXCSR control and status register.
    UINT32 _mxcsrmask;    ///< Mask of valid MXCSR bits.
    X87REG_PADDED _sts[8];      ///< X87 data registers in top-of-stack order.
    XMMREG _xmms[8];            ///< XMM registers.
    UINT8 _pad4[224];
};
struct FPSTATE
{
    // fxsave_legacy is applicable on all IA-32 and Intel(R) 64
    // processors
    FXSAVE fxsave_legacy;
    // the following are only applicable on processors that support XSAVE
    struct XSTATE
    {
        XSAVE_HEADER _extendedHeader;
        UINT8  _ymmUpper[16*16];
    }_xstate;
};

#if defined(__cplusplus)
extern "C"
#endif
void XRstorHelper(FPSTATE *fpVerboseContext);
#if defined(__cplusplus)
extern "C"
#endif
void XSaveHelper1(FPSTATE *fpVerboseContext);
#if defined(__cplusplus)
extern "C"
#endif
void XSaveHelper2(FPSTATE *fpVerboseContext);

#if defined(__cplusplus)
extern "C"
#endif
void FldzToTop3();


#if defined(__cplusplus)
extern "C"
#endif
void Fld2tToTop3a();

typedef  UINT64 ADDRINT;

int main()
{  
    // to enable the tool to identify the xsave and xrstor instructions it wants to emulate
	printf ("app writes log2(10) into first three x87 regs\n"); fflush (stdout);
	Fld2tToTop3a();
	
	unsigned char fpContext[sizeof (FPSTATE)+ 64];
	memset (fpContext, 0, sizeof (FPSTATE)+ 64);
	FPSTATE *fpVerboseContext= 
		reinterpret_cast<FPSTATE *>
		(( reinterpret_cast<ADDRINT>(fpContext) + (64 - 1)) & (-1*64));
	unsigned char fpContext1[sizeof (FPSTATE)+ 64];
	memset (fpContext1, 0, sizeof (FPSTATE)+ 64);
	FPSTATE *fpVerboseContext1= 
		reinterpret_cast<FPSTATE *>
		(( reinterpret_cast<ADDRINT>(fpContext1) + (64 - 1)) & (-1*64));

	printf ("app calls first xsave into buffer %p\n", fpVerboseContext); fflush (stdout);
	XSaveHelper1 (fpVerboseContext);  // tool does not emulate this
		
	printf ("app x87 reg values from buffer\n"); fflush (stdout);	
	int i;
	for (i=0; i< 8; i++)
	{
		printf ("app fpVerboseContext->fxsave_legacy._sts[%d]: %p %p \n", i, fpVerboseContext->fxsave_legacy._sts[i]._raw._lo, 
				fpVerboseContext->fxsave_legacy._sts[i]._raw._hi); fflush (stdout);
	}
	printf ("app _ftw value from buffer %x\n", fpVerboseContext->fxsave_legacy._ftw); fflush (stdout);	

	printf ("app x87 writes 1.0 into all x87 regs in buffer\n"); fflush (stdout);
	for (i=0; i< 8; i++)
	{
		fpVerboseContext->fxsave_legacy._sts[i]._raw._lo = 0x80000000;
	        fpVerboseContext->fxsave_legacy._sts[i]._raw._lo =   
	            fpVerboseContext->fxsave_legacy._sts[i]._raw._lo <<32;   
		fpVerboseContext->fxsave_legacy._sts[i]._raw._hi = 0x0000000000003fff;
	}
	fpVerboseContext->fxsave_legacy._ftw = 0xac;

	printf ("app calls xrstor from buffer %p\n", fpVerboseContext); fflush (stdout);
	XRstorHelper (fpVerboseContext);  // tool emulates this xrstor and can change the values in the first 3 X87 regs to 0
	                                  // if the -set_in_xrstor is specified to the tool
		
	XSaveHelper2 (fpVerboseContext1);  // tool emulates this xsave

	printf ("app x87 reg values from buffer\n"); fflush (stdout);
	for (i=0; i< 8; i++)
	{
		printf ("app fpVerboseContext->fxsave_legacy._sts[%d]: %p %p \n", i, fpVerboseContext1->fxsave_legacy._sts[i]._raw._lo, 
				fpVerboseContext1->fxsave_legacy._sts[i]._raw._hi); fflush (stdout);
		if (fpVerboseContext->fxsave_legacy._sts[i]._raw._lo&0xffffffff != 0 
		    || (fpVerboseContext->fxsave_legacy._sts[i]._raw._lo>>32) != 0x80000000
		    || fpVerboseContext->fxsave_legacy._sts[i]._raw._hi != 0x0000000000003fff)
		{
			printf ("***Error in expected x87 value\n"); fflush (stdout);
			return (-1);
		}
	}
	printf ("app _ftw value from buffer %x\n", fpVerboseContext->fxsave_legacy._ftw); fflush (stdout);	
	if (fpVerboseContext1->fxsave_legacy._ftw != 0xac)
	{
		printf ("***Error in expected ftw value\n"); fflush (stdout);
	    return (-1);
	}
	
	return (0);


}

