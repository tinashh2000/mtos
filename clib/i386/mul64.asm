INCLUDE "PROLOG.AS"

PUBLIC _mul64, __mul64

_mul64:
__mul64 PROC    m64value:DWORD
    PUSH    EBX
    PUSH    EAX
    MOV EAX,EDX
    MUL [m64value]
    MOV EBX,EAX
    POP EAX
    MUL [m64value]
    ADD EDX,EBX
    POP EBX
    RET
__mul64 ENDP

INCLUDE "EPILOG.AS"
