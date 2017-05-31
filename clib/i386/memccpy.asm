INCLUDE "PROLOG.AS"

PUBLIC memcpy,_memccpy

memcpy:
_memccpy    PROC    dest:MEMPTR,src:MEMPTR,chr:MWORD,strsize:MWORD
    PUSH    ECX,ESI,EDI
    MOV EDI,dest
    MOV ESI,src
    MOV EAX,chr
    MOV ECX,strsize
 _memccpyLoop:
    CMP AL,[ESI]
    MOVSB
    JZ	_memccpyDone
    LOOP	_memccpyLoop
 _memccpyDone:
    POP EDI,ESI,ECX
    RET 0

_memccpy    ENDP

INCLUDE "EPILOG.AS"
