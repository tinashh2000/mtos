INCLUDE "PROLOG.AS"

EXTERN _strlen, _strnlen,_memcpy

PUBLIC strncat, _strncat

strncat:
_strncat    PROC dest:MEMPTR, src:MEMPTR,tsize:MWORD
	PUSH EBX,ESI
	
	MOV	EBX,dest
	CALL	_strlen,dest
	ADD EBX,EAX		;EBX = end of dest

    CALL    _strnlen,src,tsize	;size of src, or cut it to tsize

	CALL	_memcpy,EBX,src,EAX

    ADD ESP,((SIZE MWORD) * 6)

	MOV	BYTE [EBX][EAX],0
	MOV EAX,dest
	POP	ESI, EBX
    RET 0
_strncat 	ENDP

INCLUDE "EPILOG.AS"
