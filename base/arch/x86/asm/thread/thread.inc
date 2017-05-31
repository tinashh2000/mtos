COMMENT #
THREAD_TIME_SLICE           =   10

THREAD_TYPE_KERNEL       =   00000000h
THREAD_TYPE_SYSTEM       =   00000001h
THREAD_TYPE_DRIVER       =   00000002h
THREAD_TYPE_APPLICATION  =   000000FFh

THREAD_PRIORITY_REALTIME=   223 ;223-255
THREAD_PRIORITY_HIGHEST =   191 ;191-222
THREAD_PRIORITY_HIGH    =   159 ;159-190
THREAD_PRIORITY_NORMAL  =   127 ;127-158
THREAD_PRIORITY_LOW     =   95  ;95-126
THREAD_PRIORITY_LOWEST  =   63  ;63-95
THREAD_PRIORITY_IDLE    =   31   ;Maintains system structures but does not require much
THREAD_PRIORITY_SERVICE =   0   ;Never scheduled, but can be invoked by other programs

CREATE_PROCESS_INHERITHANDLES   =   000000001h
CREATE_PROCESS_SUSPENDED        =   000000002h
CREATE_PROCESS_DEBUG            =   000000004h

KERNEL_THREAD           =   1

THREAD_ACTIVE       =   1
THREAD_SIGNATURE    =   "TMBL"                
PROCESS_SIGNATURE	=	"PMBL"

TF_CRITICAL             =   0x01   ;Avoid task switching
TF_PRIORITY             =   0x02
TF_WAITING              =   0x04   ;We are waiting for something 
TF_WAITINGFOREVENT      =   0x08   ;We are waiting for an event
TF_WAITINGFORRESOURCE   =   0x10   ;We are waiting for a resource to become free
TF_RUNNING              =   0x1000 ;A thread must be running for it to be allowed in ready queues
TF_CRITICALSECTION      =   0x2000   ;Avoid task switching

TF_WAITSTATE   = TF_WAITING | TF_WAITINGFOREVENT | TF_WAITINGFORRESOURCE

RST_TIMER = 1
RST_SHARED_RESOURCE=2
RST_DISPLAY_BUFFER=3
#

EXUCONTEXT STRUCT

    xAX     MWORD ?
    xCX     MWORD ?
    xDX     MWORD ?
    xBX     MWORD ?
    xSI     MWORD ?
    xDI     MWORD ?
    xSP     MWORD ?
    xBP     MWORD ?
    xCS     MWORD ?
    xDS     MWORD ?
    xSS     MWORD ?
    xES     MWORD ?
    xFS     MWORD ?
    xGS     MWORD ?
    xFlags  MWORD ?
    xIP     MWORD ?
    
IFDEF BITS64
    xR8     MWORD ?
    xR9     MWORD ?
    xR10    MWORD ?
    xR11    MWORD ?
    xR12    MWORD ?
    xR13    MWORD ?
    xR14    MWORD ?
    xR15    MWORD ?
ENDIF

    xCR0    MWORD ?
    xCR1    MWORD ?
    xCR2    MWORD ?
    xCR3    MWORD ?
    xCR4    MWORD ?
    xCR7    MWORD ?
    bNew    MWORD ?

	FPUState	LABEL MWORD
	
IFDEF X86FPU
	DB	108 DUP(?)
	echo "X86FPU"
ENDIF

IFDEF X86SSE
	DB 512 DUP(?)
	echo "X86SSE"
ENDIF

IFDEF X86SSE5
    DB 1024 DUP(?)
	echo "X86SSE5"
ENDIF

EXUCONTEXT  ENDS


VMMDATA STRUCT
    PTBase  MWORD ?
VMMDATA ENDS

DEBUGCONTEXT STRUCT

    dxAX     MWORD ?
    dxCX     MWORD ?
    dxDX     MWORD ?
    dxBX     MWORD ?
    dxSI     MWORD ?
    dxDI     MWORD ?
    dxSP     MWORD ?
    dxBP     MWORD ?
    dxCS     MWORD ?
    dxDS     MWORD ?
    dxSS     MWORD ?
    dxES     MWORD ?
    dxFS     MWORD ?
    dxGS     MWORD ?
    dxFlags  MWORD ?
    dxIP     MWORD ?
    dxCR0   MWORD ?
    dxCR1   MWORD ?
    dxCR2   MWORD ?
    dxCR3   MWORD ?
    dxCR4   MWORD ?

    dxXMM0  MWORD ?
    dxXMM1  MWORD ?
    dxXMM2  MWORD ?
    dxXMM3  MWORD ?
    dxXMM4  MWORD ?
    dxXMM5  MWORD ?
    dxXMM6  MWORD ?
    dxXMM7  MWORD ?
 
DEBUGCONTEXT ENDS
