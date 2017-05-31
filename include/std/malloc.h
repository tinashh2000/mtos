#ifndef _MTOX_COMMON_
#include "_mtx_.h"
#endif

EXPORTSTART
void *	__CDECL malloc(size_t size);
void *	__CDECL realloc(void *block, size_t size);
void __CDECL free(void*ptr);
EXPORTEND
