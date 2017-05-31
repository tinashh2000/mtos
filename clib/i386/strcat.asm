INCLUDE "PROLOG.AS"

EXTERN _strlen, _strcpy

PUBLIC strcat, _strcat

strcat:
_strcat PROC dest:MEMPTR, src:MEMPTR
	PUSH EBX,ESI
	
	MOV	EBX,dest
	CALL	_strlen,EBX
	
	ADD	EBX,EAX ;EBX = end of dest

	CALL	_strcpy,EBX,src

    ADD ESP,((SIZE MWORD) * 3)

	MOV	BYTE [EBX][EAX],0
	MOV EAX,dest
	POP	ESI, EBX
    RET 0
_strcat	ENDP

INCLUDE "EPILOG.AS"