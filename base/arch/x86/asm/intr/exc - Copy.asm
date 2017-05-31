USE32
PMException:
xchg bx,bx
    CLI
    push    eax
	push	ebx
	push	ecx
	push	edx
    push    esi
	push	edi
    push    es
    push    ds

    pop eax
    CALL	Hex32ToStr,(_ExcDS), EAX,8,9

    pop eax
    CALL	Hex32ToStr,(_ExcES), EAX,8,9

    pop eax
    CALL	Hex32ToStr,(_ExcEDI), EAX,8,9
    pop eax
    CALL	Hex32ToStr,(_ExcESI), EAX,8,9

    pop eax
    CALL	Hex32ToStr,(_ExcEDX), EAX,8,9
    pop eax
    CALL	Hex32ToStr,(_ExcECX), EAX,8,9
    pop eax
    CALL	Hex32ToStr,(_ExcEBX), EAX,8,9

    pop eax	
    CALL	Hex32ToStr,(_ExcEAX), EAX,8,9

    POP EAX	;String pushed by exc handler
    CALL    PrintStr,EAX
	
	CALL	Hex32ToStr,(_ExcEBP), EBP,8,9
	CALL	Hex32ToStr,(_ExcEBX), EBX,8,9
	CALL	Hex32ToStr,(_ExcCS), [ESP][8],8,9
	CALL	Hex32ToStr,(_ExcEFlags),[ESP][12],8,9	
	CALL	Hex32ToStr,(_ExcESP), ESP,8,9
	CALL	Hex32ToStr,(_ExcSS), SS,8,9
	CALL	Hex32ToStr,(_ExcFS), FS,8,9
	CALL	Hex32ToStr,(_ExcGS), GS,8,9
	CALL	Hex32ToStr,(_ExcCode), [ErrorCode],8,9
	CALL	Hex32ToStr,(_ExcCode), [ESP],8,9
	CALL	Hex32ToStr,(_ExcST0), [ESP][8],8,9
	CALL	Hex32ToStr,(_ExcST1), [ESP][12],8,9
	CALL	Hex32ToStr,(_ExcST2), [ESP][16],8,9
	CALL	Hex32ToStr,(_ExcST3), [ESP][20],8,9
	CALL	Hex32ToStr,(_ExcST4), [ESP][24],8,9
	CALL	Hex32ToStr,(_ExcST5), [ESP][28],8,9
	
    MOV EAX,CR0
	CALL	Hex32ToStr,(_ExcCR0), EAX,8,9

    MOV EAX,CR2
	CALL	Hex32ToStr,(_ExcCR2), EAX,8,9

    MOV EAX,CR3
	CALL	Hex32ToStr,(_ExcCR3), EAX,8,9

    CALL    PrintStr,(_ExcBlock)
    JMP $

SingleStep:
    IRETD

IRQ2:
    IRETD

BreakPoint:
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
