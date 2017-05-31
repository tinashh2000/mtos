InitVectors PROC
    PUSHAD
    PUSHF
    CLI
    MOV ESI,(IDTTable)
    MOV EDI,(IDTEntries)
    MOV BX,CS
    MOV CX,8Eh
    XOR EDX,EDX
 ivLoop:
    LODSD

    MOV [EDI].idtOffsetLow,AX
    MOV BYTE [EDI].idtPrivileges,CL
    SHR EAX,16
    MOV [EDI].idtOffsetHigh,AX
    MOV [EDI].idtSegmentSel,BX

    ADD EDI,(SIZE IDTEntry)
    INC EDX
    CMP EDX,32  ;After 32 exceptions, use interrupt gate
    SETA    CH
    OR  CL,CH    
    CMP EDX,256
    JB  ivLoop

    MOV EAX,(IDTEntries)
    MOV [IDTR32][2],EAX

    LIDT    FWORD [IDTR32]

    POPF
    POPAD

    RET

InitVectors ENDP

setVector   PROC    svVector:MWORD,svHandler:MWORD,svSegmentSelector:MWORD
    PUSH    EAX,EBX
    PUSHF
    CLI
    MOV EBX,svVector
    IMUL EBX,(SIZE IDTEntry)
    ADD EBX,(IDTEntries)

    MOV EAX,svHandler
    MOV [EBX].idtOffsetLow,AX
    SHR EAX,16
    MOV [EBX].idtOffsetHigh,AX

    MOV EAX,svSegmentSelector
    MOV [EBX].idtSegmentSel,AX

    LIDT    FWORD [IDTR32]

    POPF
    POP EBX,EAX
    RET

setVector   ENDP

PUBLIC SetInterruptVector, _SetInterruptVector, _SetInterruptVector@8

_SetInterruptVector@8:
_SetInterruptVector:
SetInterruptVector	PROC	svVector:MWORD,svHandler:MWORD
    PUSH    EAX,EBX

    CLI

    MOV EBX,svVector
    IMUL    EBX,EBX,8
    ADD EBX,(Handlers)

    MOV EAX,svHandler
    MOV [EBX],EAX
    MOV [EBX][(SIZE MWORD)],CS
    STI

    POP EBX,EAX
	RET
SetInterruptVector  ENDP

INCLUDE "DEBUG.ASM"
INCLUDE "8259.ASM"
INCLUDE "INTHND.ASM"
INCLUDE "INTVEC.ASM"
INCLUDE "EXC.ASM"
INCLUDE "FPU.ASM"
