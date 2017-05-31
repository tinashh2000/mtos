PUBLIC _Scheduler, __Scheduler, __Scheduler@0

__Scheduler@0:
__Scheduler:
_Scheduler:
	INT 91h
	RET
 EXERR:
    JMP SegmentAbsent

HandleVector:
    PUSH ECX, EDX
    PUSH    EBX,ECX,EDX,ESI,EDI
    CALL MWORD [EAX]
    POP EDI,ESI,EDX,ECX,EBX
    POP EDX, ECX
    POP EAX
	IRET

Intr20:
	PUSH    EAX
	MOV EAX,Handlers + ( 32 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr21:
	PUSH    EAX
	MOV EAX,Handlers + ( 33 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr22:
	PUSH    EAX
	MOV EAX,Handlers + ( 34 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr23:
	PUSH    EAX
	MOV EAX,Handlers + ( 35 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr24:
	PUSH    EAX
	MOV EAX,Handlers + ( 36 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr25:
	PUSH    EAX
	MOV EAX,Handlers + ( 37 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr26:
	PUSH    EAX
	MOV EAX,Handlers + ( 38 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr27:
	PUSH    EAX
	MOV EAX,Handlers + ( 39 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr28:
	PUSH    EAX
	MOV EAX,Handlers + ( 40 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr29:
	PUSH    EAX
	MOV EAX,Handlers + ( 41 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr2A:
	PUSH    EAX
	MOV EAX,Handlers + ( 42 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr2B:
	PUSH    EAX
	MOV EAX,Handlers + ( 43 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr2C:
	PUSH    EAX
	MOV EAX,Handlers + ( 44 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr2D:
	PUSH    EAX
	MOV EAX,Handlers + ( 45 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr2E:
	PUSH    EAX
	MOV EAX,Handlers + ( 46 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr2F:
	PUSH    EAX
	MOV EAX,Handlers + ( 47 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr30:
	PUSH    EAX
	MOV EAX,Handlers + ( 48 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr31:
	PUSH    EAX
	MOV EAX,Handlers + ( 49 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr32:
	PUSH    EAX
	MOV EAX,Handlers + ( 50 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr33:
	PUSH    EAX
	MOV EAX,Handlers + ( 51 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr34:
	PUSH    EAX
	MOV EAX,Handlers + ( 52 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr35:
	PUSH    EAX
	MOV EAX,Handlers + ( 53 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr36:
	PUSH    EAX
	MOV EAX,Handlers + ( 54 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr37:
	PUSH    EAX
	MOV EAX,Handlers + ( 55 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr38:
	PUSH    EAX
	MOV EAX,Handlers + ( 56 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr39:
	PUSH    EAX
	MOV EAX,Handlers + ( 57 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr3A:
	PUSH    EAX
	MOV EAX,Handlers + ( 58 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr3B:
	PUSH    EAX
	MOV EAX,Handlers + ( 59 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr3C:
    PUSH    EAX
    PUSHAD
    CALL    MWORD [Handlers + ( 60 * 8)]
    POPAD
;    MOV DWORD [0FEE000B0h],0
    POP EAX
    IRET
	PUSH    EAX
	MOV EAX,Handlers + ( 60 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr3D:
	PUSH    EAX
	MOV EAX,Handlers + ( 61 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr3E:
	PUSH    EAX
	MOV EAX,Handlers + ( 62 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr3F:
	PUSH    EAX
	MOV EAX,Handlers + ( 63 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr40:
	PUSH    EAX
	MOV EAX,Handlers + ( 64 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr41:
	PUSH    EAX
	MOV EAX,Handlers + ( 65 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr42:
	PUSH    EAX
	MOV EAX,Handlers + ( 66 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr43:
	PUSH    EAX
	MOV EAX,Handlers + ( 67 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr44:
	PUSH    EAX
	MOV EAX,Handlers + ( 68 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr45:
	PUSH    EAX
	MOV EAX,Handlers + ( 69 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr46:
	PUSH    EAX
	MOV EAX,Handlers + ( 70 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr47:
	PUSH    EAX
	MOV EAX,Handlers + ( 71 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr48:
	PUSH    EAX
	MOV EAX,Handlers + ( 72 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr49:
	PUSH    EAX
	MOV EAX,Handlers + ( 73 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr4A:
	PUSH    EAX
	MOV EAX,Handlers + ( 74 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr4B:
	PUSH    EAX
	MOV EAX,Handlers + ( 75 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr4C:
	PUSH    EAX
	MOV EAX,Handlers + ( 76 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr4D:
	PUSH    EAX
	MOV EAX,Handlers + ( 77 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr4E:
	PUSH    EAX
	MOV EAX,Handlers + ( 78 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr4F:
	PUSH    EAX
	MOV EAX,Handlers + ( 79 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr50:
	PUSH    EAX
	MOV EAX,Handlers + ( 80 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr51:
	PUSH    EAX
	MOV EAX,Handlers + ( 81 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr52:
	PUSH    EAX
	MOV EAX,Handlers + ( 82 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr53:
	PUSH    EAX
	MOV EAX,Handlers + ( 83 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr54:
	PUSH    EAX
	MOV EAX,Handlers + ( 84 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr55:
	PUSH    EAX
	MOV EAX,Handlers + ( 85 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr56:
	PUSH    EAX
	MOV EAX,Handlers + ( 86 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr57:
	PUSH    EAX
	MOV EAX,Handlers + ( 87 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr58:
	PUSH    EAX
	MOV EAX,Handlers + ( 88 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr59:
	PUSH    EAX
	MOV EAX,Handlers + ( 89 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr5A:
	PUSH    EAX
	MOV EAX,Handlers + ( 90 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr5B:
	PUSH    EAX
	MOV EAX,Handlers + ( 91 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr5C:
	PUSH    EAX
	MOV EAX,Handlers + ( 92 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr5D:
	PUSH    EAX
	MOV EAX,Handlers + ( 93 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr5E:
	PUSH    EAX
	MOV EAX,Handlers + ( 94 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr5F:
	PUSH    EAX
	MOV EAX,Handlers + ( 95 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr60:
	PUSH    EAX
	MOV EAX,Handlers + ( 96 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr61:
	PUSH    EAX
	MOV EAX,Handlers + ( 97 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr62:
	PUSH    EAX
	MOV EAX,Handlers + ( 98 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr63:
	PUSH    EAX
	MOV EAX,Handlers + ( 99 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr64:
	PUSH    EAX
	MOV EAX,Handlers + ( 100 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr65:
	PUSH    EAX
	MOV EAX,Handlers + ( 101 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr66:
	PUSH    EAX
	MOV EAX,Handlers + ( 102 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr67:
	PUSH    EAX
	MOV EAX,Handlers + ( 103 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr68:
	PUSH    EAX
	MOV EAX,Handlers + ( 104 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr69:
	PUSH    EAX
	MOV EAX,Handlers + ( 105 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr6A:
	PUSH    EAX
	MOV EAX,Handlers + ( 106 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr6B:
	PUSH    EAX
	MOV EAX,Handlers + ( 107 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr6C:
	PUSH    EAX
	MOV EAX,Handlers + ( 108 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr6D:
	PUSH    EAX
	MOV EAX,Handlers + ( 109 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr6E:
	PUSH    EAX
	MOV EAX,Handlers + ( 110 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr6F:
	PUSH    EAX
	MOV EAX,Handlers + ( 111 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr70:
	PUSH    EAX
	MOV EAX,Handlers + ( 112 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr71:
	PUSH    EAX
	MOV EAX,Handlers + ( 113 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr72:
	PUSH    EAX
	MOV EAX,Handlers + ( 114 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr73:
	PUSH    EAX
	MOV EAX,Handlers + ( 115 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr74:
	PUSH    EAX
	MOV EAX,Handlers + ( 116 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr75:
	PUSH    EAX
	MOV EAX,Handlers + ( 117 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr76:
	PUSH    EAX
	MOV EAX,Handlers + ( 118 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr77:
	PUSH    EAX
	MOV EAX,Handlers + ( 119 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr78:
	PUSH    EAX
	MOV EAX,Handlers + ( 120 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr79:
	PUSH    EAX
	MOV EAX,Handlers + ( 121 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr7A:
	PUSH    EAX
	MOV EAX,Handlers + ( 122 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr7B:
	PUSH    EAX
	MOV EAX,Handlers + ( 123 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr7C:
	PUSH    EAX
	MOV EAX,Handlers + ( 124 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr7D:
	PUSH    EAX
	MOV EAX,Handlers + ( 125 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr7E:
	PUSH    EAX
	MOV EAX,Handlers + ( 126 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr7F:
	PUSH    EAX
	MOV EAX,Handlers + ( 127 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr80:
	PUSH    EAX
	MOV EAX,Handlers + ( 128 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr81:
	PUSH    EAX
	MOV EAX,Handlers + ( 129 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr82:
	PUSH    EAX
	MOV EAX,Handlers + ( 130 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr83:
	PUSH    EAX
	MOV EAX,Handlers + ( 131 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr84:
	PUSH    EAX
	MOV EAX,Handlers + ( 132 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr85:
    PUSH    EAX
;    CALL    PrintChar,"("
    MOV EAX,(Handlers + ( 133 * 8) )
;    CALL    PrintHexD,EAX
;    CALL    PrintChar,")"
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr86:
	PUSH    EAX
	MOV EAX,Handlers + ( 134 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr87:
	PUSH    EAX
	MOV EAX,Handlers + ( 135 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr88:
	PUSH    EAX
	MOV EAX,Handlers + ( 136 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr89:
	PUSH    EAX
	MOV EAX,Handlers + ( 137 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr8A:
	PUSH    EAX
	MOV EAX,Handlers + ( 138 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr8B:
	PUSH    EAX
	MOV EAX,Handlers + ( 139 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr8C:
	PUSH    EAX
	MOV EAX,Handlers + ( 140 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET









Intr8D:
	PUSH    EAX
	MOV EAX,Handlers + ( 141 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr8E:
	PUSH    EAX
	MOV EAX,Handlers + ( 142 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr8F:
	PUSH    EAX
	MOV EAX,Handlers + ( 143 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
    IRET

Intr90:
;	INC BYTE [0B8000H]
	PUSH    EAX
    PUSH    ECX,EDX
    CALL    MWORD [Handlers + ( 144 * 8)]
    POP EDX,ECX
    TEST    EAX,EAX
    JZ  Intr90Done
    CALL    SwitchContext
 Intr90Done:
    MOV DWORD [0FEE000B0],0
	POP EAX
	IRET

Intr91:
	PUSH    EAX
    PUSH    ECX,EDX
    CALL    MWORD [Handlers + ( 144 * 8)]
    POP EDX,ECX
    TEST    EAX,EAX
    JZ  Intr91Done
    CALL    SwitchContext
 Intr91Done:
	POP EAX
	IRET

Intr92:
	PUSH    EAX
	MOV EAX,Handlers + ( 146 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr93:
	PUSH    EAX
	MOV EAX,Handlers + ( 147 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr94:
	PUSH    EAX
	MOV EAX,Handlers + ( 148 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr95:
	PUSH    EAX
	MOV EAX,Handlers + ( 149 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr96:
	PUSH    EAX
	MOV EAX,Handlers + ( 150 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr97:
	PUSH    EAX
	MOV EAX,Handlers + ( 151 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr98:
	PUSH    EAX
	MOV EAX,Handlers + ( 152 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr99:
	PUSH    EAX
	MOV EAX,Handlers + ( 153 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr9A:
	PUSH    EAX
	MOV EAX,Handlers + ( 154 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr9B:
	PUSH    EAX
	MOV EAX,Handlers + ( 155 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr9C:
	PUSH    EAX
	MOV EAX,Handlers + ( 156 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr9D:
	PUSH    EAX
	MOV EAX,Handlers + ( 157 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr9E:
	PUSH    EAX
	MOV EAX,Handlers + ( 158 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

Intr9F:
	PUSH    EAX
	MOV EAX,Handlers + ( 159 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrA0:
	PUSH    EAX
	MOV EAX,Handlers + ( 160 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrA1:
	PUSH    EAX
	MOV EAX,Handlers + ( 161 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrA2:
	PUSH    EAX
	MOV EAX,Handlers + ( 162 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrA3:
	PUSH    EAX
	MOV EAX,Handlers + ( 163 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrA4:
	PUSH    EAX
	MOV EAX,Handlers + ( 164 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrA5:
	PUSH    EAX
	MOV EAX,Handlers + ( 165 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrA6:
	PUSH    EAX
	MOV EAX,Handlers + ( 166 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrA7:
	PUSH    EAX
	MOV EAX,Handlers + ( 167 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrA8:
	PUSH    EAX
	MOV EAX,Handlers + ( 168 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrA9:
	PUSH    EAX
	MOV EAX,Handlers + ( 169 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrAA:
	PUSH    EAX
	MOV EAX,Handlers + ( 170 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrAB:
	PUSH    EAX
	MOV EAX,Handlers + ( 171 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrAC:
	PUSH    EAX
	MOV EAX,Handlers + ( 172 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrAD:
	PUSH    EAX
	MOV EAX,Handlers + ( 173 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrAE:
	PUSH    EAX
	MOV EAX,Handlers + ( 174 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrAF:
	PUSH    EAX
	MOV EAX,Handlers + ( 175 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrB0:
	PUSH    EAX
	MOV EAX,Handlers + ( 176 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrB1:
	PUSH    EAX
	MOV EAX,Handlers + ( 177 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrB2:
	PUSH    EAX
	MOV EAX,Handlers + ( 178 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrB3:
	PUSH    EAX
	MOV EAX,Handlers + ( 179 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrB4:
	PUSH    EAX
	MOV EAX,Handlers + ( 180 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrB5:
	PUSH    EAX
	MOV EAX,Handlers + ( 181 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrB6:
	PUSH    EAX
	MOV EAX,Handlers + ( 182 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrB7:
	PUSH    EAX
	MOV EAX,Handlers + ( 183 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrB8:
	PUSH    EAX
	MOV EAX,Handlers + ( 184 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrB9:
	PUSH    EAX
	MOV EAX,Handlers + ( 185 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrBA:
	PUSH    EAX
	MOV EAX,Handlers + ( 186 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrBB:
	PUSH    EAX
	MOV EAX,Handlers + ( 187 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrBC:
	PUSH    EAX
	MOV EAX,Handlers + ( 188 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrBD:
	PUSH    EAX
	MOV EAX,Handlers + ( 189 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrBE:
	PUSH    EAX
	MOV EAX,Handlers + ( 190 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrBF:
	PUSH    EAX
	MOV EAX,Handlers + ( 191 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrC0:
	PUSH    EAX
	MOV EAX,Handlers + ( 192 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrC1:
	PUSH    EAX
	MOV EAX,Handlers + ( 193 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrC2:
	PUSH    EAX
	MOV EAX,Handlers + ( 194 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrC3:
	PUSH    EAX
	MOV EAX,Handlers + ( 195 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrC4:
	PUSH    EAX
	MOV EAX,Handlers + ( 196 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrC5:
	PUSH    EAX
	MOV EAX,Handlers + ( 197 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrC6:
	PUSH    EAX
	MOV EAX,Handlers + ( 198 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrC7:
	PUSH    EAX
	MOV EAX,Handlers + ( 199 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrC8:
	PUSH    EAX
	MOV EAX,Handlers + ( 200 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrC9:
	PUSH    EAX
	MOV EAX,Handlers + ( 201 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrCA:
	PUSH    EAX
	MOV EAX,Handlers + ( 202 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrCB:
	PUSH    EAX
	MOV EAX,Handlers + ( 203 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrCC:
	PUSH    EAX
	MOV EAX,Handlers + ( 204 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrCD:
	PUSH    EAX
	MOV EAX,Handlers + ( 205 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrCE:
	PUSH    EAX
	MOV EAX,Handlers + ( 206 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrCF:
	PUSH    EAX
	MOV EAX,Handlers + ( 207 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrD0:
	PUSH    EAX
	MOV EAX,Handlers + ( 208 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrD1:
	PUSH    EAX
	MOV EAX,Handlers + ( 209 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrD2:
	PUSH    EAX
	MOV EAX,Handlers + ( 210 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrD3:
	PUSH    EAX
	MOV EAX,Handlers + ( 211 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrD4:
	PUSH    EAX
	MOV EAX,Handlers + ( 212 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrD5:
	PUSH    EAX
	MOV EAX,Handlers + ( 213 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrD6:
	PUSH    EAX
	MOV EAX,Handlers + ( 214 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrD7:
	PUSH    EAX
	MOV EAX,Handlers + ( 215 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrD8:
	PUSH    EAX
	MOV EAX,Handlers + ( 216 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrD9:
	PUSH    EAX
	MOV EAX,Handlers + ( 217 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrDA:
	PUSH    EAX
	MOV EAX,Handlers + ( 218 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrDB:
	PUSH    EAX
	MOV EAX,Handlers + ( 219 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrDC:
	PUSH    EAX
	MOV EAX,Handlers + ( 220 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrDD:
	PUSH    EAX
	MOV EAX,Handlers + ( 221 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrDE:
	PUSH    EAX
	MOV EAX,Handlers + ( 222 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrDF:
	PUSH    EAX
	MOV EAX,Handlers + ( 223 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrE0:
	PUSH    EAX
	MOV EAX,Handlers + ( 224 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrE1:
	PUSH    EAX
	MOV EAX,Handlers + ( 225 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrE2:
	PUSH    EAX
	MOV EAX,Handlers + ( 226 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrE3:
	PUSH    EAX
	MOV EAX,Handlers + ( 227 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrE4:
	PUSH    EAX
	MOV EAX,Handlers + ( 228 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrE5:
	PUSH    EAX
	MOV EAX,Handlers + ( 229 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrE6:
	PUSH    EAX
	MOV EAX,Handlers + ( 230 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrE7:
	PUSH    EAX
	MOV EAX,Handlers + ( 231 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrE8:
	PUSH    EAX
	MOV EAX,Handlers + ( 232 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrE9:
	PUSH    EAX
	MOV EAX,Handlers + ( 233 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrEA:
	PUSH    EAX
	MOV EAX,Handlers + ( 234 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrEB:
	PUSH    EAX
	MOV EAX,Handlers + ( 235 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrEC:
	PUSH    EAX
	MOV EAX,Handlers + ( 236 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrED:
	PUSH    EAX
	MOV EAX,Handlers + ( 237 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrEE:
	PUSH    EAX
	MOV EAX,Handlers + ( 238 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrEF:
	PUSH    EAX
	MOV EAX,Handlers + ( 239 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrF0:
	PUSH    EAX
	MOV EAX,Handlers + ( 240 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrF1:
	PUSH    EAX
	MOV EAX,Handlers + ( 241 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrF2:
	PUSH    EAX
	MOV EAX,Handlers + ( 242 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrF3:
	PUSH    EAX
	MOV EAX,Handlers + ( 243 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrF4:
	PUSH    EAX
	MOV EAX,Handlers + ( 244 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrF5:
	PUSH    EAX
	MOV EAX,Handlers + ( 245 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrF6:
	PUSH    EAX
	MOV EAX,Handlers + ( 246 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrF7:
	PUSH    EAX
	MOV EAX,Handlers + ( 247 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrF8:
	PUSH    EAX
	MOV EAX,Handlers + ( 248 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrF9:
	PUSH    EAX
	MOV EAX,Handlers + ( 249 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrFA:
	PUSH    EAX
	MOV EAX,Handlers + ( 250 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrFB:
	PUSH    EAX
	MOV EAX,Handlers + ( 251 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrFC:
	PUSH    EAX
	MOV EAX,Handlers + ( 252 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrFD:
	PUSH    EAX
	MOV EAX,Handlers + ( 253 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrFE:
	PUSH    EAX
	MOV EAX,Handlers + ( 254 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

IntrFF:
	PUSH    EAX
	MOV EAX,Handlers + ( 255 * 8)
	CMP MWORD [EAX],0
	JNZ HandleVector
	POP EAX
	IRET

