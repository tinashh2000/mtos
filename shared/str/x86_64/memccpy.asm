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

PUBLIC memccpy,_memccpy

memccpy:
_memccpy    PROC    dest:MEMPTR,src:MEMPTR,chr:MWORD,strsize:MWORD
    PUSH    ECX,ESI,EDI
    MOV EDI,dest
    MOV ESI,src
    MOV EAX,chr
    MOV ECX,strsize
 _memccpyLoop:
    CMP AL,[ESI]
    MOVSB
    JZ	_memccpyDone
    LOOP	_memccpyLoop
 _memccpyDone:
    POP EDI,ESI,ECX
    RET 0

_memccpy    ENDP

INCLUDE "EPILOG.AS"
