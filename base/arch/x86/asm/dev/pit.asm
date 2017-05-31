InitPIT PROC
    PUSH    EAX,EDX
    PUSHF
    CLI

IFDEF KDEBUG
    CALL    PrintStr,(_InitPIT)
ENDIF

    MOV EAX,1193180
    XOR EDX,EDX
    MOV EBX,1000
    DIV EBX
    MOV EBX,EAX

    MOV AL,36h
    OUT 43h,AL
    MOV AL,BL
    OUT 40h,AL
    MOV AL,BH
    OUT 40h,AL

    CALL   EnableIRQ,0

    STI

IFDEF KDEBUG
    CALL    PrintStrLF,(_Done)
ENDIF

    POPF

    POP EDX,EAX
    RET
InitPIT ENDP

RestorePIT  PROC
    PUSH    EAX
    MOV AL,36h
    OUT 43h,AL
    MOV AL,0
    OUT 40h,AL
    MOV AL,0
    OUT 40h,AL
    POP EAX
    RET
RestorePIT  ENDP

PITWaitForTick  PROC
    PUSH    EAX
    MOV EAX,[SystemTicks]
 pitwft:
    CMP EAX,[SystemTicks]
    JZ  pitwft
    POP EAX
    RET
PITWaitForTick  ENDP

