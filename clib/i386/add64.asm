INCLUDE "PROLOG.AS"

PUBLIC _add64, __add64
_add64:
__add64 PROC    m64value:DWORD
    ADD EAX,m64value
    ADC EDX,0
    RET
__add64 ENDP

INCLUDE "EPILOG.AS"
