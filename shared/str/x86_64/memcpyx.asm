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
PUBLIC	memcpy_sse,_memcpy_sse

memcpy_sse:
_memcpy_sse	PROC	dest:MWORD,src:MWORD,numbytes:MWORD
	PUSH	ECX,ESI,EDI
			MOV	ESI,src
			MOV	EDI,dest
			MOV	ECX,numbytes
			CMP	ECX,128
			JB	mmsse128
	llloop:
			MOVDQU	XMM0,[ESI]
			MOVDQU	XMM1,[ESI+10h]
			MOVDQU	XMM2,[ESI+20h]
			MOVDQU	XMM3,[ESI+30h]
			MOVDQU	XMM4,[ESI+40h]
			MOVDQU	XMM5,[ESI+50h]
			MOVDQU	XMM6,[ESI+60h]
			MOVDQU	XMM7,[ESI+70h]
			MOVDQU	[EDI],XMM0
			MOVDQU	[EDI+10h],XMM1
			MOVDQU	[EDI+20h],XMM2
			MOVDQU	[EDI+30h],XMM3
			MOVDQU	[EDI+40h],XMM4
			MOVDQU	[EDI+50h],XMM5
			MOVDQU	[EDI+60h],XMM6
			MOVDQU	[EDI+70h],XMM7
			ADD	ESI,(16*8)
			ADD	EDI,(16*8)
			SUB	ECX,128
			CMP	ECX,128
			JAE	llloop
 mmsse128:	
	CALL	_memcpy,EDI,ESI,ECX
	ADD	ESP,3 * (SIZE MWORD)
	POP	EDI,ESI,ECX
	RET 0
_memcpy_sse	ENDP

INCLUDE "EPILOG.AS"
