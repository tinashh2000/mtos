PUBLIC AcquireVariableLock, _AcquireVariableLock, _AcquireVariableLock@4

_AcquireVariableLock@4:
_AcquireVariableLock:
AcquireVariableLock    PROC    var:MWORD
    PUSH    EBX
    MOV EBX,var
 alCheck:
	MOV	AL,0
	MOV AH,1
    LOCK
    CMPXCHG BYTE [EBX],AH  ;Compare AL,cSection, if equal cSection = AH
	SETZ	AL
	AND	EAX,1
    POP EBX
	RET 0
AcquireVariableLock	ENDP

PUBLIC LockVariable,_LockVariable, _LockVariable@4
_LockVariable@4:
_LockVariable:
LockVariable    PROC    var:MWORD
    PUSH    EBX
    MOV EBX,var
 vlCheck:
	MOV	AL,0
	MOV AH,1
    LOCK
    CMPXCHG BYTE [EBX],AH  ;Compare AL,cSection, if equal cSection = AH
	JZ	vlDone
;	PAUSE
	JMP	vlCheck
	
 vlDone:

	MOV	EAX,1
    POP EBX
	RET 0
LockVariable	ENDP

