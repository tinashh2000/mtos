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

PUBLIC memcmp, _memcmp

memcmp:
_memcmp  PROC    str1:MWORD,str2:MWORD,strsize:DWORD
    PUSH    ECX,ESI,EDI
    MOV ESI,str1
    MOV EDI,str2
	
	TEST	ESI,EDI	;If one of them is zero
	JZ	memcmpDone
	
    MOV ECX,strsize
	MOV	AL,CL
    AND AL,3
    SHR ECX,2
    REPZ CMPSD
    JNZ memcmpFinal
    MOV CL,AL
    REPZ    CMPSB

    MOV EAX,0
    JZ  memcmpDone
 memcmpFinal:    

    MOV AL,1
    JA  memcmpDone
    MOV AL,0
    DEC EAX

 memcmpDone:
    POP EDI,ESI,ECX
    RET 0
_memcmp  ENDP

INCLUDE "EPILOG.AS"
