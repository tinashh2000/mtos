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

EXTERN _strlen
PUBLIC strrchr, _strrchr

strrchr:
_strrchr    PROC    block:MEMPTR,chr:MWORD
	PUSHFD
	PUSH	ECX,EDI
	MOV	EDI,block
	CALL	_strlen,EDI
	ADD	ESP,(SIZE MWORD)
	MOV	ECX,EAX
	ADD	EDI,ECX
	DEC	EDI	
    MOV AL,chr
	STD
	REPNZ	SCASB
	MOV	EAX,0
	JNZ	srcDone
	MOV	EAX,EDI
	DEC	EAX
 srcDone:	
	POP	EDI,ECX
	POPFD
    RET 0

_strrchr	ENDP

INCLUDE "EPILOG.AS"
