INCLUDE "PROLOG.AS"

EXTERN _strlen, _memchr
PUBLIC strchrnul, _strchrnul

strchrnul:
_strchrnul	PROC	src:MEMPTR,chr:MWORD

	PUSH	EBX
    CALL    _strlen,src
	INC	EAX
	MOV	EBX,EAX
	CALL	_memchr,src,chr,EAX
	TEST	EAX,EAX
	JNZ	sncDone
	MOV	EAX,EBX	;null terminator
	ADD	EAX,src
	DEC	EAX
 sncDone:
    ADD ESP,((SIZE MWORD) * 4)

	POP	EBX
    RET 0
	
_strchrnul	ENDP

INCLUDE "EPILOG.AS"
