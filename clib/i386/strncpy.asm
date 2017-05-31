INCLUDE "PROLOG.AS"

EXTERN _strnlen, _memset, _memcpy
PUBLIC strncpy, _strncpy

strncpy:
_strncpy	PROC	dest:MEMPTR,src:MEMPTR,strsize:MWORD
    PUSH   EBX

	CALL	_strnlen,src,strsize
    MOV EBX,EAX
	CALL	_memcpy,dest,src,EAX
    
	MOV	EAX,strsize
    SUB EAX,EBX
    ADD EBX,dest
    CALL    _memset,EBX,MWORD (0),EAX

    ADD ESP,((SIZE MWORD) * 8)

    POP EBX
    RET 0
_strncpy	ENDP

INCLUDE "EPILOG.AS"
