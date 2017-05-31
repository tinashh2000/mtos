PUBLIC _InitContext86@20

_InitContext86@20:
InitContext86   PROC    dContext:MWORD,ePoint:MWORD,dStackTop:MWORD,dVMMData:MWORD,dPrivilegeLevel:MWORD
    PUSH    EBX
    MOV EBX,dContext

    MOV BYTE [EBX].bNew,1   ;Indicate that this is the first time we are running

    MOV MWORD [EBX].xBX,0

JMP	icKernel

	CMP	dPrivilegeLevel,3
	JA	icUser
	
	CMP	dPrivilegeLevel,1
	JB	icKernel	;if zero
	JA  icService

	
 	MOV EAX,DRIVERCODE32 OR 1
    MOV MWORD [EBX].xCS,EAX
	
	MOV EAX,DRIVERDATA32 OR 1
	JMP	icLoadDataSegs
 icService:
	MOV	EAX,SERVICECODE32 OR 2
    MOV MWORD [EBX].xCS,EAX
	
	MOV EAX,SERVICEDATA32 OR 3
	JMP	icLoadDataSegs
 icUser:
 	MOV EAX,USERCODE32 OR 3
    MOV MWORD [EBX].xCS,EAX
	
	MOV EAX,USERDATA32 OR 3
	JMP	icLoadDataSegs
icKernel:
	MOV EAX,LINEARCODE32
    MOV MWORD [EBX].xCS,EAX

    MOV EAX,DS
	
 icLoadDataSegs:
 
    MOV MWORD [EBX].xDS,EAX
    MOV MWORD [EBX].xES,EAX
    MOV MWORD [EBX].xFS,EAX
    MOV MWORD [EBX].xGS,EAX
    MOV MWORD [EBX].xSS,EAX

    MOV MWORD [EBX].xFlags,200h    ;Interrupts enabled

    MOV EAX,dStackTop
    MOV MWORD [EBX].xSP,EAX

    MOV EAX,ePoint
    MOV MWORD [EBX].xIP,EAX

    MOV EAX,dVMMData
    MOV MWORD [EBX].xCR3,EAX

    POP EBX
    RET
InitContext86   ENDP

SwitchContext:      ;EAX = ptr to old oldthread,newthread

    CLI
	PUSH EBX
	PUSH DS
	MOV EBX, LINEARDATA32
	MOV DS, EBX
	
    CMP MWORD [EAX],0
    JZ  scNewThreadX


;    PUSH    EBX ;Save current EBX
    MOV EBX,[EAX]        ;Point to old thread
    CMP EBX,[EAX][4]
    JZ  scSameThread
    ADD EBX,(SIZE MWORD)    ;Just after signature is the EXUContext

    POP MWORD [EBX].xDS
    POP MWORD [EBX].xBX 

    MOV [EBX].xCS,CS
;DS already saved
	MOV [EBX].xES,ES
    MOV [EBX].xSS,SS
    MOV [EBX].xFS,FS
    MOV [EBX].xGS,GS

    MOV [EBX].xCX,ECX
    MOV [EBX].xDX,EDX

    MOV ECX,[ESP][4]   ;The stack frame is as follows: RET,EAX
    MOV [EBX].xAX,ECX

    MOV [EBX].xSI,ESI
    MOV [EBX].xDI,EDI
    MOV [EBX].xBP,EBP

    LEA ECX,[ESP][20]   ;We will point ESP to before the INT
    MOV [EBX].xSP,ECX   ;SFRAME: RET,EAX,12 Byte EIP,CS,Flags

    MOV ECX,[ESP][8]
    MOV [EBX].xIP,ECX

    MOV ECX,[ESP][12]
    MOV [EBX].xCS,ECX

    MOV ECX,[ESP][16]
    MOV [EBX].xFlags,ECX

    MOV ECX,CR3
    MOV [EBX].xCR3,ECX

    JMP scNewThread
scNewThreadX:
	ADD	ESP, (2 * (SIZE MWORD))
scNewThread:

    CMP MWORD [EAX][4],0
    JZ  scExit

    MOV EBX,[EAX][4]    ;Point to new thread
    ADD EBX,(SIZE MWORD)    ;Skip the signature. We are at the context

    MOV EAX,[ESP]   ;This return address, so that we may acknowledge the interrupt if need be

    MOV SS,[EBX].xSS
    MOV ESP,[EBX].xSP

    PUSH    MWORD [EBX].xFlags
    PUSH    MWORD [EBX].xCS
    PUSH    MWORD [EBX].xIP ;IRET stack frame

    PUSH    MWORD [EBX].xAX ;EAX saved in previous proc
    PUSH    EAX             ;The return addr. we havent ack'd the intr
    PUSH    MWORD [EBX].xBX ;We will use it soon

    MOV ECX,[EBX].xCX
    MOV EDX,[EBX].xDX
    MOV ESI,[EBX].xSI
    MOV EDI,[EBX].xDI
    MOV EBP,[EBX].xBP
	
	MOV	EAX,CR0		;Task switched
	OR	AL,8
	MOV CR0,EAX

    MOV EAX,CR3
    CMP EAX,[EBX].xCR3  ;Avoid rewriting the same CR3
    JZ  scCR3OK

    MOV EAX,[EBX].xCR3
    MOV CR3,EAX

 scCR3OK:

    MOV FS,[EBX].xFS
    MOV GS,[EBX].xGS
    MOV ES,[EBX].xES
    MOV DS,[EBX].xDS
	
    POP EBX
    RET
 scExit:
    RET

 scSameThread:
    POP EBX
    RET
