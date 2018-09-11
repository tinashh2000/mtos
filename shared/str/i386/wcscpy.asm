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

EXTERN _wcslen
PUBLIC wcscpy, _wcscpy

wcscpy:
_wcscpy  PROC    str1:MWORD,str2:MWORD
    PUSH    ECX,ESI,EDI
    MOV ESI,str2
    MOV EDI,str1

    CALL    _wcslen,ESI
    ADD ESP,((SIZE MWORD))

    TEST    EAX,EAX
    JZ  xcswDone

    MOV ECX,EAX
    MOV AL,CL
    AND AL,1        ;
    SHR ECX,1       ;Divide by 2
    REP MOVSD

    MOV CL,AL
    REP MOVSW
	
	XOR	AX,AX
	STOSW
	
 xcswDone:
 
    POP EDI,ESI,ECX
    RET 0
_wcscpy   ENDP

INCLUDE "EPILOG.AS"
