#pragma once

#ifndef _MTOX_COMMON_
#define _MTOX_COMMON_

#if defined(__clang__) || defined (__LLVM__)
//#pragma message("Clang")
	#define __CDECL 	__cdecl
	#define __STDCALL   __stdcall
	#define __FASTCALL  __fastcall
#elif defined(__GNUC__)
//#pragma message("GCC")
    #define __CDECL     __attribute__((cdecl))
    #define __STDCALL   __attribute__((stdcall))
    #define __FASTCALL   __attribute__((fastcall))
#else
	#define __CDECL 	__cdecl
	#define __STDCALL   __stdcall
	#define __FASTCALL  __fastcall
#endif


#define _QSORTCALL	__cdecl

//#define conc(str1, str2) __FILE__ ## #__LINE__

#define yxstr(s) ystr(s)
#define ystr(s) #s
#define STRINGIFY(x) #x
#define LockConC  __FILE__ ":" yxstr(__LINE__)
//__FILE__ ":" STRINGIFY(__LINE__)

typedef int (_QSORTCALL *QSORTPROC)(const void *,const void *);

#define I386

//#define __int64 long long
#define MIN_PAGE_SIZE   4096

typedef char CHAR;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int UINT;

typedef CHAR*       CHARPTR,STRPTR;
typedef BYTE*		BYTEPTR;
typedef void*		MEMPTR;
typedef unsigned int UCHR;
typedef unsigned long DWORD;
#include <stddef.h>

typedef wchar_t WCHAR;
typedef WCHAR*      WCHARPTR,WSTRPTR;


#define BYTEPTR(addr) ((CHARPTR) addr)

#define WC(str) (wchar_t *) L##str
#define WCH(str)(wchar_t) L##str
//#define _WC L

/*
INTx and UINTx are normally used for numbers
Other values representing other forms of data should use the WORDx values.
*/

typedef void        VOID;

/*
typedef signed char			INT8;
typedef signed short int	INT16;
typedef signed int			INT32;
typedef signed long long    INT64;

typedef unsigned char			UINT8;
typedef unsigned short int		UINT16;
typedef unsigned int           UINT32;
typedef unsigned long long      UINT64;
*/

typedef unsigned char       WORD8;
typedef unsigned short int  WORD16;
typedef unsigned int        WORD32;
typedef unsigned long long  WORD64;

typedef signed char INT8,*PINT8;
typedef signed short INT16,*PINT16;
typedef signed int INT32,*PINT32;
typedef signed __int64 INT64,*PINT64;
typedef unsigned char UINT8,*PUINT8;
typedef unsigned short UINT16,*PUINT16;
typedef unsigned int UINT32,*PUINT32;
typedef unsigned __int64 UINT64,*PUINT64;
typedef signed int LONG32,*PLONG32;
typedef unsigned int ULONG32,*PULONG32;
typedef unsigned int DWORD32,*PDWORD32;
  
/*
MWORD is the quantity that is large enough to represent the native CPU word size. INTX and UINTX are large enough to represent a numeric value which equals
the native CPU word size.
*/

#ifdef BITS64
	typedef	WORD64	MWORD;
	typedef INT64	INTX;
#else
	typedef unsigned int	MWORD;
	typedef int				INTX;
#endif

typedef int	BOOL;

#define MAX_SIGNED  ((MWORD)-1 & ~(1 << (sizeof (MWORD) * 8 - 1)))

typedef UINT64	DATETIME_S;

#define TF(c) c ? TRUE:FALSE

#ifdef __cplusplus

#define EXPORT extern "C"
#define IMPORT extern "C"
#define EXPORTSTART extern "C" {
#define EXPORTEND };

#define IMPORTSTART extern "C" {
#define IMPORTEND };

#else

#define EXPORT	extern
#define IMPORT	extern
#define EXPORTSTART
#define EXPORTEND

#define IMPORTSTART
#define IMPORTEND

#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#endif
