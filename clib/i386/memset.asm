INCLUDE "PROLOG.AS"

PUBLIC memset, _memset, memset_opt, _memset_opt

memset:
_memset PROC    dest:MEMPTR,chr:MWORD,strsize:MWORD

    PUSH    ECX,EDX,EDI

    MOV EDI,dest

    MOV AL,chr
    MOV AH,AL
    MOV CX,AX
    SHL EAX,16
    MOV AX,CX

    MOV ECX,strsize

    MOV DL,CL
    AND DL,3
    SHR ECX,2   ;Divide by 4
    REP STOSD
    MOV CL,DL
    REP STOSB

    POP EDI,EDX,ECX
    MOV EAX,dest

    RET 0

_memset ENDP

memset_opt:
_memset_opt PROC    dest:MEMPTR,chr:MEMPTR,strsize:MWORD
    PUSH    ECX, EDX, EDI

	MOV		EAX,01010101h
	MOVZX	ECX,BYTE [chr]
	IMUL	EAX,ECX

	MOV	EDX, strsize
	MOV	EDI,dest
	CMP	EDX, 128
	JB	_mso_bytetrans

;	MOVD	XMM0,EAX

	DB	066h,0fh,06eh, 0c0h	;;Code for movd xmm0,eax

	PSHUFD	XMM0,XMM0,0	;Replicate lower dword across all 128-bits

	MOVUPS  [EDI], XMM0	;unaligned [EDI] = xmm0
	ADD	EDX,EDI		;Go to end of buffer
	ADD	EDI,16		;; align
	AND	EDI, 0FFFFFFF0h	;align, edi is now aligned
	SUB	EDX,EDI		;end of buffer - edi
	

	CMP	EDX,128
	JB	_mso_bytetrans
	MOV	ECX,EDX
	SHR	ECX,7
 _mso_loop:
	MOVDQA	[EDI][0],XMM0
	MOVDQA	[EDI][16],XMM0
	MOVDQA	[EDI][32],XMM0
	MOVDQA	[EDI][48],XMM0
	MOVDQA	[EDI][64],XMM0
	MOVDQA	[EDI][80],XMM0
	MOVDQA	[EDI][96],XMM0
	MOVDQA	[EDI][112],XMM0

	ADD	EDI,128

	DEC	ECX
	JNZ	_mso_loop

 _mso_bytetrans:
	MOV	ECX,EDX
	AND	ECX,7Fh	;just the last 127bytes
 _mso_bytetrans_loop:
	SHR	ECX,2
	REP	STOSD
	MOV	CL,DL
	AND	CL,3
	REP	STOSB

 _mso_done:

    MOV EAX,dest
    POP EDI, EDX, ECX
    RET 0


_memset_opt ENDP


INCLUDE "EPILOG.AS"
