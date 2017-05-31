INCLUDE "PROLOG.AS"

EXTERN _wcslen, _wmemchr
PUBLIC wcschr, _wcschr

wcschr:
_wcschr	PROC	src:MEMPTR,chr:MWORD

	CALL	_wcslen,src
	INC	EAX
	INC	EAX
	CALL	_wmemchr,src,chr,EAX

    ADD ESP,((SIZE MWORD) * 4)

    RET 0
_wcschr	ENDP


INCLUDE "EPILOG.AS"