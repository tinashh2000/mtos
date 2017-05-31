INCLUDE "PROLOG.AS"

EXTERN _wcslen
PUBLIC wcsncmp, _wcsncmp

wcsncmp:
_wcsncmp  PROC    str1:MWORD,str2:MWORD,maxlen:MWORD
    PUSH    ECX,ESI,EDI
    MOV ESI,str1
    MOV EDI,str2

    CALL    _wcslen,ESI
    ADD ESP,((SIZE MWORD))

    TEST    EAX,EAX
    JZ  csnwDone

    MOV ECX,[maxlen]
	CMP	EAX,ECX
	CMOVB	ECX,EAX		;if EAX < ECX then ECX=EAX	
	
    MOV AL,CL
    AND AL,1        ;
    SHR ECX,1       ;Divide by 2
    REPZ CMPSD
    JNZ csnwFinal
    MOV CL,AL
    REPZ    CMPSW
    MOV EAX,0
    JZ  csnwDone
 csnwFinal:
    MOV AL,1
    JA  csnwDone
    MOV AL,0
    DEC EAX
 csnwDone:
    POP EDI,ESI,ECX
    RET 0
_wcsncmp   ENDP

INCLUDE "EPILOG.AS"