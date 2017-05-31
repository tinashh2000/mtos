INCLUDE "PROLOG.AS"

PUBLIC mtos_xmemdiff, _mtos_xmemdiff
 
mtos_xmemdiff:
_mtos_xmemdiff  PROC    wcstr:MWORD,mbstr:MWORD,strsize:DWORD
    PUSH    ECX,ESI,EDI
    MOV ESI,wcstr
    MOV EDI,mbstr
	
	TEST	ESI,ESI	;If one of them is zero
	JZ	pmemcmpDone

	TEST	EDI,EDI	;If one of them is zero
	JZ	pmemcmpDone
	
    MOV ECX,strsize
 _mtos_xmemloop:
	MOV	AL,[ESI]
	CMP	AL,[EDI]
	JNZ	_mtos_xmemne
	ADD	ESI,2
	INC EDI
	DEC	ECX
	JNZ	_mtos_xmemloop
	MOV	EAX,strsize	;Equal
 pmemcmpDone:
    POP EDI,ESI,ECX
    RET 0
 _mtos_xmemne:
	MOV	EAX,EDI
	SUB	EAX,mbstr
	JMP	pmemcmpDone
	
_mtos_xmemdiff  ENDP

INCLUDE "EPILOG.AS"
