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

EXTERN _memcpy
PUBLIC mempcpy, _mempcpy

mempcpy:
_mempcpy    PROC    dest:MEMPTR,src:MEMPTR,strsize:MWORD
    CALL    _memcpy,dest,src,strsize
    ADD ESP,((SIZE MWORD) * 3)
    MOV EAX,strsize
    ADD EAX,dest
    RET 0

_mempcpy    ENDP


INCLUDE "EPILOG.AS"
