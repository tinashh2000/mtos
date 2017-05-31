INCLUDE "PROLOG.AS"
PUBLIC strnlen, _strnlen

strnlen:
_strnlen PROC    strPTR:MEMPTR,maxLen:MWORD
    PUSH    ECX,EDI
    MOV EDI,strPTR
    MOV ECX,[maxLen]
    XOR	EAX,EAX
    REPNZ SCASB
	SETNZ AL		;Not found
    ADD	EAX,[maxLen]
    SUB EAX,ECX
    DEC EAX
    POP EDI,ECX
    RET 0
_strnlen ENDP

INCLUDE "EPILOG.AS"