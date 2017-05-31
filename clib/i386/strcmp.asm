INCLUDE "PROLOG.AS"

EXTERN _strlen

PUBLIC strcmp, _strcmp

strcmp:
_strcmp  PROC    str1:MWORD,str2:MWORD

    PUSH    ECX,ESI,EDI
    MOV ESI,str1
    MOV EDI,str2

    CALL    _strlen,ESI
    ADD ESP,((SIZE MWORD))

    TEST    EAX,EAX
    JZ  scDone

    MOV ECX,EAX
    AND AL,3
    SHR ECX,2
    REPZ CMPSD
    JNZ scFinal
    MOV CL,AL
    REPZ    CMPSB

    MOV EAX,0
    JZ  scDone
 scFinal:    

    MOV AL,1
    JA  scDone
    MOV AL,0
    DEC EAX

 scDone:
    POP EDI,ESI,ECX
    RET 0

_strcmp  ENDP

INCLUDE "EPILOG.AS"
