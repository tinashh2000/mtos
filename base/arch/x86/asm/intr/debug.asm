DebugInt:
    PUSH    EBP	;We save EBP here but wont restore it from stack, at the end of this routine.
    MOV EBP,ESP

	pushad
	CALL	PrintChar,"("
	LEA	EAX,[EBP][16]
	CALL	PrintHexD,EAX
	CALL	PrintChar,")"
	popad
;    PUSH    EAX,EBX,ECX,EDX,ESI,EDI - no need to save them
;We will save the registers below, allowing them to be later modified by the debugger before they are brought back

    STI
    SUB ESP,(SIZE DEBUGCONTEXT)

;Get all registers to the DC to present them to the debugger. The debugger may change anyone of them

    MOV [ESP].dxAX,EAX
    MOV [ESP].dxCX,ECX
    MOV [ESP].dxDX,EDX
    MOV [ESP].dxBX,EBX
    MOV [ESP].dxSI,ESI
    MOV [ESP].dxDI,EDI
	MOV	[ESP].dxDS,DS
	MOV	[ESP].dxES,ES
	MOV	[ESP].dxSS,SS
	MOV	[ESP].dxCS,CS
	MOV	[ESP].dxFS,FS
	MOV	[ESP].dxGS,GS
	
	LEA	EAX,[EBP][4]	;We want ESP to point to a place before this function.
    MOV [ESP].dxSP,EAX	;Thats at the EIP
	
    MOV EAX,[EBP]			;We saved EBP on stack, save its value in DC
    MOV [ESP].dxBP,EAX
	
	MOV	EAX,[EBP][4]		;Get EIP from stack
	MOV	[ESP].dxIP,EAX

	MOV	EAX,[EBP][8]		;Get EIP from stack
	MOV	[ESP].dxCS,EAX

	MOV	EAX,[EBP][12] 
	MOV	[ESP].dxFlags,EAX
	
	MOV	EAX,CR0
	MOV	[ESP].dxCR0,EAX

;    MOV EAX,CR1
;    MOV [ESP].dxCR1,EAX

    MOV EAX,CR2
    MOV [ESP].dxCR2,EAX

	MOV	EAX,CR3
	MOV	[ESP].dxCR3,EAX

    MOV EAX,CR4
    MOV [ESP].dxCR4,EAX 
	
	MOV EAX,DR7
	AND EAX,(NOT 2)
	MOV DR7,EAX

	PUSHAD
	MOV	EAX,CR4
	CALL	PrintHexD,EAX
	POPAD

	MOV	EAX,ESP
    CALL    DebugProcess,DWORD [EBP][4], EAX

;Restore registers from DC allowing debugger changes to show on the registers
	MOV	ECX,[ESP].dxCX
	MOV	EDX,[ESP].dxDX
	MOV	EBX,[ESP].dxBX
	MOV	ESI,[ESP].dxSI
	MOV	EDI,[ESP].dxDI
;	MOV	EAX,CR0;
;	CMP	EAX,[ESP].dxCR0
;	JNZ	c

	MOV	EAX,[ESP].dxIP	;In case the debugger changed these values, as well
	MOV	[EBP][4],EAX

	MOV	EAX,[ESP].dxCS
	MOV	[EBP][8],EAX

	MOV	EAX,[ESP].dxFlags
	MOV	[EBP][12],EAX

	MOV	EAX,[ESP].dxAX

	MOV	EBP,[ESP].dxBP	;We dont restore EBP from stack but from the DebugContext

	MOV	ESP,[ESP].dxSP	;We get the value of ESP from the DebugContext.

    IRET
