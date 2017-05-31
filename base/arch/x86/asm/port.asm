PUBLIC outportb, _outportb,_outportb@8
PUBLIC inportb, _inportb, _inportb@4

PUBLIC outportw, _outportw,_outportw@8
PUBLIC inportw, _inportw,_inportw@4

PUBLIC outportd, _outportd,_outportd@8
PUBLIC inportd, _inportd, _inportd@4

outportb:
_outportb@8:
_outportb   PROC   prt:MWORD,data:MWORD
    PUSH    EAX,EDX
    MOV EDX,prt
    MOV AL,data
    OUT DX,AL
    POP EDX,EAX
    RET
_outportb   ENDP

inportb:
_inportb@4:
_inportb   PROC   prt:MWORD
    PUSH    EDX
    XOR EAX,EAX
    MOV EDX,prt
    IN AL,DX
    POP EDX
    RET
_inportb   ENDP

outportw:
_outportw@8:
_outportw   PROC   prt:MWORD,data:MWORD
    PUSH    EAX,EDX
    MOV EDX,prt
    MOV AX,data
    OUT DX,AX
    POP EDX,EAX
    RET
_outportw   ENDP

inportw:
_inportw@4:
_inportw   PROC   prt:MWORD
    PUSH    EDX
    XOR EAX,EAX
    MOV EDX,prt
    IN AX,DX
    POP EDX
    RET
_inportw   ENDP

outportd:
_outportd@8:
_outportd   PROC   prt:MWORD,data:MWORD
    PUSH    EAX,EDX
    MOV EDX,prt
    MOV EAX,data
    OUT DX,EAX
    POP EDX,EAX
    RET
_outportd   ENDP

inportd:
_inportd@4:
_inportd   PROC   prt:MWORD
    PUSH    EDX
    XOR EAX,EAX
    MOV EDX,prt
    IN EAX,DX
    POP EDX
    RET
_inportd   ENDP

PUBLIC inportstringb, _inportstringb, _inportstringb@12
inportstringb:
_inportstringb@12:
_inportstringb	PROC prt:MWORD,dest:MEMPTR,numbytes:MWORD
	PUSH EDI,ECX
	MOV EDI,dest
	MOV ECX,numbytes
	MOV EDX,prt
	REP INSB
	POP ECX,EDI
	RET
_inportstringb	ENDP

PUBLIC outportstringb, _outportstringb, _outportstringb@12
outportstringb:
_outportstringb@12:
_outportstringb	PROC prt:MWORD,src:MEMPTR,numbytes:MWORD
	PUSH EDI,ECX
	MOV EDI,src
	MOV ECX,numbytes
	MOV	EDX,prt
	REP OUTSB
	POP ECX,EDI
	RET
_outportstringb	ENDP

PUBLIC inportstringw, _inportstringw, _inportstringw@12
inportstringw:
_inportstringw@12:
_inportstringw	PROC prt:MWORD,dest:MEMPTR,numbytes:MWORD
	PUSH EDI,ECX
	MOV EDI,dest
	MOV ECX,numbytes
	MOV EDX,prt
	SHR ECX,1
	REP INSW
	POP ECX,EDI
	RET
_inportstringw	ENDP

PUBLIC outportstringw, _outportstringw, _outportstringw@12
outportstringw:
_outportstringw@12:
_outportstringw	PROC prt:MWORD,src:MEMPTR,numbytes:MWORD
	PUSH EDI,ECX
	MOV ESI,src
	MOV ECX,numbytes
	MOV	EDX,prt
	SHR ECX,1
	REP OUTSW
	POP ECX,EDI
	RET
_outportstringw	ENDP

PUBLIC inportstringd, _inportstringd, _inportstringd@12
inportstringd:
_inportstringd@12:
_inportstringd	PROC prt:MWORD,dest:MEMPTR,numbytes:MWORD
	PUSH EDI,ECX
	MOV EDI,dest
	MOV ECX,numbytes
	MOV EDX,prt
	SHR ECX,2
	REP INSD
	POP ECX,EDI
	RET
_inportstringd	ENDP

PUBLIC outportstringd, _outportstringd, _outportstringd@12
outportstringd:
_outportstringd@12:
_outportstringd	PROC prt:MWORD,src:MEMPTR,numbytes:MWORD
	PUSH EDI,ECX
	MOV ESI,src
	MOV ECX,numbytes
	MOV	EDX,prt
	SHR ECX,2
	REP OUTSD
	POP ECX,EDI
	RET
_outportstringd	ENDP
