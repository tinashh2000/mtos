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

EXTERN _wcslen, _memcmp
PUBLIC wcsstr, _wcsstr

wcsstr:
_wcsstr PROC dest:MEMPTR,src:MEMPTR

	
	PUSH	EBX,ECX,ESI,EDI
	MOV	ESI,src
	MOV	EDI,dest

	CALL	_wcslen,EDI
	LEA	EBX,[EAX][-2]
	CALL	_wcslen,ESI
	MOV	ECX,EAX
    ADD ESP,(2*(SIZE MWORD))
	
 _wcsstrLoop:
 
	MOV	AX,[ESI]
	REP	SCASW
	JNZ	_wcsstrNotFound
	PUSH	EAX
	LEA	EAX,[EDI][-2]
	CALL	_memcmp,EAX,ESI,EBX		;memcmp, dest, src, sizeSrc
    ADD ESP,(3*(SIZE MWORD))
	CMP	EAX,0	;Is it equal
	POP	EAX
	JNZ	_wcsstrLoop ;if not loop again. Starting where EDI was before the call
	
 _wcsstrDone:
 
	MOV	EAX,EDI
	DEC	EAX
	POP	EDI,ESI,ECX,EBX
	RET 0
	
 _wcsstrNotFound:	
	MOV	EAX,0
	JMP	_wcsstrDone

_wcsstr ENDP

INCLUDE "EPILOG.AS"1