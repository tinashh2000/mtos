PUBLIC _SetPagesBase@4

_SetPagesBase@4:
SetPagesBase    PROC pages:MWORD
    PUSH    EAX
    MOV EAX,pages
    MOV CR3,EAx
    POP EAX
    RET
SetPagesBase    ENDP


PUBLIC DisableInterrupts, _DisableInterrupts, _DisableInterrupts@0
PUBLIC EnableInterrupts,_EnableInterrupts,_EnableInterrupts@0

_DisableInterrupts@0:
_DisableInterrupts:
DisableInterrupts:
    CLI
    RET

_EnableInterrupts@0:
_EnableInterrupts:
EnableInterrupts:
    STI
    RET

;thisCPUID       DB  12 DUP(0)
amdCPUID    DB  "AuthenticAMD"
intelCPUID  DB  "GenuineIntel"

PUBLIC	GetEXUTicks, _GetEXUTicks, _GetEXUTicks@0
_GetEXUTicks@0:
_GetEXUTicks:
GetEXUTicks PROC
    RDTSC
    RET
GetEXUTicks ENDP

PUBLIC  GetEXUSpeed,_GetEXUSpeed,_GetEXUSpeed@0

_GetEXUSpeed@0:
_GetEXUSpeed:
GetEXUSpeed PROC
    
    RET
GetEXUSpeed ENDP

PUBLIC  _GetFeatures@0
_GetFeatures@0:
GetFeatures PROC
    XOR EAX,EAX
    CPUID
    MOV [CPUString],EBX
    MOV [CPUString][4],EDX
    MOV [CPUString][8],ECX
    MOV BYTE [CPUString][12],0

    MOV EAX,1
    CPUID
;    TEST    EDX,(1 SHL 16)
;    SETNZ   BYTE [xPSE]
;    TEST    EDX,(1 SHL
    RET
GetFeatures ENDP

PUBLIC  _SwitchGlobal@4

_SwitchGlobal@4:

SwitchGlobalPages   PROC    flag:DWORD
    PUSH    EAX,EBX
    XOR EAX,EAX
    CMP DWORD [flag],0
    SETZ   AL
    DEC EAX
    AND EAX,(1 SHL 7)
    MOV EBX,CR4
    AND EBX,NOT (1 SHL 7)
    OR  EBX,EAX
    MOV CR4,EBX    
    POP EBX,EAX
    RET
SwitchGlobalPages   ENDP


PUBLIC  _SwitchPAE@4

_SwitchPAE@4:
SwitchPAE   PROC    flag:DWORD
    PUSH    EAX,EBX
    XOR EAX,EAX
    CMP DWORD [flag],0
    SETZ   AL
    DEC EAX
    AND EAX,(1 SHL 5)
    MOV EBX,CR4
    AND EBX,NOT (1 SHL 5)
    OR  EBX,EAX
    MOV CR4,EBX
    POP EBX,EAX
    RET
SwitchPAE   ENDP

PUBLIC  _SwitchPSE@4

_SwitchPSE@4:
SwitchPSE   PROC    flag:DWORD
    PUSH    EAX,EBX
    XOR EAX,EAX
    CMP DWORD [flag],0
    SETZ   AL
    DEC EAX
    AND EAX,(1 SHL 4)
    MOV EBX,CR4
    AND EBX,NOT (1 SHL 4)
    OR  EBX,EAX
    MOV CR4,EBX
    POP EBX,EAX
    RET
SwitchPSE   ENDP

PUBLIC _SwitchPaging@4

_SwitchPaging@4:

SwitchPaging    PROC    flag:DWORD
    PUSH    EAX,EBX
    CMP DWORD [flag],0
    SETZ AL
    MOVZX   EAX,AL
    DEC EAX
    AND EAX,(1 SHL 31)
    MOV EBX,CR0
    AND EBX,NOT (1 SHL 31)
    OR  EBX,EAX
    MOV CR0,EBX
    POP EBX,EAX
    RET
SwitchPaging    ENDP

IFDEF MTOS64
SwitchLongMode  PROC    flag:DWORD
    PUSH    EAX,EBX,ECX
    CMP DWORD [flag],0
    SETZ    BL
    MOVZX   EBX,BL
    DEC EBX
    AND EBX,(1 SHL 8)

    MOV ECX,0C0000080h
    RDMSR
    AND EAX,NOT (1 SHL 8)
    OR  EAX,EBX
    
    WRMSR
    POP ECX,EBX,EAX
    RET
SwitchLongMode  ENDP

InitLongMode    PROC
    PUSHAD
    MOV EAX,110000h
    MOV CR3,EAX
    CALL    switchPAE,1
    CALL    switchLongMode,1
    CALL    switchPaging,1
    POPAD
    RET
InitLongMode    ENDP

SwitchToLongMode  PROC  arg:DWORD
    CALL    initLongMode

    MOV EAX,Code
    SHL EAX,4
    ADD EAX,(pm64Code)

    MOV DWORD [arg],0

    PUSH    DWORD (LINEARCODE64)
    PUSH    EAX
    RETFD
USE64
 pm64Code:
    RET
SwitchToLongMode  ENDP

ENDIF

IFDEF MTOS64
    USE64
ELSE
    USE32
ENDIF

CPUInit PROC

    CALL    _8259Init
    CALL    initPIT
    CALL    initRTC
    STI
;    CALL    PITWaitForTick
;    CALL    initAPIC
    RET

CPUInit ENDP

CPUReInit PROC

    CALL    _8259Init
    CALL    initPIT
    CALL    initRTC
;    CALL    initAPIC
    RET

CPUReInit ENDP

CPUDeInit   PROC

    PUSHF
    CLI
    CALL    _8259DeInit
    CALL    restorePIT
    CALL    shutRTC
;    CALL    DeInitAPIC
    POPF
    RET

CPUDeInit   ENDP

PUBLIC _DumpRegs@0

_DumpRegs@0:
_DumpRegs:
    PUSH    EAX,ECX,EDX

    LEA EAX,[ESP][12]
    PUSH    EAX
    MOV EAX,[ESP][12]
    PUSH    EBP
    PUSH    EDI
    PUSH    ESI
    PUSH    EDX
    PUSH    ECX
    PUSH    EBX
    PUSH    EAX
    PUSH    MWORD (_RegsFmt)
    CALL    printf
    ADD ESP,(SIZE MWORD) * 9

    POP EDX,ECX,EAX
    RET

INCLUDE "CPUID.ASM"

_RegsFmt   DB   13,10,"EAX:%x, EBX:%x, ECX:%x, EDX:%x"
           DB   13,10,"ESI:%x, EDI:%x, EBP:%x, ESP:%x"
           DB   13,10,0
