INCLUDE "PROLOG.AS"

EXTERN _wcslen
PUBLIC wcscmp, _wcscmp

wcscmp:
_wcscmp  PROC    str1:MWORD,str2:MWORD
    PUSH    ECX,ESI,EDI
    MOV ESI,str1
    MOV EDI,str2

    CALL    _wcslen,ESI
    ADD ESP,((SIZE MWORD))

    TEST    EAX,EAX
    JZ  cswDone

    MOV ECX,EAX
    MOV AL,CL
    AND AL,1        ;
    SHR ECX,1       ;Divide by 2
    REPZ CMPSD
    JNZ cswFinal
    MOV CL,AL
    REPZ    CMPSW
    MOV EAX,0
    JZ  cswDone
 cswFinal:
    MOV AL,1
    JA  cswDone
    MOV AL,0
    DEC EAX
 cswDone:
    POP EDI,ESI,ECX
    RET 0
_wcscmp   ENDP

INCLUDE "EPILOG.AS"