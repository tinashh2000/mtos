#pragma once

#ifndef _MTOX_COMMON_
#include "_mtx_.h"
#endif

/* Data structure definitions for div and ldiv runtimes. */

#ifndef _DIV_T_DEFINED

typedef struct _div_t {
	int quot;
	int rem;
} div_t;

typedef struct _ldiv_t {
	long quot;
	long rem;
} ldiv_t;

typedef struct {
  long long quot;
  long long rem;
} lldiv_t;

#define _DIV_T_DEFINED
#endif  /* _DIV_T_DEFINED */


EXPORTSTART
long __CDECL atol(const char *s);
long long __CDECL atoll(const char *s);
long long __CDECL strtoll(const char *s);

long int __CDECL strtol(const char* str, char** endptr, int base);

double	__CDECL atof(const char *str);
int		__CDECL atoi(const char *str);
long int	__CDECL atol(const char *str);
double	__CDECL strtod(const char *str, char **endptr);
float       __CDECL  strtof( const char *str, char **str_end );
long int	__CDECL strtol(const char *str, char **endptr, int base);
unsigned long int	__CDECL strtoul(const char *str, char **endptr, int base);
unsigned long long	__CDECL strtoull(const char *str, char **endptr, int base);

size_t       __CDECL wcstombs(char * __s, const wchar_t *__pwcs, size_t __n);
int           __CDECL wctomb(char * __s, wchar_t __wc);
double        __CDECL _wtof(const wchar_t * __s);
int           __CDECL _wtoi(const wchar_t * __s);
long          __CDECL _wtol(const wchar_t * __s);
long double   __CDECL _wtold(const wchar_t * __s);
double        __CDECL wcstod(const wchar_t * __s, wchar_t * *__endptr);
long          __CDECL wcstol(const wchar_t * __s, wchar_t * *__endptr, int __radix);
long double   __CDECL _wcstold(const wchar_t * __s, wchar_t * *__endptr);
unsigned long __CDECL wcstoul(const wchar_t * __s, wchar_t * *__endptr, int __radix);
int           __CDECL _wsystem(const wchar_t * __command);
wchar_t *     __CDECL _itow(int __value, wchar_t *__string, int __radix);
wchar_t *     __CDECL _ltow(long __value, wchar_t *__string, int __radix);
wchar_t *     __CDECL _ultow(unsigned long __value, wchar_t *__string, int __radix);

void*	__CDECL calloc(size_t nitems, size_t size);
void	__CDECL free(void *ptr);
void*	__CDECL malloc(size_t size);
void*	__CDECL realloc(void *ptr, size_t size);
void	__CDECL abort(void);
int		__CDECL atexit(void(*func)(void));
void	__CDECL exit(int status);
char *	__CDECL getenv(const char *name);
int		__CDECL  system(const char *string);
void *	__CDECL bsearch(const void *key, const void *base, size_t nitems, size_t size, int(*compar)(const void *, const void *));
//void 	__CDECL qsort(void *base, size_t nitems, size_t size, int(*compar)(const void *, const void*));
void    __CDECL qsort(void *base, size_t num, size_t width, QSORTPROC comp);
int 	__CDECL abs(int x);
div_t 	__CDECL div(int numer, int denom);
long int	__CDECL labs(long int x);
long long	__CDECL llabs(long long x);
ldiv_t 	__CDECL ldiv(long int numer, long int denom);
lldiv_t 	__CDECL lldiv(long long numer, long long denom);

int 	__CDECL rand(void);
void 	__CDECL srand(unsigned int seed);
int 	__CDECL mblen(const char *str, size_t n);
size_t 	__CDECL mbstowcs(wchar_t *pwcs, const char *str, size_t n);
int 	__CDECL mbtowc(wchar_t *pwc, const char *str, size_t n);
size_t 	__CDECL wcstombs(char *str, const wchar_t *pwcs, size_t n);
int 	__CDECL wctomb(char *str, wchar_t wchar);

int __CDECL at_quick_exit(void (*func)(void));
int	__CDECL at_quick_exit(void (*)(void));
void __CDECL quick_exit(int status);
EXPORTEND

