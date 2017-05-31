#pragma once
#define RAND_MAX	65535
#define _NOSTDIO
#define _NOSTRINGH
#define _NOSTDLIB
#define _NOSTDDEF
#define _NOSTDARG

//#define memcpy	OSMemCpy
//#define memset	OSMemSet
//*#define memmove	OSMemMove

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#ifndef _MTOX_COMMON_
#include "_mtx_.h"
#endif

EXPORTSTART

void InitStd(void);

char *  __CDECL xsprintf(char *dest, const char *str,...);
char *  __CDECL ysprintf(char *dest, const char *str, ...);
int __CDECL snprintf2(char *str, size_t sz, const char *format, ...);
int __CDECL sprintf2(char *str, const char *format, ...);
size_t	__CDECL	mtos_memdiff(CHARPTR s1, CHARPTR s2, size_t len);
size_t	__CDECL	mtos_wcmemdiff(WCHARPTR s1, WCHARPTR s2, size_t len);
size_t	__CDECL mtos_xmemdiff(WCHARPTR s1, CHARPTR s2, size_t len);

// int     putchar ( int character );

int xxprintf(const char *str,...);

BOOL	IsNumber(char *str);
BOOL	IsNumberW(WCHAR *str);

BOOL	IsLeapYear(UINT16 year);
UINT16	MonthsToDays(UINT16 month);
DATETIME_S	DateToSeconds(UINT16 year, UINT8 month, UINT8 day);

UINT32 CopyStr(char *dest, char *src, UINT32*limit);
UINT32 Hex64ToStr(char *str, UINT64 val, UINT32 *limit, UINT32 paddNum);
UINT32 Hex32ToStr(char *str, UINT32 val, UINT32 *limit, UINT32 paddNum);
UINT32 Hex16ToStr(char *str, UINT32 val, UINT32 *limit, UINT32 paddNum);

UINT32 Int64ToStr(char *st, UINT64 val, UINT32* limit,UINT32 paddNum);
UINT32 Int32ToStr(char *st, UINT32 val, UINT32* limit, UINT32 paddNum);
UINT32 Int16ToStr(char *st, UINT32 val, UINT32* limit, UINT32 paddNum);


UINT32 CopyWStr(WCHARPTR dest, WCHARPTR src, UINT32*limit);
UINT32 Hex64ToWStr(WCHARPTR str, UINT64 val, UINT32 *limit, UINT32 paddNum);
UINT32 Hex32ToWStr(WCHARPTR str, UINT32 val, UINT32 *limit, UINT32 paddNum);
UINT32 Hex16ToWStr(WCHARPTR str, UINT32 val, UINT32 *limit, UINT32 paddNum);

UINT32 Int64ToWStr(WCHARPTR st, UINT64 val, UINT32* limit, UINT32 paddNum);
UINT32 Int32ToWStr(WCHARPTR st, UINT32 val, UINT32* limit, UINT32 paddNum);
UINT32 Int16ToWStr(WCHARPTR st, UINT32 val, UINT32* limit, UINT32 paddNum);

void PrintInt32(UINT32 val,UINT32 paddNum);
void PrintInt64(UINT32 val,UINT32 paddNum);
void PrintHex32(UINT32 val, UINT32 paddNum);
void PrintHex64(UINT32 val, UINT32 paddNum);

EXPORTEND

#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
