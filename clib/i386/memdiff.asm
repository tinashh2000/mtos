INCLUDE "PROLOG.AS"

PUBLIC mtos_memdiff, _mtos_memdiff
 
 mtos_memdiff:
_mtos_memdiff  PROC    str1:MWORD,str2:MWORD,strsize:DWORD
    PUSH    ECX,ESI,EDI
    MOV ESI,str1
    MOV EDI,str2
	
	TEST	ESI,ESI	;If one of them is zero
	JZ	pmemcmpDone

	TEST	EDI,EDI	;If one of them is zero
	JZ	pmemcmpDone
	
    MOV ECX,strsize
	MOV	AL,CL
    AND AL,3
    SHR ECX,2
    REPZ CMPSD
    JNZ pmemcmpNE
    MOV CL,AL
    REPZ    CMPSB
	JNZ	pmemcmpFinal
	MOV EAX,strsize
	JMP	pmemcmpDone

 pmemcmpFinal:    
	DEC	EDI
	MOV	EAX,EDI		;Calculate how many bytes 
	SUB	EAX,str2
 pmemcmpDone:
    POP EDI,ESI,ECX
    RET 0
 pmemcmpNE:
	SUB	EDI,4
	SUB	ESI,4
	MOV	ECX,4
	REP	CMPSB
	JMP	pmemcmpFinal
_mtos_memdiff  ENDP

INCLUDE "EPILOG.AS"
