MAX_CPU     =   256

KERNEL_ALIGN    =   4194304
KERNEL_SIZE     =   4194304     ;4MB Kernel
REQUIRED_MEMORY =   536870912   ;512MB

LOADER_CODE16   =   08
LOADER_CODE32   =   16
LOADER_DATA32   =   24

LINEARCODE32    =   32
LINEARDATA32    =   40
DRIVERCODE32	=   48
DRIVERDATA32 	=   56
SERVICECODE32	=   64
SERVICEDATA32 	=   72
USERCODE32    	=   80
USERDATA32    	=   88

KERN_INIT       =   1
KERN_LOADFILE   =   2
KERN_SETVGAMODE =   3
KERN_CALLINT    =   4
KERN_SETBANK    =   5
KERN_WRITEFILE  =   250
KERN_EXIT       =   255

OUTPUT_CONSOLE  =   1
OUTPUT_BITFONT  =   2
OUTPUT_VPRINT   =   3


TSS STRUC
    tssBackLnk      DD  ?
    tssESP0         DD  ?
    tssSS0          DD  ?
    tssESP1         DD  ?
    tssSS1          DD  ?
    tssESP2         DD  ?
    tssSS2          DD  ?
    tssCR3          DD  ?
    tssEIP          DD  ?
    tssEFlags       DD  ?
    tssEAX          DD  ?
    tssECX          DD  ?
    tssEDX          DD  ?
    tssEBX          DD  ?
    tssESP          DD  ?
    tssEBP          DD  ?
    tssESI          DD  ?
    tssEDI          DD  ?
    tssES           DD  ?
    tssCS           DD  ?
    tssSS           DD  ?
    tssDS           DD  ?
    tssFS           DD  ?
    tssGS           DD  ?
    tssLDT          DD  ?
    tssIOMapBase    DD  ?
TSS ENDS

REGISTERS   STRUC
    rsRAX       MWORD   ?
    rsRBX       MWORD   ?
    rsRCX       MWORD   ?
    rsRDX       MWORD   ?
    rsRSI       MWORD   ?
    rsRDI       MWORD   ?
    rsRSP       MWORD   ?
    rsRBP       MWORD   ?
    rsCS        MWORD   ?
    rsDS        MWORD   ?
    rsES        MWORD   ?
    rsSS        MWORD   ?
    rsFS        MWORD   ?
    rsGS        MWORD   ?
    rsRFlags    MWORD   ?
    rsRIP       MWORD   ?

IFDEF MTOS64

    r8          MWORD   ?
    r9          MWORD   ?
    r10         MWORD   ?
    r11         MWORD   ?
    r12         MWORD   ?
    r13         MWORD   ?
    r14         MWORD   ?
    r15         MWORD   ?
ENDIF   

REGISTERS   ENDS


INCLUDE "VESA.INC"
INCLUDE "PMSTRUC.INC"
INCLUDE "INTR\INTR.INC"
INCLUDE "X86_64.INC"

LOADERPARAM STRUC
    lpCallBack      DD  ?,?
    lpCodeSeg       DD  ?
    lpDataSeg       DD  ?
    lpKernelBuffer  DD  ?
    lpDiskBufferSeg DD  ?
    lpFSBufferSeg   DD  ?
    lpFSDrives      DD  ?
    lpMemoryMap     DD  ?
    lpVesaInfo      DB  (SIZE VbeInfoBlock)     DUP(?)
    lpVesaModeInfo  DB  (SIZE ModeInfoBlock)    DUP(?)
    lpAPVector        DD  ?
    lpAPEntry         DD  ?,?
LOADERPARAM ENDS

MTDIDataBlock   STRUC
    msg_code        DD  ?   ;Used for passing messages
    opcodes         DD  ?   ;Op code of current instruction
    instr_ptr       DD  ?   ;Pointer to instructions
    instr_sel       DD  ?   ;Pointer to selector
    instr_len       DD  ?   ;Number of bytes remaining in buffer
    instr_flags     DD  ?   ;Flags baba
    Reserved        DD  ?
    reg_rax         DQ  ?
    reg_rbx         DQ  ?
    reg_rcx         DQ  ?
    reg_rdx         DQ  ?
    reg_rsp         DQ  ?
    reg_rbp         DQ  ?
    reg_rsi         DQ  ?
    reg_rdi         DQ  ?
    reg_rip         DQ  ?
    reg_rflags      DQ  ?
    reg_es          DD  ?
    reg_ds          DD  ?
    reg_ss          DD  ?
    reg_cs          DD  ?
    reg_fs          DD  ?
    reg_gs          DD  ?
MTDIDataBlock   ENDS

MemMap  STRUC
    mmpAddress  QWORD   ?
    mmpLength   QWORD   ?
    mmpType     DWORD   ?
MemMap  ENDS
