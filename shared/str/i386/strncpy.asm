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

EXTERN _strnlen, _memset, _memcpy
PUBLIC strncpy, _strncpy

strncpy:
_strncpy	PROC	dest:MEMPTR,src:MEMPTR,strsize:MWORD
    PUSH   EBX

	CALL	_strnlen,src,strsize
    MOV EBX,EAX
	CALL	_memcpy,dest,src,EAX
    
	MOV	EAX,strsize
    SUB EAX,EBX
    ADD EBX,dest
    CALL    _memset,EBX,MWORD (0),EAX

    ADD ESP,((SIZE MWORD) * 8)

    POP EBX
    RET 0
_strncpy	ENDP

INCLUDE "EPILOG.AS"
