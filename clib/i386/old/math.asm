PUBLIC __mul64

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

PUBLIC __div64
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

PUBLIC __add64
__add64 PROC    m64value:DWORD
    ADD EAX,m64value
    ADC EDX,0
    RET
__add64 ENDP

PUBLIC __sub64
__sub64 PROC    m64value:DWORD
    SUB EAX,m64value
    SBB EDX,0
    RET
__sub64 ENDP

