GetCurrentEXU:
    JMP _GetCurrentEXU@0

GetCurrentThread:
    JMP _GetCurrentThread@0

GetThreadName:
	CALL	_GetThreadName@8
	ADD ESP, (2 * (SIZE MWORD))
	RET

SchedulerCX:
    JMP _SchedulerCX@0

SchedulerX:
    CALL _SchedulerX@4
	ADD ESP, (1 * (SIZE MWORD))
	RET


TimerHandler:
    JMP _TimerHandler@0

PrintStr:
    CALL _PrintStr@4
	ADD ESP, (1 * (SIZE MWORD))
	RET


PrintChar:
    CALL _PrintChar@4
	ADD ESP, (1 * (SIZE MWORD))
	RET

PrintHexD:
    CALL _PrintHexD@4
	ADD ESP, (1 * (SIZE MWORD))
	RET

;HexToStr32:
;    JMP _HexToStr32@8

Hex32ToStr:
    CALL _Hex32ToStr@16
	ADD ESP, (4 * (SIZE MWORD))
	RET


DebugProcess:
	CALL	_DebugProcess@8
	ADD ESP, (2 * (SIZE MWORD))
	RET

printf:
    JMP _printf

memset:
    JMP _memset

KernelEntry:
    CALL _KernelEntry@20
	ADD ESP, (5 * (SIZE MWORD))
	RET

GetDebugThreadX:
	JMP _GetDebugThreadX@0

SetDebugThread:
	CALL _SetDebugThreadX@4
	ADD ESP, (8 * (SIZE MWORD))
	RET
