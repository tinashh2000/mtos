;PrintChar   PROC    pcChar:MWORD
;    MOV AH,0Eh
;    MOV AL,pcChar
;    INT 10h
;    RET
;PrintChar   ENDP

PrintStr    PROC    psString:MWORD
    PUSH    EAX,ESI
    MOV ESI,psString
    XOR EAX,EAX
 _psLoop:
    LODSB
    CMP AL,0
    JZ  _psDone
    CALL    PrintChar,EAX
    JMP _psLoop
 _psDone:
    POP ESI,EAX
    RET
PrintStr    ENDP

fPrintHexD   PROC    dValue:MWORD,dFlags:MWORD
    PUSH    EAX,EBX,ECX

    MOV EBX,[dValue]
    MOV CL,8
    MOV DX,dFlags
 phdLoop:
    ROL EBX,4
    MOV AL,BL
    AND AL,0Fh
    CMP AL,9
    SETBE AH
    DEC AH
    AND AH,7
    ADD AL,AH
    ADD AL,30h
    MOVZX   EAX,AL
    CALL    PrintChar,EAX
    DEC CL
    JNZ phdLoop
    POP ECX,EBX,EAX
    RET
fPrintHexD   ENDP

PrintInt32  PROC    piValue:MWORD

LOCAL strNum:DB 32

    PUSH    EAX,EBX,ECX,EDX,ESI,EDI

    MOV EAX,[piValue]

    LEA EDI,[strNum][31]
    MOV EBX,10

    MOV BYTE [EDI],0

pi32:

    XOR EDX,EDX
    DIV EBX

    ADD DL,30h      ;Make it ASCII
    DEC EDI
    MOV [EDI],DL
    TEST    EAX,EAX
    JNZ pi32

pi32Num:

    CALL    PrintStr,EDI

    POP EDI,ESI,EDX,ECX,EBX,EAX

    RET

PrintInt32  ENDP

sPrintChar   PROC    pcChar:MWORD
    PUSH    EAX
    MOV AL,pcChar
    STOSB
    POP EAX
    RET
sPrintChar   ENDP

sPrintStr    PROC    psString:MWORD
    PUSH    EAX,ESI
    MOV ESI,psString
    XOR EAX,EAX
 _vspsLoop:
    CMP BYTE [ESI],0
    JZ  _psDone
    MOVSB
    JMP _vspsLoop
 _vspsDone:
    POP ESI,EAX
    RET
sPrintStr    ENDP

sPrintHexD   PROC    dValue:MWORD
    PUSH    EAX,EBX,ECX

    MOV EBX,[dValue]
    MOV CL,8
 vsphdLoop:
    ROL EBX,4
    MOV AL,BL
    AND AL,0Fh
    CMP AL,9
    SETBE AH
    DEC AH
    AND AH,7
    ADD AL,AH
    ADD AL,30h
    MOVZX   EAX,AL

    STOSB

    DEC CL
    JNZ vsphdLoop
    POP ECX,EBX,EAX
    RET
sPrintHexD   ENDP

sPrintInt32  PROC    piValue:MWORD

LOCAL strNum:DB 32

    PUSH    EAX,EBX,ECX,EDX,ESI

    PUSH    EDI

    MOV EAX,[piValue]
    LEA EDI,[strNum][31]    
    MOV EBX,10

    MOV BYTE [EDI],0

vspi32:

    XOR EDX,EDX
    DIV EBX

    ADD DL,30h      ;Make it ASCII
    DEC EDI
    MOV [EDI],DL
    TEST    EAX,EAX
    JNZ vspi32

vspi32Num:
    MOV EBX,EDI

    POP EDI
    CALL    sPrintStr,EBX

    POP ESI,EDX,ECX,EBX,EAX

    RET

sPrintInt32  ENDP

