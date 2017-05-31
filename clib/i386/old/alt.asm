PUBLIC _wcsnlen

_wcsnlen PROC    strPTR:MEMPTR,maxLen:MWORD
    PUSH    ECX,EDI
    MOV EDI,strPTR
    MOV ECX,[maxLen]
    XOR EAX,EAX
    REPNZ SCASW
    MOV EAX,[maxLen]
    SUB EAX,ECX
    DEC EAX
    POP EDI,ECX
    RET 0
_wcsnlen ENDP

