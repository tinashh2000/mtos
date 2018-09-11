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

PUBLIC	wmemcpy, _wmemcpy

wmemcpy:
_wmemcpy PROC    dest:MEMPTR,src:MEMPTR,strsize:MWORD

    PUSH    ECX,ESI,EDI

    MOV ECX,strsize
    MOV ESI,src
    MOV EDI,dest

    MOV AL,CL
    AND AL,1
    SHR ECX,1       ;Divide by 2
    REP MOVSD
    MOV CL,AL
    REP MOVSW

    MOV EAX,dest
    POP EDI,ESI,ECX
    RET 0

_wmemcpy ENDP

INCLUDE "EPILOG.AS"
