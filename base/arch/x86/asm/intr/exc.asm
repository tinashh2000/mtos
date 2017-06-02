USE32

SPOFS	= 0
PUBLIC	DumpRegisters
DumpRegisters:
	RET

PMException:
	CLD
	CMP	DWORD [ESP],0
	JNZ	PMEWrite
	JMP	PMEWritingDone
 PMEWrite:
	PUSH    EAX, EBX, ECX, EDX,ESI,EDI,EBP

	MOV	EBP, ESP
	PUSH	DS,ES

	MOV	EAX,LINEARDATA32
	MOV	DS,EAX
	MOV	ES,EAX


	CALL	GetCurrentThread

	CALL	GetThreadName,EAX,(_ExcThreadName)
	CALL	PrintHexD,esp
    CALL	Hex32ToStr, MWORD (_ExcEBP), [EBP][(SPOFS + 0)],MWORD (8), MWORD (9)
	CALL	PrintHexD,esp
    CALL	Hex32ToStr, MWORD (_ExcEDI), [EBP][(SPOFS + 4)],MWORD (8), MWORD (9)
    CALL	Hex32ToStr, MWORD (_ExcESI), [EBP][(SPOFS + 8)],MWORD (8), MWORD (9)
    CALL	Hex32ToStr, MWORD (_ExcEDX), [EBP][(SPOFS + 12)],MWORD (8), MWORD (9)
    CALL	Hex32ToStr, MWORD (_ExcECX), [EBP][(SPOFS + 16)],MWORD (8), MWORD (9)
    CALL	Hex32ToStr, MWORD (_ExcEBX), [EBP][(SPOFS + 20)],MWORD (8), MWORD (9)
    CALL	Hex32ToStr, MWORD (_ExcEAX), [EBP][(SPOFS + 24)],MWORD (8), MWORD (9)

	CALL    PrintStr, [EBP][(SPOFS + 28)]
	CALL    GetCurrentEXU
	CALL	PrintHexD,EAX

	CALL	Hex32ToStr,MWORD (_ExcEIP), [EBP][(SPOFS + 32)],MWORD (8), MWORD (9)
	CALL	Hex32ToStr,MWORD (_ExcCS), [EBP][(SPOFS + 36)],MWORD (8), MWORD (9)
	CALL	Hex32ToStr,MWORD (_ExcEFlags),[EBP][(SPOFS + 40)],MWORD (8), MWORD (9)
	LEA		EAX,[EBP][(SPOFS + 44)]
	CALL	Hex32ToStr,MWORD (_ExcESP), EAX,MWORD (8), MWORD (9)

	MOV	EAX,DS
	CALL	Hex32ToStr, MWORD (_ExcDS), EAX,MWORD (8), MWORD (9)
	MOV	EAX,ES
    CALL	Hex32ToStr, MWORD (_ExcES), EAX,MWORD (8), MWORD (9)
	MOV	EAX,SS
	CALL	Hex32ToStr, MWORD (_ExcSS), EAX,MWORD (8), MWORD (9)
	MOV	EAX,FS
	CALL	Hex32ToStr, MWORD (_ExcFS), EAX,MWORD (8), MWORD (9)
	MOV	EAX,GS
	CALL	Hex32ToStr, MWORD (_ExcGS), EAX,MWORD (8), MWORD (9)

	CALL	Hex32ToStr, MWORD (_ExcCode), [ErrorCode],MWORD (8), MWORD (9)
	
;	CALL	Hex32ToStr, MWORD (_ExcST0), [EBP][(SPOFS + 44)],MWORD (8), MWORD (9)
;	CALL	Hex32ToStr, MWORD (_ExcST1), [EBP][(SPOFS + 48)],MWORD (8), MWORD (9)
;	CALL	Hex32ToStr, MWORD (_ExcST2), [EBP][(SPOFS + 52)],MWORD (8), MWORD (9)
;	CALL	Hex32ToStr, MWORD (_ExcST3), [EBP][(SPOFS + 56)],MWORD (8), MWORD (9)
;	CALL	Hex32ToStr, MWORD (_ExcST4), [EBP][(SPOFS + 60)],MWORD (8), MWORD (9)
;	CALL	Hex32ToStr, MWORD (_ExcST5), [EBP][(SPOFS + 64)],MWORD (8), MWORD (9)

    MOV EAX,CR0
	CALL	Hex32ToStr, MWORD (_ExcCR0), EAX,MWORD (8), MWORD (9)
    MOV EAX,CR2
	CALL	Hex32ToStr, MWORD (_ExcCR2), EAX,MWORD (8), MWORD (9)
    MOV EAX,CR3
	CALL	Hex32ToStr, MWORD (_ExcCR3), EAX,MWORD (8), MWORD (9)
    MOV EAX,CR4
	CALL	Hex32ToStr, MWORD (_ExcCR4), EAX,MWORD (8), MWORD (9)

	CALL	PrintStr,(_LF)
	CALL	PrintStr,(_LF)
    CALL    PrintStr, MWORD (_ExcBlock)
	CALL	PrintStr,(_LF)
	CALL	PrintStr,(_LF)


	POP	DS, ES
	POP	EBP, EDI, ESI, EDX, ECX, EBX, EAX
PMEWritingDone:
	ADD	ESP,4		;Skip error code string
	STI
	JMP DebugInt


SingleStep:
	CLD
	PUSH	DWORD (0)
	JMP		PMException

IRQ2:
    IRETD

BreakPoint:
	
	CLD
	PUSH	DWORD (_Int3)
	JMP		PMException

    IRETD

Intr04:
    IRETD
Intr05:
    IRETD
Intr09:
    IRETD
Intr0F:
    IRETD
Intr11:
    IRETD
Intr12:
    IRETD
Intr13:
    IRETD
Intr14:
    IRETD
Intr15:
    IRETD
Intr16:
    IRETD
Intr17:
    IRETD
Intr18:
    IRETD
Intr19:
    IRETD
Intr1A:
    IRETD
Intr1B:
    IRETD
Intr1C:
    IRETD
Intr1D:
    IRETD
Intr1E:
    IRETD
Intr1F:
    IRETD

DivideError:
    push    DWORD (_DivideError)
    jmp PMException

InvalidOpCode:
    push    DWORD (_InvalidOpCode)
    jmp PMException

DoubleFault:
    push    DWORD (_DoubleFault)
    jmp PMException

InvalidTSS:
    push    DWORD (_InvalidTSS)
    jmp PMException

SegmentAbsent:
    push    DWORD (_SegmentAbsent)
    jmp PMException

StackFault:
    push    DWORD (_StackFault)
    jmp PMException

GPFault:
    pop [ErrorCode]
    push    DWORD (_GPFault)
    jmp PMException

PageFault:
	CLD
    pop [ErrorCode]
    push    eax,ds
    mov eax,cr0
    and eax,not 80000000h
    mov cr0,eax

    mov ax,LINEARDATA32
    mov ds,ax
    mov ebp,[110000h]
    mov edi,[111000h]
    pop ds,eax
    push    DWORD (_PageFault)
    jmp PMException

CoprocessorError:
    push    DWORD (_CoprocessorError)
    jmp PMException
