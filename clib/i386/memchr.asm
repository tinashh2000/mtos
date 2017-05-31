INCLUDE "PROLOG.AS"

PUBLIC memchr,_memchr
memchr:
_memchr	PROC	block:MEMPTR,chr:MWORD,initSize:MWORD
	PUSH	EDI
	MOV	ECX,initSize
	MOV	EDI,block
	MOV	AL,chr
	
	REPNZ	SCASB
	MOV	EAX,0
	JNZ	mcDone
	MOV	EAX,EDI
	DEC	EAX
 mcDone:	
	POP	EDI
    RET 0

_memchr	ENDP

INCLUDE "EPILOG.AS"
