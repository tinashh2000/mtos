INCLUDE "PROLOG.AS"

PUBLIC _sub64, __sub64
_sub64:
__sub64 PROC    m64value:DWORD
    SUB EAX,m64value
    SBB EDX,0
    RET
__sub64 ENDP

INCLUDE "EPILOG.AS"
