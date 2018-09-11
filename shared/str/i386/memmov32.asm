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

PUBLIC memmove32, _memmove32

memmove32:
_memmove32  PROC    dest:MEMPTR,src:MEMPTR,strsize:MWORD

    PUSH    ECX,ESI,EDI
    MOV ECX,strsize
    MOV ESI,src
    MOV EDI,dest
    
    LEA EAX,[ECX*4][ESI]  ;if src+size > dest then it overlaps
    CMP EAX,EDI     ;if Src+size > dest && dest > src
    SETA    AL
    CMP EDI,ESI
    SETA    AH
    AND AL,AH
    JNZ _memmove32Overlaps

    REP MOVSD

    POP EDI,ESI,ECX

    RET 0

 _memmove32Overlaps:

    PUSHF
    STD
    LEA EDI,[ECX*4][EDI][-4]  ;(Dest+len)-4
    LEA ESI,[ECX*4][ESI][-4]
    REP MOVSD

    POPF
    POP EDI,ESI,ECX

    RET 0


_memmove32  ENDP

INCLUDE "EPILOG.AS"
