GDTEntry    STRUC
    gdtSegLimit0 DW  ?
    gdtSegBase0  DW  ?
    gdtSegBase1  DB  ?
    gdtAttr      DB  ?
    gdtSegLimit1 DB  ?
    gdtSegBase3  DB  ?
GDTEntry    ENDS

IDTEntry    STRUC
    idtOffsetLow   DW  ?
    idtSegmentSel  DW  ?
                   DB  ?
    idtPrivileges  DB  ?
    idtOffsetHigh  DW  ?
IDTEntry    ENDS
