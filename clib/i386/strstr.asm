INCLUDE "PROLOG.AS"

EXTERN _strlen, _memcmp
PUBLIC strstr, _strstr

strstr:
_strstr PROC dest:MEMPTR,src:MEMPTR
	
	PUSH	EBX,ECX,ESI,EDI
	MOV	ESI,src
	MOV	EDI,dest

	CALL	_strlen,EDI
	MOV		EBX,EAX
	CALL	_strlen,ESI
	MOV	ECX,EAX
    ADD ESP,(2*(SIZE MWORD))
	
 _strstrLoop:
 
	MOV	AL,[ESI]
	REP	SCASB
	JNZ	_strstrNotFound
	PUSH	EAX
	MOV	EAX,EDI
	DEC	EAX
	CALL	_memcmp,EAX,ESI,EBX		;memcmp, dest, src, sizeSrc
    ADD ESP,(3*(SIZE MWORD))
	CMP	EAX,0	;Is it equal
	POP	EAX
	JNZ	_strstrLoop ;if not loop again. Starting where EDI was before the call
	
 _strstrDone:
 
	MOV	EAX,EDI
	DEC	EAX
	POP	EDI,ESI,ECX,EBX
	RET
	
 _strstrNotFound:	
	MOV	EAX,0
	JMP	_strstrDone

_strstr ENDP
	
INCLUDE "EPILOG.AS"
