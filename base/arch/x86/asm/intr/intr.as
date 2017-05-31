IDTEntries  LABEL   DWORD
            DB  (SIZE IDTEntry)*256 DUP(0)

IDTR32Size = $-IDTEntries-1

IDTR32  LABEL   FWORD
            DW  IDTR32Size
            DD  0

IDTTable    LABEL   DWORD
            DD  DivideError
            DD  SingleStep
            DD  IRQ2
            DD  BreakPoint
            DD  Intr04
            DD  Intr05
            DD  InvalidOpCode
            DD  CoprocessorAbsent
            DD  DoubleFault
            DD  Intr09
            DD  InvalidTSS
            DD  SegmentAbsent
            DD  StackFault
            DD  GPFault
            DD  PageFault
            DD  Intr0F
            DD  CoprocessorError
            DD  Intr11
            DD  Intr12
            DD  Intr13
            DD  Intr14
            DD  Intr15
            DD  Intr16
            DD  Intr17
            DD  Intr18
            DD  Intr19
            DD  Intr1A
            DD  Intr1B
            DD  Intr1C
            DD  Intr1D
            DD  Intr1E
            DD  Intr1F
            DD  _IRQ00
            DD  _IRQ01
            DD  _IRQ02
            DD  _IRQ03
            DD  _IRQ04
            DD  _IRQ05
            DD  _IRQ06
            DD  _IRQ07
            DD  _IRQ08
            DD  _IRQ09
            DD  _IRQ0A
            DD  _IRQ0B
            DD  _IRQ0C
            DD  _IRQ0D
            DD  _IRQ0E
            DD  _IRQ0F
            DD Intr30
            DD Intr31
            DD Intr32
            DD Intr33
            DD Intr34
            DD Intr35
            DD Intr36
            DD Intr37
            DD Intr38
            DD Intr39
            DD Intr3A
            DD Intr3B
            DD Intr3C
            DD Intr3D
            DD Intr3E
            DD Intr3F
            DD Intr40
            DD Intr41
            DD Intr42
            DD Intr43
            DD Intr44
            DD Intr45
            DD Intr46
            DD Intr47
            DD Intr48
            DD Intr49
            DD Intr4A
            DD Intr4B
            DD Intr4C
            DD Intr4D
            DD Intr4E
            DD Intr4F
            DD Intr50
            DD Intr51
            DD Intr52
            DD Intr53
            DD Intr54
            DD Intr55
            DD Intr56
            DD Intr57
            DD Intr58
            DD Intr59
            DD Intr5A
            DD Intr5B
            DD Intr5C
            DD Intr5D
            DD Intr5E
            DD Intr5F
            DD Intr60
            DD Intr61
            DD Intr62
            DD Intr63
            DD Intr64
            DD Intr65
            DD Intr66
            DD Intr67
            DD Intr68
            DD Intr69
            DD Intr6A
            DD Intr6B
            DD Intr6C
            DD Intr6D
            DD Intr6E
            DD Intr6F
            DD Intr70
            DD Intr71
            DD Intr72
            DD Intr73
            DD Intr74
            DD Intr75
            DD Intr76
            DD Intr77
            DD Intr78
            DD Intr79
            DD Intr7A
            DD Intr7B
            DD Intr7C
            DD Intr7D
            DD Intr7E
            DD Intr7F
            DD Intr80
            DD Intr81
            DD Intr82
            DD Intr83
            DD Intr84
            DD Intr85
            DD Intr86
            DD Intr87
            DD Intr88
            DD Intr89
            DD Intr8A
            DD Intr8B
            DD Intr8C
            DD Intr8D
            DD Intr8E
            DD Intr8F
            DD Intr90
            DD Intr91
            DD Intr92
            DD Intr93
            DD Intr94
            DD Intr95
            DD Intr96
            DD Intr97
            DD Intr98
            DD Intr99
            DD Intr9A
            DD Intr9B
            DD Intr9C
            DD Intr9D
            DD Intr9E
            DD Intr9F
            DD IntrA0
            DD IntrA1
            DD IntrA2
            DD IntrA3
            DD IntrA4
            DD IntrA5
            DD IntrA6
            DD IntrA7
            DD IntrA8
            DD IntrA9
            DD IntrAA
            DD IntrAB
            DD IntrAC
            DD IntrAD
            DD IntrAE
            DD IntrAF
            DD IntrB0
            DD IntrB1
            DD IntrB2
            DD IntrB3
            DD IntrB4
            DD IntrB5
            DD IntrB6
            DD IntrB7
            DD IntrB8
            DD IntrB9
            DD IntrBA
            DD IntrBB
            DD IntrBC
            DD IntrBD
            DD IntrBE
            DD IntrBF
            DD IntrC0
            DD IntrC1
            DD IntrC2
            DD IntrC3
            DD IntrC4
            DD IntrC5
            DD IntrC6
            DD IntrC7
            DD IntrC8
            DD IntrC9
            DD IntrCA
            DD IntrCB
            DD IntrCC
            DD IntrCD
            DD IntrCE
            DD IntrCF
            DD IntrD0
            DD IntrD1
            DD IntrD2
            DD IntrD3
            DD IntrD4
            DD IntrD5
            DD IntrD6
            DD IntrD7
            DD IntrD8
            DD IntrD9
            DD IntrDA
            DD IntrDB
            DD IntrDC
            DD IntrDD
            DD IntrDE
            DD IntrDF
            DD IntrE0
            DD IntrE1
            DD IntrE2
            DD IntrE3
            DD IntrE4
            DD IntrE5
            DD IntrE6
            DD IntrE7
            DD IntrE8
            DD IntrE9
            DD IntrEA
            DD IntrEB
            DD IntrEC
            DD IntrED
            DD IntrEE
            DD IntrEF
            DD IntrF0
            DD IntrF1
            DD IntrF2
            DD IntrF3
            DD IntrF4
            DD IntrF5
            DD IntrF6
            DD IntrF7
            DD IntrF8
            DD IntrF9
            DD IntrFA
            DD IntrFB
            DD IntrFC
            DD IntrFD
            DD IntrFE
            DD IntrFF
