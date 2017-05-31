PUBLIC xCPUID, _xCPUID, _xCPUID@4

_xCPUID@4:
_xCPUID:
xCPUID  PROC    regs:MWORD
    PUSH    EBX,ECX,EDX
    MOV EBX,[regs]
    MOV EAX,[EBX].rxAX
    MOV ECX,[EBX].rxCX
    CPUID
    PUSH    EBX
    MOV EBX,[regs]
    MOV [EBX].rxAX,EAX
    MOV [EBX].rxCX,ECX
    MOV [EBX].rxDX,EDX
    MOV [EBX].rxSI,ESI
    MOV [EBX].rxDI,EDI
    POP MWORD [EBX].rxBX
    XOR EAX,EAX
    POP EDX,ECX,EBX
    RET
xCPUID  ENDP                        

PUBLIC xRDMSR, _xRDMSR, _xRDMSR@4
_xRDMSR@4:
_xRDMSR:
xRDMSR  PROC    regs:MWORD
    PUSH    EBX,ECX
    MOV EBX,[regs]
    MOV ECX,[EBX].rxCX
    RDMSR
    MOV EBX,[regs]
    MOV [EBX].rxAX,EAX
    MOV [EBX].rxDX,EDX
    POP ECX,EBX
    RET
xRDMSR  ENDP                        

PUBLIC xWRMSR, _xWRMSR, _xWRMSR@4
_xWRMSR@4:
_xWRMSR:
xWRMSR  PROC    regs:MWORD
    PUSH    EBX,ECX
    MOV EBX,[regs]
	MOV	EAX,[EBX].rxAX
	MOV	EDX,[EBX].rxDX
    MOV ECX,[EBX].rxCX
    WRMSR
    POP ECX,EBX
    RET
xWRMSR  ENDP                        

