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

PUBLIC wmemset,_wmemset

wmemset:
_wmemset PROC    dest:MEMPTR,chr:MWORD,strsize:MWORD
    PUSH    ECX,EDX,ESI

    MOV EDI,dest

    MOV AX,chr
    MOV CX,AX
    SHL EAX,16
    MOV AX,CX

    MOV ECX,strsize

    MOV DL,CL
    AND DL,1
    SHR ECX,1   ;Divide by 2
    REP STOSD
    MOV CL,DL
    REP STOSB

    POP ESI,EDX,ECX
    RET 0

_wmemset ENDP

INCLUDE "EPILOG.AS"
