#ifndef _WCTYPE_H
#define _WCTYPE_H

/* wctype.h - C99 standard header */


// Bit masks for the possible character types

/* macros */
#define WEOF  ((wint_t)(-1))

/* type definitions */
#ifndef _WINT_T_DEFINED
#define _WINT_T_DEFINED
typedef unsigned short wint_t;
#endif /* _WINT_T_DEFINED */

typedef unsigned int wctrans_t;
typedef unsigned int wctype_t;
EXPORTSTART
int __CDECL iswalnum(wint_t);
int __CDECL iswalpha(wint_t);
int __CDECL iswcntrl(wint_t);
int __CDECL iswdigit(wint_t);
int __CDECL iswgraph(wint_t);
int __CDECL iswlower(wint_t);
int __CDECL iswprint(wint_t);
int __CDECL iswpunct(wint_t);
int __CDECL iswspace(wint_t);
int __CDECL iswblank(wint_t);
int __CDECL iswupper(wint_t);
int __CDECL iswxdigit(wint_t);
int __CDECL _iswascii(wint_t);
int __CDECL iswctype(wint_t, wctype_t);
int __CDECL towlower(wint_t);
int __CDECL towupper(wint_t);
int __CDECL towctrans(wint_t, wctrans_t);
wctrans_t __CDECL wctrans(const char *);
wctype_t __CDECL wctype(const char *);

EXPORTEND

#endif
