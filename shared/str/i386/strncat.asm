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

EXTERN _strlen, _strnlen,_memcpy

PUBLIC strncat, _strncat

strncat:
_strncat    PROC dest:MEMPTR, src:MEMPTR,tsize:MWORD
	PUSH EBX,ESI
	
	MOV	EBX,dest
	CALL	_strlen,dest
	ADD EBX,EAX		;EBX = end of dest

    CALL    _strnlen,src,tsize	;size of src, or cut it to tsize

	CALL	_memcpy,EBX,src,EAX

    ADD ESP,((SIZE MWORD) * 6)

	MOV	BYTE [EBX][EAX],0
	MOV EAX,dest
	POP	ESI, EBX
    RET 0
_strncat 	ENDP

INCLUDE "EPILOG.AS"
