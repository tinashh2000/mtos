INCLUDE "PROLOG.AS"

PUBLIC wmemset,_wmemset

wmemset:
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

INCLUDE "EPILOG.AS"
