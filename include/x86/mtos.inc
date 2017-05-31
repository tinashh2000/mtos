IFDEF MTOS64
    TYPEDEF QWORD   MEMPTR
    TYPEDEF QWORD   MWORD
    TYPEDEF QWORD   BOOL
ELSE
    TYPEDEF DWORD   MEMPTR
    TYPEDEF DWORD   MWORD
    TYPEDEF DWORD   BOOL
ENDIF

TYPEDEF DWORD   INT32
TYPEDEF DWORD   UINT32
TYPEDEF QWORD   INT64
TYPEDEF QWORD   UINT64
TYPEDEF WORD    INT16
TYPEDEF WORD    UINT16
TYPEDEF BYTE    INT8
TYPEDEF BYTE    UINT8

WORDSIZE    = (SIZE MWORD)