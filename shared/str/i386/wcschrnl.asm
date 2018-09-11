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

EXTERN _wcslen,_wmemchr
PUBLIC wcschrnul, _wcschrnul

wcschrnul:
_wcschrnul	PROC	src:MEMPTR,chr:MWORD

	PUSH	EBX
	CALL	_wcslen,src
	ADD	EAX,2
	MOV	EBX,EAX
	CALL	_wmemchr,src,chr,EAX
	TEST	EAX,EAX
    JNZ wcscnDone
	MOV	EAX,EBX	;null terminator
	ADD	EAX,src
	DEC	EAX
	DEC	EAX
 wcscnDone:

    ADD ESP,((SIZE MWORD) * 4)

	POP	EBX
    RET 0
	
_wcschrnul	ENDP
INCLUDE "EPILOG.AS"
