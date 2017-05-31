FILE* __CDECL  fopen (const char*, const char*);
FILE* __CDECL  fopen (const char*, const char*);
FILE* __CDECL 	freopen (const char*, const char*, FILE*);
int __CDECL 	fflush (FILE*);
int __CDECL 	fclose (FILE*);

int __CDECL 	remove (const char*);
int __CDECL 	rename (const char*, const char*);
FILE* __CDECL 	tmpfile (void);
char* __CDECL 	tmpnam (char*);

#ifndef __STRICT_ANSI__
char* __CDECL 	_tempnam (const char*, const char*);
int __CDECL 	_rmtmp(void);
int __CDECL 	_unlink (const char*);

#ifndef	NO_OLDNAMES
char* __CDECL 	tempnam (const char*, const char*);
int __CDECL 	rmtmp(void);
int __CDECL 	unlink (const char*);
#endif
#endif /* __STRICT_ANSI__ */

int __CDECL 	setvbuf (FILE*, char*, int, size_t);

void __CDECL 	setbuf (FILE*, char*);

int __CDECL  fprintf (FILE*, const char*, ...);
int __CDECL  printf (const char*, ...);
int __CDECL  sprintf (char*, const char*, ...);
int __CDECL  vfprintf (FILE*, const char*, va_list arg);
int __CDECL  vprintf (const char*, va_list arg);
int __CDECL  vsprintf (char*, const char*, va_list arg);

int __CDECL  _snprintf (char*, size_t, const char*, ...);
int __CDECL  _vsnprintf (char*, size_t, const char*, va_list arg);
int __CDECL  _vscprintf (const char*, va_list arg);

#ifndef __NO_ISOCEXT  /* externs in libmingwex.a */
/*
 * Microsoft does not provide implementations for the following,
 * which are required by C99.  Note in particular that the corresponding
 * Microsoft implementations of _snprintf() and _vsnprintf() are *not*
 * compatible with C99, but the following are; if you want the MSVCRT
 * behaviour, you *must* use the Microsoft uglified names.
 */
int __CDECL  snprintf (char *, size_t, const char *, ...);
int __CDECL  vsnprintf (char *, size_t, const char *, va_list arg);

int __CDECL  vscanf (const char *  , va_list arg);
int __CDECL  vfscanf (FILE *  , const char *  ,
		     va_list arg);
int __CDECL  vsscanf (const char * ,const char *  , va_list arg);

#endif  /* !__NO_ISOCEXT */

/*
 * Formatted Input
 */

int __CDECL 	fscanf (FILE*, const char*, ...);
int __CDECL 	scanf (const char*, ...);
int __CDECL 	sscanf (const char*, const char*, ...);
/*
 * Character Input and Output Functions
 */

int __CDECL 	fgetc (FILE*);
char* __CDECL 	fgets (char*, int, FILE*);
int __CDECL 	fputc (int, FILE*);
int __CDECL 	fputs (const char*, FILE*);
char* __CDECL 	gets (char*);
int __CDECL 	puts (const char*);
int __CDECL 	ungetc (int, FILE*);

/* Traditionally, getc and putc are defined as macros. but the
   standard doesn't say that they must be macros.
   We use inline functions here to allow the fast versions
   to be used in C++ with namespace qualification, eg., ::getc.

   _filbuf and _flsbuf  are not thread-safe. */
int __CDECL 	_filbuf (FILE*);
int __CDECL 	_flsbuf (int, FILE*);


/*
 * Direct Input and Output Functions
 */

size_t __CDECL 	fread (void*, size_t, size_t, FILE*);
size_t __CDECL 	fwrite (const void*, size_t, size_t, FILE*);

/*
 * File Positioning Functions
 */

int __CDECL 	fseek (FILE*, long, int);
long __CDECL 	ftell (FILE*);
void __CDECL 	rewind (FILE*);

int __CDECL 	_fseek_nolock (FILE*, long, int);
long __CDECL 	_ftell_nolock (FILE*);

