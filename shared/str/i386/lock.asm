;****************************************************************************************
;* Copyright (C) 2018 Tinashe Mutandagayi                                               *
;*                                                                                      *
;* This file is part of the MT-Operating System source code. The author(s) of this file *
;* is/are not liable for any damages, loss or loss of information, deaths, sicknesses   *
;* or other bad things resulting from use of this file or software, either direct or    *
;* indirect.                                                                            *
;* Terms and conditions for use and distribution can be found in the license file named *
;* LICENSE.TXT. If you distribute this file or continue using it,                       *
;* it means you understand and agree with the terms and conditions in the license file. *
;* binding this file.                                                                   *
;*                                                                                      *
;* Happy Coding :)                                                                      *
;****************************************************************************************

INCLUDE "PROLOG.AS"

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


PUBLIC UnlockVariable,_UnlockVariable, _UnlockVariable@4
_UnlockVariable@4:
_UnlockVariable:
UnlockVariable    PROC    var:MWORD
    PUSH    EBX
    MOV EBX,var
	MOV	MWORD [EBX], 0
	MOV	EAX,1
    POP EBX
	RET 0
UnlockVariable	ENDP


PUBLIC IsVariableLocked,_IsVariableLocked, _IsVariableLocked@4
_IsVariableLocked@4:
_IsVariableLocked:
IsVariableLocked    PROC    var:MWORD
    PUSH    EBX
	XOR	EAX,EAX
	CMP MWORD [EBX],0
	SETNZ AL	
    POP EBX
	RET 0
IsVariableLocked	ENDP

INCLUDE "EPILOG.AS"
