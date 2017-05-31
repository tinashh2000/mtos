INCLUDE "PROLOG.AS"

EXTERN _wcslen,_wmemchr
PUBLIC wcschrnul, _wcschrnul

wcschrnul:
_wcschrnul	PROC	src:MEMPTR,chr:MWORD

	PUSH	EBX
	CALL	_wcslen,src
	ADD	EAX,2
	MOV	EBX,EAX
	CALL	_wmemchr,src,chr,EAX
	TEST	EAX,EAX
    JNZ wcscnDone
	MOV	EAX,EBX	;null terminator
	ADD	EAX,src
	DEC	EAX
	DEC	EAX
 wcscnDone:

    ADD ESP,((SIZE MWORD) * 4)

	POP	EBX
    RET 0
	
_wcschrnul	ENDP
INCLUDE "EPILOG.AS"
