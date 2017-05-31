INCLUDE "PROLOG.AS"

PUBLIC memmove, _memmove

memmove:
_memmove    PROC    dest:MEMPTR,src:MEMPTR,strsize:MWORD

    PUSH    ESI,EDI

    MOV EDX,strsize
    MOV ESI,src
    MOV EDI,dest

    LEA EAX,[EDX][ESI]  ;if src+size > dest then it overlaps
    CMP EAX,EDI     ;if Src+size > dest && dest > src
    SETA    AL
    CMP EDI,ESI
    SETA    AH
    AND AL,AH
    JNZ _memmoveOverlaps	

    MOV ECX,EDX
    AND DL,3
    SHR ECX,2       ;Divide by 4
    REP MOVSD
    MOV CL,DL
    REP MOVSB
    MOV EAX,dest
    POP EDI,ESI

    RET 0

 _memmoveOverlaps:
	MOV	ECX,EDX
    PUSHF
    STD
    LEA EDI,[ECX][EDI][-4]  ;(Dest+len)-4
    LEA ESI,[ECX][ESI][-4]
    MOV AL,CL
    AND AL,3
    SHR ECX,2       ;Divice by 4
    REP MOVSD
    MOV CL,AL

    ADD EDI,3
    ADD ESI,3
    REP MOVSB

    POPF

    MOV EAX,dest
    POP EDI,ESI

    RET 0


_memmove    ENDP

INCLUDE "EPILOG.AS"
