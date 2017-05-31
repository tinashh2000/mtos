INCLUDE "PROLOG.AS"
PUBLIC strlen, _strlen

;;;;;;;;;;;;;;;;;STRLEN;;;;;;;;;;;;;;;;;;;;;;;;;;;;

strlen:
_strlen PROC    strPTR:MWORD
    PUSH    ECX,EDI
    MOV EDI,strPTR
    MOV ECX,-1
    XOR EAX,EAX
    REPNZ SCASB
    SETNZ   AL
    ADD EAX,-2
    SUB EAX,ECX
    POP EDI,ECX
    RET 0
_strlen ENDP
INCLUDE "EPILOG.AS"
