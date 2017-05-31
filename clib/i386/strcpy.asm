INCLUDE "PROLOG.AS"

EXTERN _strlen
PUBLIC strcpy, _strcpy

strcpy:
_strcpy  PROC    str1:MWORD,str2:MWORD
    PUSH    ECX,ESI,EDI
    MOV ESI,str2
    MOV EDI,str1

    CALL    _strlen,ESI
    ADD ESP,((SIZE MWORD))

    TEST    EAX,EAX
    JZ  xscDone

    MOV ECX,EAX
    SHR ECX,2

    AND AL,3

    REP MOVSD

    MOV CL,AL
    REP MOVSB
	
	MOV	AL,0
	STOSB
 xscDone:
    POP EDI,ESI,ECX
    RET 0
_strcpy  ENDP

INCLUDE "EPILOG.AS"
