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

PUBLIC memset32, _memset32, _memset32@12

_memset32@12:
_memset32:
memset32 PROC    destx:MEMPTR,valuex:MWORD,strsizex:MWORD

    PUSH    EAX,ECX,EDX,EDI

    MOV EDI,destx
    MOV EAX,valuex
    MOV ECX,strsizex
    REP STOSD

    POP EDI,EDX,ECX,EAX

    RET 0
memset32 ENDP

PUBLIC memsetvalue, _memsetvalue, _memsetvalue@16

_memsetvalue@16:
_memsetvalue:
memsetvalue    PROC    destx:MEMPTR,chrx:MWORD,strsizex:MWORD,chrsizex:MWORD
    PUSH    EAX,EBX,ECX,EDI
    MOV EDI,destx
    MOV EAX,chrx
    CMP MWORD chrsizex,4
    JZ  _msvSizeOK
    MOV CX,AX
    SHL EAX,16
    MOV AX,CX
    CMP MWORD chrsizex,2
    JZ  _msvSizeOK
    MOV AH,AL
    ROL EAX,16
    MOV AH,AL
 _msvSizeOK:
    MOV ECX,strsizex
    MOV BL,CL
    SHR ECX,2
    REP STOSD
    MOV CL,BL
    SHR CL,1
    AND CL,1
    REP STOSW
    MOV CL,BL
    AND CL,1
    REP STOSB
    POP EDI,ECX,EBX,EAX
    RET 0
memsetvalue    ENDP

INCLUDE "EPILOG.AS"