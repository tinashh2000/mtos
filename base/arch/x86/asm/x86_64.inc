CPUF_FPU        =   00000001h
CPUF_VME        =   00000002h
CPUF_DE         =   00000004h
CPUF_PSE        =   00000008h
CPUF_TSC        =   00000010h
CPUF_MSR        =   00000020h
CPUF_PAE        =   00000040h
CPUF_MCE        =   00000080h
CPUF_CX8        =   00000100h
CPUF_APIC       =   00000200h

CPUF_SEP        =   00000800h
CPUF_MTRR       =   00001000h
CPUF_PGE        =   00002000h
CPUF_MCA        =   00004000h
CPUF_CMOV       =   00008000h
CPUF_PAT        =   00010000h
CPUF_PSE36      =   00020000h
CPUF_PSN        =   00040000h
CPUF_CLFSH      =   00080000h

CPUF_DS         =   00200000h
CPUF_ACPI       =   00400000h
CPUF_MMX        =   00800000h
CPUF_FXSR       =   01000000h
CPUF_SSE        =   02000000h
CPUF_SSE2       =   04000000h
CPUF_SS         =   08000000h
CPUF_HTT        =   10000000h
CPUF_TH         =   20000000h

CPUF_PBE        =   80000000h


INTEL_CPU       =   1
AMD_CPU         =   2
VIA_CPU         =   3
UMC_CPU         =   4
CYRIX_CPU       =   5
TRANSMETA_CPU   =   6
CENTAUR_CPU     =   7
NEXGEN_CPU      =   8
SIS_CPU         =   9
NSC_CPU         =   10
RISE_CPU        =   11


AVX_INSTR       =   80h
MMX_INSTR       =   1
SSE_INSTR       =   2

EXUREGS STRUCT
    rxAX     MWORD ?
    rxBX     MWORD ?
    rxCX     MWORD ?
    rxDX     MWORD ?
    rxSI     MWORD ?
    rxDI     MWORD ?
    rxSP     MWORD ?
    rxBP     MWORD ?
EXUREGS ENDS
