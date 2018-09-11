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

EXTERN _strlen
PUBLIC strncmp, _strncmp

strncmp:
_strncmp  PROC    str1:MWORD,str2:MWORD,maxlen:MWORD
    PUSH    ECX,ESI,EDI
    MOV ESI,str1
    MOV EDI,str2

    CALL    _strlen,ESI
    ADD ESP,((SIZE MWORD))

    TEST    EAX,EAX
    JZ  scnDone

    MOV ECX,[maxlen]
	CMP	EAX,ECX
	CMOVB	ECX,EAX		;if EAX < ECX then ECX=EAX	

    AND AL,3
    SHR ECX,2
    REPZ CMPSD
    JNZ scnFinal
    MOV CL,AL
    REPZ    CMPSB

    MOV EAX,0
    JZ  scnDone
 scnFinal:    

    MOV AL,1
    JA  scnDone
    MOV AL,0
    DEC EAX

 scnDone:
    POP EDI,ESI,ECX
    RET 0
_strncmp  ENDP

INCLUDE "EPILOG.AS"
