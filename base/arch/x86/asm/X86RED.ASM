GetCurrentEXU:
    JMP _GetCurrentEXU@0

GetCurrentThread:
    JMP _GetCurrentThread@0

GetThreadName	PROC	p1:MWORD, p2:MWORD
	CALL	_GetThreadName@8, p1, p2
	ADD ESP, (2 * (SIZE MWORD))
	RET
GetThreadName	ENDP

SchedulerCX:
    JMP _SchedulerCX@0

SchedulerX	PROC	p1:MWORD
    CALL _SchedulerX@4, p1
	ADD ESP, (1 * (SIZE MWORD))
	RET
SchedulerX	ENDP

TimerHandler:
    JMP _TimerHandler@0

PrintStr	PROC	p1:MWORD
    CALL _PrintStr@4, p1
	ADD ESP, (1 * (SIZE MWORD))
	RET
PrintStr	ENDP

PrintChar	PROC	chrx:MWORD
    CALL _PrintChar@4, chrx
	ADD ESP, (1 * (SIZE MWORD))
	RET
PrintChar	ENDP

PrintHexD	PROC	val:MWORD
    CALL _PrintHexD@4, val
	ADD ESP, (1 * (SIZE MWORD))
	RET
PrintHexD	ENDP

Hex32ToStr	PROC	p1:MWORD, p2:MWORD, p3:MWORD, p4:MWORD
    CALL _Hex32ToStr@16, p1, p2, p3, p4
	ADD ESP, (4 * (SIZE MWORD))
	RET
Hex32ToStr	ENDP

DebugProcess	PROC	p1:MWORD, p2:MWORD
	CALL	_DebugProcess@8, p1, p2
	ADD ESP, (2 * (SIZE MWORD))
	RET
DebugProcess	ENDP

printf:
    JMP _printf

memset:
    JMP _memset

KernelEntry	PROC	p1:MWORD, p2:MWORD, p3:MWORD, p4:MWORD, p5:MWORD
    CALL _KernelEntry@20, p1 ,p2, p3, p4, p5
	ADD ESP, (5 * (SIZE MWORD))
	RET
KernelEntry	ENDP

GetDebugThreadX:
	JMP _GetDebugThreadX@0

SetDebugThread	PROC	p1:MWORD
	CALL _SetDebugThreadX@4, p1
	ADD ESP, (1 * (SIZE MWORD))
	RET
SetDebugThread	ENDP