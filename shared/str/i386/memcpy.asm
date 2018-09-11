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


PUBLIC memcpy, _memcpy, memcpy_opt, _memcpy_opt


memcpy:
_memcpy PROC    dest:MEMPTR,src:MEMPTR,strsize:MWORD

    PUSH    ECX,ESI,EDI

    MOV ECX,strsize
    MOV ESI,src
    MOV EDI,dest
   
    MOV AL,CL
    AND AL,3
    SHR ECX,2       ;Divide by 4
    REP MOVSD
    MOV CL,AL
    REP MOVSB

    MOV EAX,dest
    POP EDI,ESI,ECX
    RET 0


_memcpy ENDP

memcpy_opt:
_memcpy_opt PROC    dest:MEMPTR,src:MEMPTR,strsize:MWORD
    PUSH    ECX, EDX, ESI, EDI

    MOV EAX,strsize
    MOV ESI,src
    MOV EDI,dest

	CMP	EAX, 256		;Dont try to optimize lengths < 256
	JB	_mcpo_bytetrans

	TEST	ESI,15	;Is it aligned to 16 bytes
	JZ	_mcpo_srcaligned_checkdest
	TEST	EDI,15
	JZ	_mcpo_destaligned_srcnot

;;None of them is aligned, so we align the source 

	MOV	EDX,ESI		;Align the source.
	AND	EDX,15		;No need to check length, length >=32
	MOV	ECX,16
	SUB	ECX,EDX
	
	SUB	EAX,ECX	;Dont forget to update the remaining bytes
	MOV	DL,CL
	SHR	ECX,2
	REP	MOVSD	;first copy 4bytes at a time
	MOV	CL,DL
	AND	CL,3
	REP	MOVSB		;After this, addresses now aligned
;;Fall into srcaligned_destnot
 _mcpo_srcaligned_destnot:
	MOV	ECX,EAX
	SHR	ECX,7
 _mcpo_srcaligned_destnot_loop:	

 cmp ecx, 0x100000
 jbe xyxy
 sti
 int 3
 xyxy:
	PREFETCHNTA [128][ESI]; //SSE2 PREFETCH
	PREFETCHNTA [160][ESI];
	PREFETCHNTA [192][ESI];
	PREFETCHNTA [224][ESI];
	  
	MOVDQA	XMM1,[ESI][0]
	MOVDQA	XMM0,[ESI][16]
	MOVDQA	XMM2,[ESI][32]
	MOVDQA	XMM3,[ESI][48]
	MOVDQA	XMM4,[ESI][64]
	MOVDQA	XMM5,[ESI][80]
	MOVDQA	XMM6,[ESI][96]
	MOVDQA	XMM7,[ESI][112]

	MOVDQU	[EDI][0],XMM1
	MOVDQU	[EDI][16],XMM0
	MOVDQU	[EDI][32],XMM2
	MOVDQU	[EDI][48],XMM3
	MOVDQU	[EDI][64],XMM4
	MOVDQU	[EDI][80],XMM5
	MOVDQU	[EDI][96],XMM6
	MOVDQU	[EDI][112],XMM7

	ADD	ESI,128
	ADD	EDI,128

	DEC	ECX
	JNZ	_mcpo_srcaligned_destnot_loop

	JMP	_mcpo_bytetrans1

 _mcpo_destaligned_srcnot:
	MOV	ECX,EAX
	SHR	ECX,7
 _mcpo_destaligned_srcnot_loop:	
	MOVDQU	XMM0,[ESI][0]
	MOVDQU	XMM1,[ESI][16]
	MOVDQU	XMM2,[ESI][32]
	MOVDQU	XMM3,[ESI][48]
	MOVDQU	XMM4,[ESI][64]
	MOVDQU	XMM5,[ESI][80]
	MOVDQU	XMM6,[ESI][96]
	MOVDQU	XMM7,[ESI][112]

	MOVDQA	[EDI][0],XMM0
	MOVDQA	[EDI][16],XMM1
	MOVDQA	[EDI][32],XMM2
	MOVDQA	[EDI][48],XMM3
	MOVDQA	[EDI][64],XMM4
	MOVDQA	[EDI][80],XMM5
	MOVDQA	[EDI][96],XMM6
	MOVDQA	[EDI][112],XMM7

	ADD	ESI,128
	ADD	EDI,128

	DEC	ECX
	JNZ	_mcpo_destaligned_srcnot_loop

	JMP	_mcpo_bytetrans1
	
 _mcpo_srcaligned_checkdest:
	TEST	EDI,15
	JNZ	_mcpo_srcaligned_destnot

 _mcpo_srcaligned_destaligned:
	MOV	ECX,EAX
	SHR	ECX,7
 _mcpo_srcaligned_destaligned_loop:	
	MOVDQA	XMM0,[ESI][0]
	MOVDQA	XMM1,[ESI][16]
	MOVDQA	XMM2,[ESI][32]
	MOVDQA	XMM3,[ESI][48]
	MOVDQA	XMM4,[ESI][64]
	MOVDQA	XMM5,[ESI][80]
	MOVDQA	XMM6,[ESI][96]
	MOVDQA	XMM7,[ESI][112]

	MOVDQA	[EDI][0],XMM0
	MOVDQA	[EDI][16],XMM1
	MOVDQA	[EDI][32],XMM2
	MOVDQA	[EDI][48],XMM3
	MOVDQA	[EDI][64],XMM4
	MOVDQA	[EDI][80],XMM5
	MOVDQA	[EDI][96],XMM6
	MOVDQA	[EDI][112],XMM7

	ADD	ESI,128
	ADD	EDI,128

	DEC	ECX
	JNZ	_mcpo_srcaligned_destaligned_loop

;Fall into
 _mcpo_bytetrans1:
 	AND	EAX,127
 _mcpo_bytetrans:
	MOV	ECX,EAX
 _mcpo_bytetrans_loop:
	SHR	ECX,2
	REP	MOVSD
	MOV	CL,AL
	AND	CL,3
	REP	MOVSB
 _mcpo_done:
    MOV EAX,dest
    POP EDI, ESI, EDX, ECX
    RET 0


_memcpy_opt ENDP

INCLUDE "EPILOG.AS"