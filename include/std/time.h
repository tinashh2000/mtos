#pragma once

#ifndef _TIME_H
#define _TIME_H

/* time.h - C99 standard header */


/* macros */
#ifndef NULL
#define NULL  ((void *)0)
#endif

/* type definitions */
#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#if __POCC_TARGET__ == 3
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif
#endif /* _SIZE_T_DEFINED */

#ifndef _TIME_T_DEFINED
#define _TIME_T_DEFINED
typedef unsigned long time_t;
#endif /* _TIME_T_DEFINED */

#define CLOCKS_PER_SEC  1000

#ifndef _CLOCK_T_DEFINED
#define _CLOCK_T_DEFINED
typedef unsigned int clock_t;
#endif /* _CLOCK_T_DEFINED */

struct tm {
    int tm_sec;     /* seconds after the minute [0,60] */
    int tm_min;     /* minutes after the hour [0,59] */
    int tm_hour;    /* hours since midnight [0,23] */
    int tm_mday;    /* day of the month [1,31] */
    int tm_mon;     /* month since January [0,11] */
    int tm_year;    /* years since 1900 */
    int tm_wday;    /* days since Sunday [0,6] */
    int tm_yday;    /* days since January 1 [0,365] */
    int tm_isdst;   /* Daylight Saving Time flag */
};

#if __POCC_STDC_VERSION__ >= 201101L
#define TIME_UTC  1
struct timespec {
    time_t tv_sec;
    long tv_nsec;
};
#endif /* __POCC_STDC_VERSION__ >= 201101L */

/* declarations */
EXPORTSTART
double __CDECL difftime(time_t, time_t);
time_t __CDECL time(time_t *);
char * __CDECL asctime(const struct tm *);
clock_t __CDECL clock(void);
char * __CDECL ctime(const time_t *);
struct tm * __CDECL gmtime(const time_t *);
struct tm * __CDECL localtime(const time_t *);
time_t __CDECL mktime(struct tm *);
size_t __CDECL strftime(char *, size_t, const char *, const struct tm *);
#if __POCC_STDC_VERSION__ >= 201101L
int __CDECL timespec_get(struct timespec *, int);
#endif /* __POCC_STDC_VERSION__ >= 201101L */

/* private extensions to standard C */
unsigned int __CDECL _sleep(unsigned int);
char * __CDECL _strdate(char *);
char * __CDECL _strtime(char *);


#if __POCC_TARGET__ == 1 || __POCC_TARGET__ == 3
unsigned long long __CDECL _rdtsc(void);
#endif

EXPORTEND

/* bounds-checking interfaces (TR24731-1, C11 annex K) */
#if __STDC_WANT_LIB_EXT1__

#ifndef _ERRNO_T_DEFINED
#define _ERRNO_T_DEFINED
typedef int errno_t;
#endif /* _ERRNO_T_DEFINED */

#ifndef _RSIZE_T_DEFINED
#define _RSIZE_T_DEFINED
#if __POCC_TARGET__ == 3
typedef unsigned long long rsize_t;
#else
typedef unsigned int rsize_t;
#endif
#endif /* _RSIZE_T_DEFINED */

EXPORTSTART
/* functions */
errno_t __CDECL asctime_s(char *, rsize_t, const struct tm *);
errno_t __CDECL ctime_s(char *, rsize_t, const time_t *);
struct tm * __CDECL gmtime_s(const time_t * restrict, struct tm * restrict);
struct tm * __CDECL localtime_s(const time_t * restrict, struct tm * restrict);

EXPORTEND
#endif /* __STDC_WANT_LIB_EXT1__ */

#endif /* _TIME_H */
