_IRQ00:
    PUSH    EAX,ECX,EDX

    CALL    TimerHandler

    POP EDX,ECX

    TEST    EAX,EAX
    JZ  _irq0Done

    CALL    SwitchContext

 _irq0Done:
    MOV AL,20h
    OUT 20h,AL
    POP EAX
    IRET

_IRQ01:

    PUSH    EAX
    IN  AL,60h

    MOV AL,20h
    OUT 20h,AL

    POP EAX
    IRET


_IRQ02:

    PUSH    EAX
    MOV AL,20h
    OUT 20h,AL
    POP EAX
    IRET

_IRQ03:

    PUSH    EAX
    MOV AL,20h
    OUT 20h,AL
    POP EAX
    IRET

_IRQ04:

    PUSH    EAX
    MOV AL,20h
    OUT 20h,AL
    POP EAX
    IRET

_IRQ05:

    PUSH    EAX
    MOV AL,20h
    OUT 20h,AL
    POP EAX
    IRET

_IRQ06:

    PUSH    EAX
    MOV AL,20h
    OUT 20h,AL
    POP EAX
    IRET

_IRQ07:

    PUSH    EAX
    MOV AL,20h
    OUT 20h,AL
    POP EAX
    IRET


_IRQ08:
    PUSH    EAX

    MOV AL,0Ch
    OUT 70h,AL
    IN  AL,71h

    MOV AL,20h
    OUT 0A0h,AL
    OUT 20h,AL
    POP EAX
    IRET

_IRQ09:

    PUSH    EAX
    MOV AL,20h
    OUT 0A0h,AL
    OUT 20h,AL
    POP EAX
    IRET

_IRQ0A:

    PUSH    EAX
    MOV AL,20h
    OUT 0A0h,AL
    OUT 20h,AL
    POP EAX
    IRET

_IRQ0B:

    PUSH    EAX
    MOV AL,20h
    OUT 0A0h,AL
    OUT 20h,AL
    POP EAX
    IRET

_IRQ0C:

    PUSH    EAX
    MOV AL,20h
    OUT 0A0h,AL
    OUT 20h,AL
    POP EAX
    IRET

_IRQ0D:

    PUSH    EAX
    MOV AL,20h
    OUT 0A0h,AL
    OUT 20h,AL
    POP EAX
    IRET

_IRQ0E:

    PUSH    EAX
    MOV AL,20h
    OUT 0A0h,AL
    OUT 20h,AL
    POP EAX
    IRET

_IRQ0F:

    PUSH    EAX
    MOV AL,20h
    OUT 0A0h,AL
    OUT 20h,AL
    POP EAX
    IRET
