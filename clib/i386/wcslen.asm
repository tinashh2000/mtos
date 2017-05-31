INCLUDE "PROLOG.AS"
PUBLIC wcslen, _wcslen

wcslen:
_wcslen  PROC    strPTR:MWORD
    PUSH    ECX,EDI
    MOV EDI,strPTR
    MOV ECX,-1
    XOR AX,AX
    REPNZ SCASW
	MOV	EAX,-2	;cur ptr
	SUB	EAX,ECX ;-initial
    POP EDI,ECX
    RET 0
_wcslen  ENDP

INCLUDE "EPILOG.AS"