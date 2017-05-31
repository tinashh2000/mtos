_InitRTC        DB  "Initializing RTC...",0
_InitPIT        DB  "Initializing PIT...",0
_InitDevices    DB  "Initializing Devices...",0
_Done           DB  "Done!",0
_KernelError    DB  "System Error. Can not continue",13,10,0
_UserEnd        DB  "Terminated by user",13,10,0
_GPFault        DB  "General protection fault ",13,10,0
_DivideError    DB  "Divide error ",13,10,0
_InvalidOpCode  DB  "Invalid OpCode ",13,10,0
_DoubleFault    DB  "Double Fault ",13,10,0
_InvalidTSS     DB  "Invalid TSS ",13,10,0
_SegmentAbsent  DB  "Segment Absent ",13,10,0
_StackFault     DB  "Stack Fault ",13,10,0
_PageFault      DB  "Page Fault ",13,10,0
_CoprocessorError   DB  "Coprocessor Error ",13,10,0
_CoprocessorAbsent  DB  "Coprocessor Absent ",13,10,0


_ExcBlock   LABEL
            DB  "EAX:"
_ExcEAX     DB  "???????? "
            DB  "EBX:"
_ExcEBX     DB  "???????? "
            DB  "ECX:"
_ExcECX     DB  "???????? "
            DB  "EDX:"
_ExcEDX     DB  "???????? "
            DB  "ESI:"
_ExcESI     DB  "???????? ",13,10 

            DB  "EDI:"
_ExcEDI     DB  "???????? "
            DB  "EBP:"
_ExcEBP     DB  "???????? "
            DB  "ESP:"
_ExcESP     DB  "???????? "
            DB  "EIP:"
_ExcEIP     DB  "???????? "
            DB  "CS :"
_ExcCS      DB  "???????? ",13,10

            DB  "DS :"
_ExcDS      DB  "???????? "
            DB  "SS :"
_ExcSS      DB  "???????? "
            DB  "ES :"
_ExcES      DB  "???????? "
            DB  "FS :"
_ExcFS      DB  "???????? "
            DB  "GS :"
_ExcGS      DB  "???????? ",13,10

            DB  "CR0:"
_ExcCR0     DB  "???????? "
            DB  "CR2:"
_ExcCR2     DB  "???????? "
            DB  "CR3:"
_ExcCR3     DB  "???????? "
            DB  "CR4:"
_ExcCR4     DB  "???????? "
			DB  "ERR:"
_ExcCode    DB  "???????? "
            DB  "EFLAGS:"
_ExcEFlags  DB  "???????? ",13,10

;			DB  "Stack0:"
;_ExcST0     DB  "???????? "
;            DB  "Stack1:"
;_ExcST1     DB  "???????? "
;            DB  "Stack2:"
;_ExcST2     DB  "????????"
;            DB  "Stack3:"
;_ExcST3     DB  "????????",13,10
;            DB  "Stack4:"
;_ExcST4     DB  "????????"
;            DB  "Stack5:"
;_ExcST5     DB  "????????",13,10
			DB	"ThreadName:"
_ExcThreadName	DB 17 DUP(0)
            DB  0
_LF     DB 13,10,0

_InvalidImage   DB  "Invalid Image",13,10,0
_ImageError     DB  "Image Error",13,10,0

_HelloWorld     DB  "Hello World!",13,10,0

_KernelFile     DB  "KERNEL.SYS",0
_KernelName     DB  "KERNEL"
_Blank			DB	0


_Int1		DB	"Int1",0
_Int3		DB	"Int3",0
ErrorCode   DD  0

_kStackPtr  DD  (_KernelStack)
            DD  LINEARDATA32

INCLUDE "X86_64.AS"
INCLUDE "INTR\INTR.AS"