int __CDECL 	_fseeki64 (FILE*, __int64, int);
__int64 __CDECL 	_ftelli64 (FILE*);
int __CDECL 	_fseeki64_nolock (FILE*, __int64, int);
__int64 __CDECL 	_ftelli64_nolock (FILE*);

#ifdef __USE_MINGW_FSEEK  /* These are in libmingwex.a */
/*
 * Workaround for limitations on win9x where a file contents are
 * not zero'd out if you seek past the end and then write.
 */

int __CDECL  __mingw_fseek (FILE *, long, int);
size_t __CDECL  __mingw_fwrite (const void*, size_t, size_t, FILE*);
#define fseek(fp, offset, whence)  __mingw_fseek(fp, offset, whence)
#define fwrite(buffer, size, count, fp)  __mingw_fwrite(buffer, size, count, fp)
#endif /* __USE_MINGW_FSEEK */

int __CDECL 	fgetpos	(FILE*, fpos_t*);
int __CDECL 	fsetpos (FILE*, const fpos_t*);

/*
 * Error Functions
 */

int __CDECL 	feof (FILE*);
int __CDECL 	ferror (FILE*);

void __CDECL 	clearerr (FILE*);
void __CDECL 	perror (const char*);


#ifndef __STRICT_ANSI__
/*
 * Pipes
 */
FILE* __CDECL 	_popen (const char*, const char*);
int __CDECL 	_pclose (FILE*);

#ifndef NO_OLDNAMES
FILE* __CDECL 	popen (const char*, const char*);
int __CDECL 	pclose (FILE*);
#endif

/*
 * Other Non ANSI functions
 */
int __CDECL 	_flushall (void);
int __CDECL 	_fgetchar (void);
int __CDECL 	_fputchar (int);
FILE* __CDECL 	_fdopen (int, const char*);
int __CDECL 	_fileno (FILE*);
int __CDECL 	_fcloseall (void);
FILE* __CDECL 	_fsopen (const char*, const char*, int);
int __CDECL 	_getmaxstdio (void);
int __CDECL 	_setmaxstdio (int);

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA) || defined(HAVE_GET_OUTPUT_FORMAT)
unsigned int __CDECL  _get_output_format (void);
unsigned int __CDECL  _set_output_format (unsigned int);
int __CDECL  _get_printf_count_output (void);
int __CDECL  _set_printf_count_output (int);

#else
#define _get_output_format() 0
#define _set_output_format(x) 0
#define _get_printf_count_output() 0
#define _set_printf_count_output(x) 0
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_VISTA) || defined(HAVE_GET_OUTPUT_FORMAT) */

#define _TWO_DIGIT_EXPONENT 1

#ifndef _NO_OLDNAMES
int __CDECL 	fgetchar (void);
int __CDECL 	fputchar (int);
FILE* __CDECL 	fdopen (int, const char*);
int __CDECL 	fileno (FILE*);
#endif	/* Not _NO_OLDNAMES */

#include "sys/types.h"

#if !defined (__NO_MINGW_LFS)
inline	FILE* __CDECL  fopen64 (const char*, const char*);
inline  FILE* __CDECL  fopen64 (const char* filename, const char* mode)
{
  return fopen (filename, mode);
}

int __CDECL  fseeko64 (FILE*, off64_t, int);

#ifdef __USE_MINGW_FSEEK
int __CDECL  __mingw_fseeko64 (FILE *, off64_t, int);
#define fseeko64(fp, offset, whence)  __mingw_fseeko64(fp, offset, whence)
#endif /* __USER_MINGW_FSEEK */

inline off64_t __CDECL  ftello64 (FILE *);
inline off64_t __CDECL  ftello64 (FILE * stream)
{
  fpos_t pos;
  if (fgetpos(stream, &pos))
    return  -1LL;
  else
   return ((off64_t) pos);
}
#endif /* __NO_MINGW_LFS */

#endif	/* Not __STRICT_ANSI__ */

/* Wide  versions */

