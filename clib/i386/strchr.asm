INCLUDE "PROLOG.AS"

EXTERN _strlen, _memchr
PUBLIC strchr, _strchr

strchr:
_strchr	PROC	src:MEMPTR,chr:MWORD

    CALL    _strlen,src
	INC	EAX
	CALL	_memchr,src,chr,EAX

    ADD ESP,((SIZE MWORD) * 4)

    RET 0
	
_strchr	ENDP

INCLUDE "EPILOG.AS"
