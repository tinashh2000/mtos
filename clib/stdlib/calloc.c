/* calloc function */
#include <stdlib.h>
#include <string.h>

_cdecl void *calloc(size_t nelem, size_t size) {	/* allocate a data object on the heap and clear it */
	const size_t n = nelem * size;
	char *p = (char *)malloc(n);

	if (p)
		memset(p, '\0', n);
	return (p);
}

/*
 * Copyright (c) 1992-2003 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1422 */
