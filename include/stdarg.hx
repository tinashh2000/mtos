/**
*** Copyright (C) 1985-2014 Intel Corporation.  All rights reserved.
***
*** The information and source code contained herein is the exclusive
*** property of Intel Corporation and may not be disclosed, examined
*** or reproduced in whole or in part without explicit written authorization
*** from the company.
***
**/
/*===---- stdarg.h - Variable argument handling ----------------------------===
 *
 * Copyright (c) 2008 Eli Friedman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *===-----------------------------------------------------------------------===
 */
#ifndef _INC_STDARG
#define _INC_STDARG

#if defined(_WIN32)
/*
 * stdarg.h
 *
 * Replacement header for standard stdarg.h
 *
 * This replacement is necessary to support the 16 byte
 * aligned parameters.
 *
 * 18 Sept 1997 [kbs]
 */


#include "STDDEF.H"

#ifdef __INTEL_COMPILER
#define __builtin_alignof(t) __ALIGNOF__(t)
#else
#define __builtin_alignof(t) (4)
#endif

/*
 * The following macro computes the size actually occupied in
 * the parameter block by a parameter of the same type as t.
 * All parameter sizes are really multiples of int size in a
 * parameter block.
 */
#define _PARMSIZE(t) \
    ((sizeof(t) + (sizeof(int)-1)) & ~(sizeof(int) -1))

/*
 * The following macro computes the alignment in the parameter block
 * of a parameter of type t.  Any type that doesn't require 16 byte
 * alignment, only gets 4 byte alignment.
 */
#define _PARMALIGN(t) \
    (__builtin_alignof(t) < 32 ? __builtin_alignof(t) < 16 ? 4 : 16 : 32)

/*
 * The following macro computes the base address of a parameter of type
 * t given the address of the first byte after the previous parameter.
 */
#define _PARMADDR(fb_addr,t) \
    ((char *)((((int)fb_addr) + (_PARMALIGN(t)-1)) & ~(_PARMALIGN(t)-1)))

/*
 * The following macro computes the address of a parameter.
 * We use reinterpret_cast for C++ compilation in order to not depend
 * on a user-specified operator&().
 */
#ifdef  __cplusplus
#define _ADDROFVAR(t)   (&reinterpret_cast<const char &>(t))
#else
#define _ADDROFVAR(t)   (&(t))
#endif

typedef char * va_list;

#ifdef __INTEL_CHKP_ENABLED
#define va_start(ap,anchor) \
    ((ap)  = (va_list)__chkp_kill_bounds((va_list)_ADDROFVAR(anchor) + \
             _PARMSIZE(anchor)))
#else
#define va_start(ap,anchor) \
    ((ap)  = (va_list)_ADDROFVAR(anchor) + _PARMSIZE(anchor))
#endif

#define va_arg(ap,t) \
    (*((t *)((ap = (va_list)(_PARMADDR(ap,t) + _PARMSIZE(t))) - \
                   _PARMSIZE(t))))

#define va_end(ap) \
    ( ap = 0 )

#else // !defined(WIN32)
#ifndef __STDARG_H
#define __STDARG_H

#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap)          __builtin_va_end(ap)
#define va_arg(ap, type)    __builtin_va_arg(ap, type)

/* GCC always defines __va_copy, but does not define va_copy unless in c99 mode
 * or -ansi is not specified, since it was not part of C90.
 */
#define __va_copy(d,s) __builtin_va_copy(d,s)

#if !defined(__STRICT_ANSI__) || __STDC_VERSION__ + 0 >= 199900L || defined(__GXX_EXPERIMENTAL_CXX0X__) 
#define va_copy(dest, src)  __builtin_va_copy(dest, src)
#endif

/* Hack required to make standard headers work, at least on Ubuntu */
#define __GNUC_VA_LIST 1
typedef __builtin_va_list __gnuc_va_list;

#endif // __STDARG_H
#endif // !(defined(_WIN32) || defined(_WIN64))
#endif // _INC_STDARG
