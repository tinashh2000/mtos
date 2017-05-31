#pragma once

#ifndef _MTOX_COMMON_
#include "_mtx_.h"
#endif

//#include <stddef.h>
#include <stdarg.h>

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

typedef struct
{
	void* _Placeholder;
} FILE;

#define stdin  ((FILE*)0)
#define stdout ((FILE*)1)
#define stderr ((FILE*)2)

#define	EOF	(-1)

typedef long long fpos_t;

EXPORTSTART
FILE *	__CDECL	fopen ( const char * filename, const char * mode );
int		__CDECL	fclose ( FILE * stream );
int		__CDECL	fflush ( FILE * stream );
void	__CDECL	clearerr ( FILE * stream );
int		__CDECL	feof ( FILE * stream );
size_t	__CDECL fread(void *ptr, size_t size, size_t n, FILE *stream);
int		__CDECL fseek(FILE *stream,long int offset, int whence );
long int __CDECL	ftell ( FILE * stream );
int 	__CDECL	fsetpos ( FILE * stream, const fpos_t * pos );
int 	__CDECL	fgetpos ( FILE * stream, fpos_t * pos );
int		__CDECL fgetsize(FILE *stream, fpos_t *pos);
int     __CDECL printf(const char *str,...);
int     __CDECL sprintf(char *dest,const char *str,...);
int     __CDECL vsnprintf(char* _Buffer, const size_t _BufferCount, char const* _Format, va_list _ArgList);
int		__CDECL vfprintf(FILE *f, const char *format,va_list arg);

/*int     __CDECL sprintf(char *dest,const char *str,...);
int     __CDECL vsnprintf(char* _Buffer, const size_t _BufferCount, char const* _Format, va_list _ArgList);
int		__CDECL vfprintf(FILE *f, const char *format,va_list arg);
*/

#include "stdiox.h"
#include "string.h"
#include "wchar.h"
EXPORTEND
