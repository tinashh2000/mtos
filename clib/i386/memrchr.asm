INCLUDE "PROLOG.AS"

PUBLIC memrchr, _memrchr

memrchr:
_memrchr    PROC    block:MEMPTR,chr:MWORD,initSize:MWORD
	PUSHFD
	PUSH	ECX,EDI
	MOV	ECX,initSize
	MOV	EDI,block
	ADD	EDI,ECX
	DEC	EDI	
    MOV AL,chr
	STD
	REPNZ	SCASB
	MOV	EAX,0
	JNZ	mrcDone
	MOV	EAX,EDI
	INC	EAX
 mrcDone:	
	POP	EDI,ECX
	POPFD
    RET 0

_memrchr	ENDP

INCLUDE "EPILOG.AS"
