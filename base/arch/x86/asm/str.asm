PUBLIC _memset32, _memset32@12

_memset32@12:
_memset32 PROC    destx:MEMPTR,valuex:MWORD,strsizex:MWORD

    PUSH    EAX,ECX,EDX,EDI

    MOV EDI,destx
    MOV EAX,valuex
    MOV ECX,strsizex
    REP STOSD

    POP EDI,EDX,ECX,EAX

    RET 0
_memset32 ENDP


PUBLIC _memsetvalue, _memsetvalue@16

_memsetvalue@16:
_memsetvalue    PROC    destx:MEMPTR,chrx:MWORD,strsizex:MWORD,chrsizex:MWORD
    PUSH    EAX,EBX,ECX,EDI
    MOV EDI,destx
    MOV EAX,chrx
    CMP MWORD chrsizex,4
    JZ  _msvSizeOK
    MOV CX,AX
    SHL EAX,16
    MOV AX,CX
    CMP MWORD chrsizex,2
    JZ  _msvSizeOK
    MOV AH,AL
    ROL EAX,16
    MOV AH,AL
 _msvSizeOK:
    MOV ECX,strsizex
    MOV BL,CL
    SHR ECX,2
    REP STOSD
    MOV CL,BL
    SHR CL,1
    AND CL,1
    REP STOSW
    MOV CL,BL
    AND CL,1
    REP STOSB
    POP EDI,ECX,EBX,EAX
    RET 0
_memsetvalue    ENDP

