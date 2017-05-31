INCLUDE "PROLOG.AS"

PUBLIC _div64, __div64

_div64:
__div64 PROC    m64value:DWORD
    PUSH    EBX

    PUSH    EAX
    MOV EAX,EDX
    XOR EDX,EDX
    DIV m64value
    MOV EBX,EAX
    POP EAX
    DIV m64value
    MOV EDX,EBX

    POP EBX
    RET
__div64 ENDP

INCLUDE "EPILOG.AS"
