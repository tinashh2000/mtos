IsAPICPresent   PROC
    PUSH    EBX,ECX,EDX
    MOV EAX,1
    XOR ECX,ECX
    CPUID

    TEST    EDX,CPUF_APIC
    SETNZ   AL
    MOVZX   EAX,AL
    POP EDX,ECX,EBX
    RET
IsAPICPresent   ENDP

PUBLIC InitAPIC, _InitAPIC, _InitAPIC@0

_InitAPIC@0:
_InitAPIC:
InitAPIC    PROC
    PUSHAD
    CALL    ApicInit
    POPAD
    RET
InitAPIC    ENDP

DeInitAPIC  PROC
    CALL    ApicDisableTimer
    CALL    EnableAPIC,0
    RET
DeInitAPIC  ENDP

EnableAPIC  PROC    flag:MWORD

    PUSHAD      ;Enable from spurious IV
    CALL    ApicReadRegister,0F0h

    AND EAX,NOT (0100h) ;Clear the bit first

    CMP flag,0
    SETZ    CL
    MOVZX ECX,CL
    DEC ECX
    AND ECX,100h
    OR  EAX,ECX

    CALL    ApicWriteRegister,0F0h,EAX

    POPAD
    RET

EnableAPIC  ENDP

ReadAPICMSR PROC
    CALL    ReadMSR,01Bh
    RET
ReadAPICMSR ENDP

WriteAPICMSR    PROC  wamValueLow:MWORD,wamValueHigh:MWORD
    CALL    WriteMSR,01Bh,wamValueLow,wamValueHigh
    RET
WriteAPICMSR    ENDP

ReadMSR PROC    rmRegister:MWORD
    PUSH    ECX
    MOV ECX,rmRegister
    RDMSR
    POP ECX
    RET
ReadMSR ENDP

WriteMSR    PROC    wmRegister:MWORD,wmValueLow:MWORD,wmValueHigh:MWORD
    PUSH    ECX
    MOV EAX,wmValueLow
    MOV EDX,wmValueHigh
    MOV ECX,wmRegister
    WRMSR
    POP ECX
    RET
WriteMSR    ENDP

ApicWriteRegister   PROC    address:MWORD,value:MWORD
    CALL    GetCurrentEXU
    MOV EBX,[apicBase][EAX*4]
    ADD EBX,address
    MOV EAX,[value]
    MOV [EBX],EAX
    RET
ApicWriteRegister   ENDP

ApicReadRegister    PROC    address:MWORD
    CALL    GetCurrentEXU
    MOV EBX,[apicBase][EAX*4]
    ADD EBX,address
    MOV EAX,[EBX]    
    RET
ApicReadRegister    ENDP

ApicSendIPI PROC targetAPIC:MWORD,vector:MWORD
    MOV EAX,targetAPIC
;    SHL EAX,
    RET
ApicSendIPI ENDP

ApicGetBase	PROC
	CALL    GetCurrentEXU
	IMUL	EAX,(SIZE MWORD)
	ADD	EAX,(apicBase)
	MOV	EAX,[EAX]
	RET
ApicGetBase	ENDP

ApicInit	PROC
    PUSHF
    CLI

IFDEF KDEBUG
    CALL    PrintStr,(_initAPIC)
ENDIF

    CALL    EnableAPIC,1

	CALL    GetCurrentEXU

	MOV	ESI,EAX
	IMUL	ESI,(SIZE MWORD)
	ADD	ESI,(apicBase)

	MOV	ECX,1Bh
	RDMSR
	AND	EAX,NOT (0FFFh)
	MOV	EBX,EAX
	MOV	[ESI],EAX

	MOV	DWORD [EBX][APIC_SPURIOUS],0FFh | APIC_SW_ENABLE

	MOV	DWORD [EBX][APIC_DFR],0FFFFFFFFh

    MOV DWORD [EBX][APIC_TASKPRIOR],0

	CALL	ApicInitTimer

IFDEF KDEBUG
    CALL    PrintStr,(_Done)
ENDIF

    POPF
	RET
ApicInit	ENDP

ApicInitTimer	PROC

	CALL	ApicGetBase
	MOV	EBX,EAX

	MOV	DWORD [EBX]APIC_LVT_TMR,90h	;init APIC timer
    MOV DWORD [EBX]APIC_TMRDIV,APIC_TIMER_DIV64

    MOV ESI,[SystemTicks]
    LEA EAX,[ESI][100]      ;Try to time 100ms. 1sec might be too much

    TEST    ESI,ESI
    JZ  aitTimeOut

    MOV DWORD [EBX]APIC_TMRINITCNT,-1   ;we want to measure how much APIC
    MOV ECX,-1                          ;timer changes over 100ms
    MOV EDX,2
 aitPollPIT:
    SUB ECX,1
    SBB EDX,0
    JBE aitTimeOut
    CMP EAX,[SystemTicks]
    JGE aitPollPIT

	MOV	DWORD [EBX]APIC_LVT_TMR,APIC_DISABLE	;Stop counter
    MOV EDI,[EBX]APIC_TMRCURRCNT

    PUSHF
    CLI
    MOV EBX,[SystemTicks]
    SUB EBX,ESI     ;Number of ticks

    MOV EAX,-1
    SUB EAX,EDI
    INC EAX
    XOR EDX,EDX
    SHL EAX,6
    MUL EBX

    MOV EBX,1000
    XOR EDX,EDX
    DIV EBX

    MOV EBX,64
    SHR EAX,6
    CMP EAX,EBX
    CMOVA   EAX,EBX

    CALL    ApicSetTimer,APIC_TIMER_DIV64,EAX,90h

    POPF
 aitDone:
	RET
 aitTimeOut:
    CALL    PrintStr,(_apicTimeout)
    JMP aitDone
ApicInitTimer  ENDP
	
ApicSetTimer	PROC	divisor:MWORD,initCount:MWORD,vector:MWORD
	PUSHF
	CLI
	CALL	ApicGetBase	
	MOV	EBX,EAX

	MOV	EAX,divisor
	MOV	[EBX]APIC_TMRDIV,EAX

	MOV	EAX,initCount
    MOV [EBX]APIC_TMRINITCNT,EAX

	MOV	EAX,vector
    OR  EAX,TMR_PERIODIC
	MOV	[EBX]APIC_LVT_TMR,EAX
	POPF
	RET
ApicSetTimer	ENDP

ApicDisableTimer    PROC
	MOV	DWORD [EBX]APIC_LVT_TMR,APIC_DISABLE	;Stop counter
    RET
ApicDisableTimer    ENDP

