INCLUDE "PROLOG.AS"

EXTERN _wcslen
PUBLIC wcscpy, _wcscpy

wcscpy:
_wcscpy  PROC    str1:MWORD,str2:MWORD
    PUSH    ECX,ESI,EDI
    MOV ESI,str2
    MOV EDI,str1

    CALL    _wcslen,ESI
    ADD ESP,((SIZE MWORD))

    TEST    EAX,EAX
    JZ  xcswDone

    MOV ECX,EAX
    MOV AL,CL
    AND AL,1        ;
    SHR ECX,1       ;Divide by 2
    REP MOVSD

    MOV CL,AL
    REP MOVSW
	
	XOR	AX,AX
	STOSW
	
 xcswDone:
 
    POP EDI,ESI,ECX
    RET 0
_wcscpy   ENDP

INCLUDE "EPILOG.AS"
