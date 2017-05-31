INCLUDE "PROLOG.AS"

PUBLIC memcmp, _memcmp

memcmp:
_memcmp  PROC    str1:MWORD,str2:MWORD,strsize:DWORD
    PUSH    ECX,ESI,EDI
    MOV ESI,str1
    MOV EDI,str2
	
	TEST	ESI,EDI	;If one of them is zero
	JZ	memcmpDone
	
    MOV ECX,strsize
	MOV	AL,CL
    AND AL,3
    SHR ECX,2
    REPZ CMPSD
    JNZ memcmpFinal
    MOV CL,AL
    REPZ    CMPSB

    MOV EAX,0
    JZ  memcmpDone
 memcmpFinal:    

    MOV AL,1
    JA  memcmpDone
    MOV AL,0
    DEC EAX

 memcmpDone:
    POP EDI,ESI,ECX
    RET 0
_memcmp  ENDP

INCLUDE "EPILOG.AS"