#ifndef _WSTDIO_DEFINED
/*  also in wchar.h - keep in sync */
int __CDECL 	fwprintf (FILE*, const wchar_t*, ...);
int __CDECL 	wprintf (const wchar_t*, ...);
int __CDECL 	_snwprintf (wchar_t*, size_t, const wchar_t*, ...);
int __CDECL 	vfwprintf (FILE*, const wchar_t*, va_list arg);
int __CDECL 	vwprintf (const wchar_t*, va_list arg);
//int __CDECL 	_vsnwprintf (wchar_t*, size_t, const wchar_t*, va_list arg);
int __CDECL 	_vscwprintf (const wchar_t*, va_list arg);
int __CDECL 	fwscanf (FILE*, const wchar_t*, ...);
int __CDECL 	wscanf (const wchar_t*, ...);
int __CDECL 	swscanf (const wchar_t*, const wchar_t*, ...);
wint_t __CDECL 	fgetwc (FILE*);
wint_t __CDECL 	fputwc (wchar_t, FILE*);
wint_t __CDECL 	ungetwc (wchar_t, FILE*);

/* These differ from the ISO C prototypes, which have a maxlen parameter (like snprintf).  */
#ifndef __STRICT_ANSI__
int __CDECL 	swprintf (wchar_t*, const wchar_t*, ...);
int __CDECL 	vswprintf (wchar_t*, const wchar_t*, va_list arg);
#endif

wchar_t * __CDECL fgetws(const wchar_t * s, int n, FILE *stream);
int __CDECL 	fputws (const wchar_t*, FILE*);
wint_t __CDECL 	getwc (FILE*);
wint_t __CDECL 	getwchar (void);
wint_t __CDECL 	putwc (wint_t, FILE*);
wint_t __CDECL 	putwchar (wint_t);
#ifndef __STRICT_ANSI__
void __CDECL  _lock_file(FILE*);
void __CDECL  _unlock_file(FILE*);
wchar_t* __CDECL  _getws (wchar_t*);
int __CDECL 	_putws (const wchar_t*);
FILE* __CDECL 	_wfdopen(int, const wchar_t *);
FILE* __CDECL 	_wfopen (const wchar_t*, const wchar_t*);
FILE* __CDECL 	_wfreopen (const wchar_t*, const wchar_t*, FILE*);
FILE* __CDECL 	_wfsopen (const wchar_t*, const wchar_t*, int);
wchar_t* __CDECL  _wtmpnam (wchar_t*);
wchar_t* __CDECL  _wtempnam (const wchar_t*, const wchar_t*);
int __CDECL 	_wrename (const wchar_t*, const wchar_t*);
int __CDECL 	_wremove (const wchar_t*);
void __CDECL 	_wperror (const wchar_t*);
FILE* __CDECL 	_wpopen (const wchar_t*, const wchar_t*);
#endif  /* __STRICT_ANSI__ */

#ifndef __NO_ISOCEXT  /* externs in libmingwex.a */
int __CDECL  snwprintf (wchar_t* s, size_t n, const wchar_t*  format, ...);
int __CDECL  vsnwprintf (wchar_t* s, size_t n, const wchar_t* format, va_list arg);

int __CDECL  vwscanf (const wchar_t *  , va_list arg);
int __CDECL  vfwscanf (FILE *  ,
		       const wchar_t *  , va_list arg);
int __CDECL  vswscanf (const wchar_t *  ,
		       const wchar_t *  , va_list arg);
#endif

#define _WSTDIO_DEFINED
#endif /* _WSTDIO_DEFINED */

#ifndef __STRICT_ANSI__
#ifndef NO_OLDNAMES
FILE* __CDECL 	wpopen (const wchar_t*, const wchar_t*);
#endif /* not NO_OLDNAMES */
#endif
/*
 * Other Non ANSI wide functions
 */
wint_t __CDECL 	_fgetwchar (void);
wint_t __CDECL 	_fputwchar (wint_t);
int __CDECL 	_getw (FILE*);
int __CDECL 	_putw (int, FILE*);

#ifndef _NO_OLDNAMES
wint_t __CDECL 	fgetwchar (void);
wint_t __CDECL 	fputwchar (wint_t);
int __CDECL 	getw (FILE*);
int __CDECL 	putw (int, FILE*);
#endif	/* Not _NO_OLDNAMES */
