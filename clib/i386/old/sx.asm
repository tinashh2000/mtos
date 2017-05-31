    CALL    _strlen,DWORD (_mystr)
    INT 20h

_strlen PROC    strPTR:DWORD
    PUSH    ECX,EDI
    MOV EDI,strPTR
    MOV ECX,-1
    XOR EAX,EAX
    REPNZ SCASB
    SETNZ   AL
    ADD EAX,-2
    SUB EAX,ECX
    POP EDI,ECX
    RET
_strlen ENDP

_mystr  DB "HelloWorld",0
