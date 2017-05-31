INCLUDE "PROLOG.AS"

EXTERN _wmemcpy
PUBLIC wmempcpy, _wmempcpy

wmempcpy:
_wmempcpy    PROC    dest:MEMPTR,src:MEMPTR,strsize:MWORD
    CALL    _wmemcpy,dest,src,strsize
    ADD ESP,((SIZE MWORD) * 3)

    MOV EAX,strsize
    ADD EAX,EAX     ;Mul by 2
    ADD EAX,dest
    RET 0

_wmempcpy    ENDP

INCLUDE "EPILOG.AS"
