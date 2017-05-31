Save8259    PROC
    PUSH    EAX
    IN  AL,0A1h
    MOV AH,AL
    IN  AL,021h
    MOV [V8259],AX
    POP EAX
    RET
Save8259    ENDP

Restore8259 PROC

    PUSH    EAX
    MOV AX,[V8259]
    OUT 21h,AL

	JMP	$+2
	JMP	$+2

    MOV AL,AH
    OUT 0A1h,AL

	JMP	$+2
	JMP	$+2

    POP EAX
    RET

Restore8259 ENDP

_8259Init    PROC
    PUSHF
    CLI

    CALL    Save8259

    MOV AL,11h
    OUT 020h,AL
	JMP	$+2
	JMP	$+2
    OUT 0A0h,AL
	JMP	$+2
	JMP	$+2

    MOV AL,32
    OUT 21h,AL
	JMP	$+2
	JMP	$+2

    MOV AL,40
    OUT 0A1h,AL
	JMP	$+2
	JMP	$+2

	MOV	AL,4
	OUT	21h,AL
	JMP	$+2
	JMP	$+2

	MOV	AL,2h
	OUT	0A1h,AL
	JMP	$+2
	JMP	$+2

	MOV	AL,1h
	OUT	21h,AL
	JMP	$+2
	JMP	$+2

	OUT	21h,AL
	
;    CALL    Restore8259
;    MOV AL,0
;    OUT 21h,AL
;    MOV AL,0FFh
;    OUT 0A1h,AL

    MOV AL,NOT 4    ;Disable all interrupts except IRQ2 on master PIC
    OUT 21h,AL
    MOV AL,0FFh     ;Disable all interrupts on slave PIC
    OUT 0A1h,AL

    POPF
    RET
_8259Init    ENDP

_8259DeInit  PROC

    PUSHF
    CLI

    MOV AL,11h
    OUT 020h,AL
    OUT 0A0h,AL

    MOV AL,8
    OUT 21h,AL

    MOV AL,70h
    OUT 0A1h,AL

    CALL    Restore8259
    
    POPF
    RET
    
    RET
_8259DeInit  ENDP


acknowledgeIRQ  PROC    irqNum:DWORD

    PUSH    EAX
    MOV EAX,[irqNum]
    CMP EAX,8
    JAE aiCascade
    OR  AL,60h
    MOV AL,20h
    OUT 20h,AL
    POP EAX
    RET
 aiCascade:
    MOV AL,20h
    OUT 0A0h,AL
    OUT 020h,AL
    POP EAX
    RET

    SUB EAX,8
    OR  AL,60h
    OUT 0A0h,AL
    MOV AL,62h
    OUT 20h,AL
    POP EAX
    RET
    
acknowledgeIRQ  ENDP

EnableIRQ   PROC    irqNum:DWORD
    PUSH    EAX,ECX,EDX
    PUSHF
    CLI
    IN  AL,21h
    IN  AL,0A1h

    MOV EDX,021h
    MOV EAX,0A1h
    MOV CL,[irqNum]
    CMP CL,8
    CMOVAE  EDX,EAX   ;Enable on 0A1h

    AND CL,7

    MOV AH,1
    SHL AH,CL
    NOT AH
    IN  AL,DX
    AND AL,AH
    OUT DX,AL
    POPF
    POP EDX,ECX,EAX
    RET
EnableIRQ   ENDP

DisableIRQ  PROC    irqNum:DWORD
    PUSH    EAX,ECX,EDX
    PUSHF
    CLI
    MOV EDX,021h
    MOV EAX,0A1h
    MOV CL,[irqNum]
    CMP CL,8
    CMOVAE  EDX,EAX   ;Enable on 0A1h

    IN  AL,DX

    AND CL,7
    MOV AH,1
    SHL AH,CL
    OR  AL,AH
    OUT DX,AL
    POPF
    POP EDX,ECX,EAX
    RET
DisableIRQ  ENDP

PUBLIC _Disable8259@0

_Disable8259@0:
Disable8259 PROC
    MOV AL,0FFh
    OUT 0A1h,AL
    OUT 021h,AL
    RET
Disable8259 ENDP
