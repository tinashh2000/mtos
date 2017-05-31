#include <mtos.h>
#include "clib.h"


/*
size_t xstrnlen(const char *s,size_t maxlen) {
    size_t len = strlen(s);
    if (len > maxlen)
        return maxlen;

    return len;
}

void InitStd() {
	InitStream(&StdError_Stream,NULL,NULL,&_xpPutStr,&_xpPutChar,NULL,NULL,NULL,NULL);
	InitStream(&StdOut_Stream,NULL,NULL,&_xpPutStr,&_xpPutChar,NULL,NULL,NULL,NULL);
	InitStream(&StdIn_Stream,NULL,NULL,NULL,NULL,NULL,&_xpGetStr,&_xpGetChar,&_xpGetData);
}
*/
