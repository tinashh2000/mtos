INCLUDE "PROLOG.AS"

PUBLIC	wmemcpy, _wmemcpy

wmemcpy:
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

INCLUDE "EPILOG.AS"
