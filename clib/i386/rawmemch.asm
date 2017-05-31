INCLUDE "PROLOG.AS"

EXTERN _memchr
PUBLIC rawmemchr, _rawmemchr

rawmemchr:
_rawmemchr	PROC	block:MEMPTR,chr:MWORD
	CALL	_memchr,block,chr,-1
    ADD ESP,((SIZE MWORD) * 3)
    RET 0

_rawmemchr	ENDP

INCLUDE "EPILOG.AS"
