INCLUDE "PROLOG.AS"

PUBLIC wmemchr, _wmemchr

wmemchr:
_wmemchr	PROC	block:MEMPTR,chr:MWORD,initSize:MWORD
	PUSH	ECX,EDI
	MOV	ECX,initSize
	MOV	EDI,block
	MOV	AX,chr
	
	REPNZ	SCASW
	MOV	EAX,0
	JNZ	wmcDone
	MOV	EAX,EDI
	DEC	EAX
	DEC	EAX
 wmcDone:	
	POP	EDI,ECX
    RET 0

_wmemchr	ENDP

INCLUDE "EPILOG.AS"