CoprocessorAbsent:
IF (X86_NOFPU EQ 1)
    PUSH	DWORD (_CoprocessorAbsent)
	JMP		PMException
ENDIF

    PUSH    EAX,EBX,ECX,EDX
	JMP skps
PUSHAD	
	CALL	GetDebugThreadX

	TEST	EAX,EAX
	JZ	notDebugThread
	MOV	EBX,EAX
	CALL	GetCurrentThread
	CMP	EAX,EBX
	JNZ	notDebugThread

	PUSHAD
	CALL PrintHexD,01234h
	MOV	EAX,CR4
	CALL	PrintHexD,EAX
	MOV	EAX,CR3
	CALL	PrintHexD,EAX
    POPAD
    
	CALL    PrintStr, DWORD (_CoprocessorAbsent)
	MOV	EAX,CR0
	CALL	PrintHexD,EAX
	CALL	PrintStr,(_LF)
;	INT 3
	CLTS
    FNINIT
	NOP
	INT 3
	XCHG AX,AX

notDebugThread:
 POPAD

 skps:
    CALL    GetCurrentEXU
    LEA EBX,[EAX*4][(LastFPUThread)]  ;Get last thread to use FPU
    MOV ECX,[EBX]
    TEST    ECX,ECX                 ;If present save its registers
    JNZ smrSave

smrFirstTime:
    CLI
    CLTS
    FNINIT

	CALL    GetCurrentThread        ;If not just mark current as last to use FPU
    MOV [EBX],EAX
	OR	BYTE [EAX][(SIZE MWORD)].bNew, 2

IFDEF X86SSE
    TEST    BYTE [x86MediaFlags],AVX_INSTR
    JNZ  smrSSE
    TEST    BYTE [x86MediaFlags],SSE_INSTR
    JZ smrDone
 smrSSE:

	XORPD	XMM0,XMM0
	MOVDQA	XMM1,XMM0
	MOVDQA	XMM2,XMM0
	MOVDQA	XMM3,XMM0
	MOVDQA	XMM4,XMM0
	MOVDQA	XMM5,XMM0
	MOVDQA	XMM6,XMM0
	MOVDQA	XMM7,XMM0

ENDIF
;endif x86sse
 smrDone:

    POP EDX,ECX,EBX,EAX
    IRET

 smrSave:        

    CLI
    CLTS

    CALL    GetCurrentThread        ;If not just mark current as last to use FPU
	CMP	EAX,ECX	;is current thread last one to access FPU
	JZ	smrDone	;if so dont save

    TEST    BYTE [x86MediaFlags],AVX_INSTR
    JNZ smrSaveSSE
    TEST    BYTE [x86MediaFlags],SSE_INSTR
    JNZ smrSaveSSE

	LEA	ECX,[ECX][(SIZE MWORD)].FPUState	;Go past thread signature. (SIZE MWORD) and point to FPUState
    FNSAVE  [ECX]   ;Save SSE state

    MOV [EBX],EAX   ;;Save in last FPU current 

	TEST	BYTE [EAX][(SIZE MWORD)].bNew, 2
	JZ	smrFirstTime
 smrRestoreFPU:
   	LEA	EAX,[EAX][(SIZE MWORD)].FPUState	;Go past thread signature. (SIZE MWORD) and point to FPUStat
    FRSTOR [EAX]

    JMP smrDone

 smrSaveSSE:

   	LEA	ECX,[ECX][(SIZE MWORD)].FPUState	;Go past thread signature. (SIZE MWORD) and point to FPUState
    FXSAVE  [ECX]      ;Save SSE state

    MOV [EBX],EAX

	TEST	BYTE [EAX][(SIZE MWORD)].bNew, 2
	JZ	smrFirstTime

smrRestoreSSE:
	LEA	EAX,[EAX][(SIZE MWORD)].FPUState	;Go past thread signature. (SIZE MWORD) and point to FPUState
    FXRSTOR [EAX]

    JMP smrDone

