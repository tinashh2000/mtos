PUBLIC _memmove

_memmove    PROC    dest:MEMPTR,src:MEMPTR,strsize:MWORD

    PUSH    ESI,EDI

    MOV EDX,strsize
    MOV ESI,src
    MOV EDI,dest

    LEA EAX,[EDX][ESI]  ;if src+size > dest then it overlaps
    CMP EAX,EDI     ;if Src+size > dest && dest > src
    SETA    AL
    CMP EDI,ESI
    SETA    AH
    AND AL,AH
    JNZ _memmoveOverlaps	

    MOV ECX,EDX
    AND DL,3
    SHR ECX,2       ;Divide by 4
    REP MOVSD
    MOV CL,DL
    REP MOVSB
    MOV EAX,dest
    POP EDI,ESI

    RET 0

 _memmoveOverlaps:
	MOV	ECX,EDX
    PUSHF
    STD
    LEA EDI,[ECX][EDI][-4]  ;(Dest+len)-4
    LEA ESI,[ECX][ESI][-4]
    MOV AL,CL
    AND AL,3
    SHR ECX,2       ;Divice by 4
    REP MOVSD
    MOV CL,AL

    ADD EDI,3
    ADD ESI,3
    REP MOVSB

    POPF

    MOV EAX,dest
    POP EDI,ESI

    RET 0


_memmove    ENDP


PUBLIC _memmove32

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


PUBLIC _memcpy

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


PUBLIC _wmemcpy

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


PUBLIC _mempcpy

_mempcpy    PROC    dest:MEMPTR,src:MEMPTR,strsize:MWORD
    CALL    _memcpy,dest,src,strsize
    ADD ESP,((SIZE MWORD) * 3)
    MOV EAX,strsize
    ADD EAX,dest
    RET 0

_mempcpy    ENDP

_wmempcpy    PROC    dest:MEMPTR,src:MEMPTR,strsize:MWORD
    CALL    _wmemcpy,dest,src,strsize
    ADD ESP,((SIZE MWORD) * 3)

    MOV EAX,strsize
    ADD EAX,EAX     ;Mul by 2
    ADD EAX,dest
    RET 0

_wmempcpy    ENDP


PUBLIC _memccpy

_memccpy    PROC    dest:MEMPTR,src:MEMPTR,chr:MWORD,strsize:MWORD
    PUSH    ECX,ESI,EDI
    MOV EDI,dest
    MOV ESI,src
    MOV EAX,chr
    MOV ECX,strsize
 _memccpyLoop:
    CMP AL,[ESI]
    MOVSB
    JZ  _memccpyDone
    LOOP    _memccpyLoop
 _memccpyDone:
    POP EDI,ESI,ECX
    RET 0

_memccpy    ENDP


PUBLIC _memset

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

    RET 0

_memset ENDP

PUBLIC _wmemset

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


;;;;;;;;;;;;;;;;;MEMCHR;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PUBLIC _memchr

_memchr	PROC	block:MEMPTR,chr:MWORD,initSize:MWORD
	PUSH	EDI
	MOV	ECX,initSize
	MOV	EDI,block
	MOV	AL,chr
	
	REPNZ	SCASB
	MOV	EAX,0
	JNZ	mcDone
	MOV	EAX,EDI
	DEC	EAX
 mcDone:	
	POP	EDI
    RET 0

_memchr	ENDP


PUBLIC _rawmemchr

_rawmemchr	PROC	block:MEMPTR,chr:MWORD
	CALL	_memchr,block,chr,-1
    ADD ESP,((SIZE MWORD) * 3)
    RET 0

_rawmemchr	ENDP


PUBLIC _memrchr

_memrchr    PROC    block:MEMPTR,chr:MWORD,initSize:MWORD
	PUSHFD
	PUSH	ECX,EDI
	MOV	ECX,initSize
	MOV	EDI,block
	ADD	EDI,ECX
	DEC	EDI	
    MOV AL,chr
	STD
	REPNZ	SCASB
	MOV	EAX,0
	JNZ	mrcDone
	MOV	EAX,EDI
	DEC	EAX
 mrcDone:	
	POP	EDI,ECX
	POPFD
    RET 0

_memrchr	ENDP

PUBLIC _wmemrchr

_wmemrchr    PROC    block:MEMPTR,chr:MWORD,initSize:MWORD
	PUSHFD
	PUSH	ECX,EDI
	MOV	ECX,initSize
	MOV	EDI,block
	ADD	EDI,ECX
	SUB EDI,2
    MOV AX,chr
	STD
	REPNZ	SCASW
	MOV	EAX,0
	JNZ	wmrcDone
	MOV	EAX,EDI
	SUB EAX,2
	SHR EAX,1
 wmrcDone:	
	POP	EDI,ECX
	POPFD
    RET 0

_wmemrchr	ENDP

PUBLIC _memcmp

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

PUBLIC	_memcpy_sse
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

PUBLIC _mtos_memdiff
 
_mtos_memdiff  PROC    str1:MWORD,str2:MWORD,strsize:DWORD
    PUSH    ECX,ESI,EDI
    MOV ESI,str1
    MOV EDI,str2
	
	TEST	ESI,EDI	;If one of them is zero
	JZ	pmemcmpDone
	
    MOV ECX,strsize
	MOV	AL,CL
    AND AL,3
    SHR ECX,2
    REPZ CMPSD
    JNZ pmemcmpNE
    MOV CL,AL
    REPZ    CMPSB
	JNZ	pmemcmpFinal
	XOR	EAX,EAX
	JMP	pmemcmpDone

 pmemcmpFinal:    
	DEC	EDI
	MOV	EAX,EDI		;Calculate how many bytes 
	SUB	EAX,str2
 pmemcmpDone:
    POP EDI,ESI,ECX
    RET 0
 pmemcmpNE:
	SUB	EDI,4
	SUB	ESI,4
	MOV	ECX,4
	REP	CMPSB
	JMP	pmemcmpFinal
_mtos_memdiff  ENDP
