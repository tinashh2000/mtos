INCLUDE "PROLOG.AS"

PUBLIC wmemrchr, _wmemrchr

wmemrchr:
_wmemrchr    PROC    block:MEMPTR,chr:MWORD,initSize:MWORD
	PUSHFD
	PUSH	ECX,EDI
	MOV	ECX,initSize
	MOV	EDI,block
	ADD	EDI,ECX
	SUB EDI,2
    MOV AX,chr
	STD
	REPNZ	SCASW
	MOV	EAX,0
	JNZ	wmrcDone
	MOV	EAX,EDI
	SUB EAX,2
	SHR EAX,1
 wmrcDone:	
	POP	EDI,ECX
	POPFD
    RET 0

_wmemrchr	ENDP

INCLUDE "EPILOG.AS"
