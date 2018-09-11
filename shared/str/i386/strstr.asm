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

EXTERN _strlen, _memcmp
PUBLIC strstr, _strstr

strstr:
_strstr PROC dest:MEMPTR,src:MEMPTR
	
	PUSH	EBX,ECX,ESI,EDI
	MOV	ESI,src
	MOV	EDI,dest
	
	XOR EAX,EAX
	TEST ESI,ESI
	JZ	_strstrDone2
	TEST EDI,EDI
	JZ	_strstrDone2
	CALL	_strlen,EDI
	MOV		EBX,EAX
	CALL	_strlen,ESI
	MOV	ECX,EAX
    ADD ESP,(2*(SIZE MWORD))
	
 _strstrLoop:
 
	MOV	AL,[ESI]
	REP	SCASB
	JNZ	_strstrNotFound
	PUSH	EAX
	MOV	EAX,EDI
	DEC	EAX
	CALL	_memcmp,EAX,ESI,EBX		;memcmp, dest, src, sizeSrc
    ADD ESP,(3*(SIZE MWORD))
	CMP	EAX,0	;Is it equal
	POP	EAX
	JNZ	_strstrLoop ;if not loop again. Starting where EDI was before the call
	
 _strstrDone:
 
	MOV	EAX,EDI
	DEC	EAX
_strstrDone2:
	POP	EDI,ESI,ECX,EBX
	RET 0
	
 _strstrNotFound:	
	MOV	EAX,0
	JMP	_strstrDone

_strstr ENDP
	
INCLUDE "EPILOG.AS"
