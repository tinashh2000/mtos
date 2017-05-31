BASE_IRQ    =   32

VectorContext   STRUCT
    vcEBX       MWORD   ?
    vcEFlags    MWORD   ?
    vcEIP       MWORD   ?
    vcCS        MWORD   ?
VectorContext   ENDS
