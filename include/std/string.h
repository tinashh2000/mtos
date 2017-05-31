#pragma once

#define _STRING_H_
//#define __midl
#ifndef _MTOX_COMMON_
#include "_mtx_.h"
#endif

EXPORTSTART

	void *rawmemchr(void *block, int c);
	void *mempcpy(void *dest,void *src,size_t size);
	char * __CDECL strlwr(char *str);
	char * __CDECL strupr(char *str);

	char		__CDECL strcpy(char * wto, const char * wfrom);
	size_t		__CDECL strlen(const char *str);
	int			__CDECL strcmp(const char *str1,const char *str2);
	size_t		__CDECL strnlen(const char *str, size_t maxlen);
	int 		__CDECL strncmp ( const char * str1, const char * str2, size_t num );
	char *		__CDECL strncat ( char * destination, const char * source, size_t num );
	char *  	__CDECL strcat ( char * destination, const char * source );
	const char*	__CDECL strchr ( const char * str, int character );
	char*		__CDECL strncpy ( char * destination, const char * source, size_t num );
	const char*	__CDECL strrchr ( const char * str, int character );
	int			__CDECL strcoll ( const char * str1, const char * str2 );
	char *		__CDECL strstr(const char *s1,const char *s2);
	char * __CDECL _strlwr(char *str);
	char * __CDECL _strupr(char *str);
	void*		__CDECL memchr ( void * ptr, int value, size_t num );
	void*		__CDECL memrchr(void * ptr, int value, size_t num);
	void*		__CDECL memset(void *ptr, int value, size_t num); 
	void*		__CDECL memset_opt(void *ptr,int value,size_t num);
	void*		__CDECL memcpy(void *destination,const void *source,size_t num);
	int			__CDECL memcmp(const void *ptr1, const void *ptr2, size_t num);
	void*		__CDECL memmove(void *dest,const void*source, size_t num);

	void*		__CDECL memcpy_opt(void *destination, const void *source, size_t num);

EXPORTEND
