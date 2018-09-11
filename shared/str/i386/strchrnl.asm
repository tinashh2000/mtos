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

EXTERN _strlen, _memchr
PUBLIC strchrnul, _strchrnul

strchrnul:
_strchrnul	PROC	src:MEMPTR,chr:MWORD

	PUSH	EBX
    CALL    _strlen,src
	INC	EAX
	MOV	EBX,EAX
	CALL	_memchr,src,chr,EAX
	TEST	EAX,EAX
	JNZ	sncDone
	MOV	EAX,EBX	;null terminator
	ADD	EAX,src
	DEC	EAX
 sncDone:
    ADD ESP,((SIZE MWORD) * 4)

	POP	EBX
    RET 0
	
_strchrnul	ENDP

INCLUDE "EPILOG.AS"
