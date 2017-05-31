INCLUDE "PROLOG.AS"

EXTERN _memcpy
PUBLIC mempcpy, _mempcpy

mempcpy:
_mempcpy    PROC    dest:MEMPTR,src:MEMPTR,strsize:MWORD
    CALL    _memcpy,dest,src,strsize
    ADD ESP,((SIZE MWORD) * 3)
    MOV EAX,strsize
    ADD EAX,dest
    RET 0

_mempcpy    ENDP


INCLUDE "EPILOG.AS"
