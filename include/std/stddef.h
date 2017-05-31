#pragma once

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define true 1
#define false 0
#define TRUE 1
#define FALSE 0

#define	ADDPTR(p,sz) (((char*)p) + sz)
typedef unsigned long 		u_long;
typedef unsigned int 		u_int;
typedef unsigned short 		u_short;
typedef unsigned char 		u_char;

typedef unsigned long 		ulong;
typedef unsigned short 		ushort;
typedef unsigned int 		uint;
typedef unsigned char		unchar;



#ifndef _WINT_T_DEFINED
#define _WINT_T_DEFINED
typedef unsigned short wint_t;
#endif /* _WINT_T_DEFINED */

#ifndef __cplusplus
typedef unsigned short int wchar_t;
#endif // wchar_t


typedef short int SHORT;
typedef int INT;
typedef long LONG;

typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned long ULONG;

#if defined(__clang__) || defined(__llvm__)
	#define __int64 long long
#elif defined(__GNUC__)
	#define __int64 long long
#elif defined(_MSC_VER)
//	typedef long long __int64;
	#define __int64 long long
#endif

typedef unsigned __int64 ULONGLONG, FILETIME, uint64; //, uint64_t;
typedef __int64 LONGLONG, QWORD;

typedef char int8;
typedef short int16;
typedef int int32;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

enum
{
	BooleanType,
	IntegerType,
	FloatingPointType,
	StringType,
};

typedef DWORD COLORREF;
typedef float	FLOAT;
typedef double	DOUBLE;

#ifndef NULL
//#define NULL    ((void *)0)
#define NULL    0
#endif

#define NONE 0

#ifndef _STDDEF_H
#define _STDDEF_H

#ifndef offsetof
#define offsetof(ty,m)  ((size_t)&(((ty*)0)->m))
#endif

/* type definitions */
#ifndef _PTRDIFF_T_DEFINED
#define _PTRDIFF_T_DEFINED
#ifdef BITS64
typedef long long ptrdiff_t;
#else
typedef int ptrdiff_t;
#endif
#endif /* _PTRDIFF_T_DEFINED */

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#ifdef BITS64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif
#endif /* _SIZE_T_DEFINED */

/* bounds-checking interfaces (TR24731-1, C11 annex K) */
#if __STDC_WANT_LIB_EXT1__

#ifndef _RSIZE_T_DEFINED
#define _RSIZE_T_DEFINED
#if __POCC_TARGET__ == 3
typedef unsigned long long rsize_t;
#else
typedef unsigned int rsize_t;
#endif
#endif /* _RSIZE_T_DEFINED */

#endif /* __STDC_WANT_LIB_EXT1__ */

#include <stdint.h>
#endif /* _STDDEF_H */
