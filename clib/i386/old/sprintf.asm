PUBLIC _sprintf

_sprintf:
sprintf    PROC
    PUSH    EBX,ESI,EDI
    LEA EBX,[ESP][(WORDSIZE * 4)]     ;[EBX] = first param
    MOV EDI,SS:[EBX]    ;Destination
    MOV ESI,SS:[EBX][(WORDSIZE)] ;Format
    ADD EBX,WORDSIZE * 2    ;Point to 3rd param
 sprintfLoop:
	LODSB
	CMP	AL,"%"
    JZ  sprintfFormatSpec
	STOSB
 sprintfFormatNext:
	CMP	AL,0
    JNZ sprintfLoop
    POP EDI,ESI,EBX
    RET 0

 sprintfFormatSpec:

    LODSB
	CMP	AL,"i"
    JZ  sprintfPrintInt
	CMP	AL,"f"
    JZ  sprintfPrintDouble
	CMP	AL,"c"
    JZ  sprintfPrintChar
	CMP	AL,"x"
    JZ  sprintfPrintHex
	CMP	AL,"s"
    JZ  sprintfPrintStr
	MOV	AH,"%"
	XCHG	AL,AH
	STOSW
    JMP sprintfFormatNext

 sprintfPrintInt:

    CALL    sprintInt32,SS:[EBX]

    ADD EBX,(SIZE MWORD)

    JMP sprintfFormatNext

 sprintfPrintDouble:
;   CALL    sprintDouble,SS:[EBX]
    ADD EBX,(SIZE MWORD)
    JMP sprintfFormatNext

 sprintfPrintChar:
    CALL    sprintChar,SS:[EBX]
    ADD EBX,(SIZE MWORD)
    JMP sprintfFormatNext

 sprintfPrintHex:
    CALL    sprintHexD,SS:[EBX]
    ADD EBX,(SIZE MWORD)
    JMP sprintfFormatNext
	
 sprintfPrintStr:
    CALL    sprintStr,SS:[EBX]
    ADD EBX,(SIZE MWORD)
    JMP sprintfFormatNext

sprintf    ENDP


PUBLIC _xsprintf

_xsprintf:
xsprintf    PROC
    PUSH    EBX,ESI,EDI
    LEA EBX,[ESP][(WORDSIZE * 4)]     ;[EBX] = first param
    MOV EDI,SS:[EBX]    ;Destination
    MOV ESI,SS:[EBX][(WORDSIZE)] ;Format
    ADD EBX,WORDSIZE * 2    ;Point to 3rd param
    PUSH    EDI
 xsprintfLoop:
	LODSB
	CMP	AL,"%"
    JZ  xsprintfFormatSpec
	STOSB
 xsprintfFormatNext:
	CMP	AL,0
    JNZ xsprintfLoop

    POP EAX
    POP EDI,ESI,EBX
    RET 0

 xsprintfFormatSpec:

    LODSB
	CMP	AL,"i"
    JZ  xsprintfPrintInt
	CMP	AL,"f"
    JZ  xsprintfPrintDouble
	CMP	AL,"c"
    JZ  xsprintfPrintChar
	CMP	AL,"x"
    JZ  xsprintfPrintHex
	CMP	AL,"s"
    JZ  xsprintfPrintStr
	MOV	AH,"%"
	XCHG	AL,AH
	STOSW
    JMP xsprintfFormatNext

 xsprintfPrintInt:

    CALL    sprintInt32,SS:[EBX]

    ADD EBX,(SIZE MWORD)

    JMP xsprintfFormatNext

 xsprintfPrintDouble:
;   CALL    sprintDouble,SS:[EBX]
    ADD EBX,(SIZE MWORD)
    JMP xsprintfFormatNext

 xsprintfPrintChar:
    CALL    sprintChar,SS:[EBX]
    ADD EBX,(SIZE MWORD)
    JMP xsprintfFormatNext

 xsprintfPrintHex:
    CALL    sprintHexD,SS:[EBX]
    ADD EBX,(SIZE MWORD)
    JMP xsprintfFormatNext
	
 xsprintfPrintStr:
    CALL    sprintStr,SS:[EBX]
    ADD EBX,(SIZE MWORD)
    JMP xsprintfFormatNext

xsprintf    ENDP

