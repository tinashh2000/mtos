FORMAT COFF32

.LANG STDCALL

USE32

INCLUDE "MTOS.INC"
INCLUDE "KERNEL.INC"
INCLUDE "THREAD\THREAD.INC"

INCLUDE "X86IMP.INC"

SEGMENT '.code' CODE


INCLUDE "X86RED.ASM"

PUBLIC DoXCHG,_DoXCHG,_DoXCHG@0
DoXCHG:
_DoXCHG:
_DoXCHG@0:
	XCHG BX,BX
	RET

PUBLIC _KernelEntryX, _KernelEntryX@0, KernelEntryX, 

PUBLIC _Init386@0,_Init386, Init386

_KernelEntryX:
NOP
NOP
NOP
MOV EAX,EBX
MOV EBX,EAX
NOP
NOP
    JMP KernelEntry

_Init386:
_Init386@0:
Init386:
    CLI
	CLTS
    MOV EAX,LINEARDATA32
    MOV DS,EAX
    MOV ES,EAX
    MOV FS,EAX
    MOV GS,EAX

	MOV	EAX,(_kUninitItemsEnd)
	SUB	EAX,(_kUninitItems)

    CALL	memset,(_kUninitItems),0,EAX
    ADD ESP,(SIZE MWORD)*3

    CALL    InitVectors
    CALL    CPUInit
    CLI
    
    XOR ECX,ECX
    MOV EAX,1
    CPUID
    BT  EDX,23
    JNC noSSE

    OR  BYTE [x86MediaFlags],MMX_INSTR
    
    BT  EDX,25
    JNC noSSE

    MOV EAX,CR0
    OR  AL,2    ;MP=1
    AND AL,NOT 0Ch  ;1100b, TS=0,EM=0,,TS will be set by Thread system
	MOV	AX,3
    MOV CR0,EAX
    
    MOV EAX,CR4
    OR  EAX,(1 SHL 9)
    MOV CR4,EAX

    OR  BYTE [x86MediaFlags],SSE_INSTR

    BT EDX,26
    JNC sseDone
    MOV DL,2

    BT ECX,9
    JNC sseDone
    MOV DL,3

    BT ECX,19
    JNC sseDone
    MOV DL,4

 sseDone:

    MOV BYTE [x86SSEVersion],DL

 noSSE:
    MOV EBX,[ESP]
    MOV EAX,DS
    MOV SS,EAX
    MOV ESP,(_KernelStack)
    PUSH    EBX

    STI
    RET

PUBLIC InitAP, _InitAP, _InitAP@0
_InitAP@0:
_InitAP:
InitAP:
    CLI
	CLTS
    MOV EAX,LINEARDATA32
    MOV DS,EAX
    MOV ES,EAX
    MOV FS,EAX
    MOV GS,EAX
    MOV ECX,ESP ;This stack came from the boot loader. It will be changed
    MOV SS,EAX  ;When the first thread is created
    MOV ESP,ECX
;    CALL    CPUInit
    TEST  BYTE [x86MediaFlags],SSE_INSTR
	JZ	initAPDone
	
    MOV EAX,CR0
    OR  AL,2    ;MP=1
    AND AL,NOT 0Ch  ;1100b, TS=0,EM=0,,TS will be set by Thread system
    MOV CR0,EAX

    MOV EAX,CR4
    OR  EAX,(3 SHL 9)
    MOV CR4,EAX
	
 initAPDone:
 
    LIDT    FWORD [IDTR32]

    RET

INCLUDE "RTC.ASM"
INCLUDE "PIT.ASM"
INCLUDE "PROCS.ASM"
INCLUDE "PORT.ASM"
INCLUDE "STR.ASM"
INCLUDE "THREAD\THREAD.ASM"
INCLUDE "INTR\INTR.ASM"

echo $
ENDS


SECTION 'init' DATA
DB "INITIALIZED DATA"
echo "Data",$

INCLUDE "X86SYS.AS"
echo "Data",$

DB "INITIALIZED DATA END"
ENDS

SECTION 'uninit' DATA
echo "UData",$
INCLUDE "X86SYS.8"
echo "UData",$
ENDS
