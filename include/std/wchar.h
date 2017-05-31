#pragma once

#ifndef _MTOX_COMMON_
#include "_mtx_.h"
#endif

#include <time.h>

typedef int mbstate_t;

	
EXPORTSTART
void*		__CDECL memmove(void *dest,const void*source, size_t num);
int __CDECL mbsinit(const mbstate_t *_P);
wchar_t * __CDECL wmemmove(wchar_t *s1, const wchar_t *s2, size_t sz);
wchar_t * __CDECL wmemset(wchar_t *s1, wchar_t ch, size_t sz);
int __CDECL wctob(wint_t);

unsigned long long int __CDECL wcstoull (const wchar_t* str, wchar_t** endptr, int base);
long long __CDECL wcstoll( const wchar_t *nptr, wchar_t **endptr, int base );
int __CDECL wmemcmp (const wchar_t* ptr1, const wchar_t* ptr2, size_t num);

wchar_t *	__CDECL wmemcpy(wchar_t * wto, const wchar_t * wfrom, size_t size);
wchar_t * __CDECL wmempcpy(wchar_t * dest, wchar_t * src,size_t size);
void * 		__CDECL wmemchr(const wchar_t*s, int c, size_t n);
wchar_t *	__CDECL wmemrchr(const wchar_t * s, int c_in, size_t n);

unsigned long __CDECL wcstoul(const wchar_t *, wchar_t **, int);
long double __CDECL wcstold (const wchar_t* str, wchar_t** endptr);
wchar_t *	__CDECL wcscpy(wchar_t * wto, const wchar_t * wfrom);
wchar_t * __CDECL wcsrchr(const wchar_t *wstring, wchar_t c);
wchar_t*	__CDECL wcsstr(const wchar_t *haystack, const wchar_t *needle);
size_t		__CDECL wcslen(const wchar_t *str);
wchar_t*	__CDECL wcschr(const wchar_t *wstring, int wc);
size_t 		__CDECL wcsnlen(const wchar_t *s, size_t n);
wchar_t * __CDECL wcsupr(wchar_t *str);
wchar_t * __CDECL wcslwr(wchar_t *str);

wchar_t * __CDECL wcscat(wchar_t *, const wchar_t *);
size_t __CDECL wcrtomb(char *, wchar_t, mbstate_t *);
size_t __CDECL wcsrtombs(char *, const wchar_t **, size_t, mbstate_t *);
size_t __CDECL mbsrtowcs(wchar_t *, const char **, size_t, mbstate_t *);
int __CDECL wcscoll(const wchar_t *, const wchar_t *);
int __CDECL wcscmp(const wchar_t *, const wchar_t *);

wchar_t * __CDECL wcscat(wchar_t *, const wchar_t *);

int __CDECL wcscmp(const wchar_t *, const wchar_t *);
wchar_t * __CDECL wcscpy(wchar_t *, const wchar_t *);
size_t __CDECL wcscspn(const wchar_t *, const wchar_t *);
size_t __CDECL wcslen(const wchar_t *);
wchar_t * __CDECL wcsncat(wchar_t *, const wchar_t *, size_t);
int __CDECL wcsncmp(const wchar_t *, const wchar_t *, size_t);
wchar_t * __CDECL wcsncpy(wchar_t *, const wchar_t *, size_t);
wchar_t * __CDECL wcspbrk(const wchar_t *, const wchar_t *);
wchar_t * __CDECL wcsrchr(const wchar_t *, wchar_t);
size_t __CDECL wcsspn(const wchar_t *, const wchar_t *);
wchar_t * __CDECL wcsstr(const wchar_t *, const wchar_t *);
wchar_t * __CDECL wcstok(wchar_t *, const wchar_t *);
wchar_t * __CDECL _wcserror(int);
wchar_t * __CDECL __wcserror(const wchar_t *);
wchar_t * __CDECL _wcsdup(const wchar_t *);
int __CDECL _wcsicmp(const wchar_t *, const wchar_t *);
int __CDECL _wcsnicmp(const wchar_t *, const wchar_t *, size_t);
wchar_t * __CDECL _wcsnset(wchar_t *, wchar_t, size_t);
wchar_t * __CDECL _wcsrev(wchar_t *);
wchar_t * __CDECL _wcsset(wchar_t *, wchar_t);
wchar_t * __CDECL _wcslwr(wchar_t *);
wchar_t * __CDECL _wcsupr(wchar_t *);
size_t __CDECL wcsxfrm(wchar_t *, const wchar_t *, size_t);
int __CDECL wcscoll(const wchar_t *, const wchar_t *);
int __CDECL _wcsicoll(const wchar_t *, const wchar_t *);
int __CDECL _wcsncoll(const wchar_t *, const wchar_t *, size_t);
int __CDECL _wcsnicoll(const wchar_t *, const wchar_t *, size_t);

wint_t __CDECL btowc(int);

float __CDECL wcstof(const wchar_t *nptr, wchar_t **endptr);

#ifndef _WTIME_DEFINED
size_t __CDECL wcsftime(wchar_t *, size_t, const wchar_t *, struct tm *);
#endif

size_t __CDECL mbrlen(const char *, size_t, mbstate_t *);
size_t	__CDECL mbrtowc (wchar_t* pwc, const char* pmb, size_t max, mbstate_t* ps);
int __CDECL  fwide (FILE* stream, int mode);

EXPORTEND