/***************************************************************************************
* Copyright (C) 2018 Tinashe Mutandagayi                                               *
*                                                                                      *
* This file is part of the MT-Operating System source code. The author(s) of this file *
* is/are not liable for any damages, loss or loss of information, deaths, sicknesses   *
* or other bad things resulting from use of this file or software, either direct or    *
* indirect.                                                                            *
* Terms and conditions for use and distribution can be found in the license file named *
* LICENSE.TXT. If you distribute this file or continue using it,                       *
* it means you understand and agree with the terms and conditions in the license file. *
* binding this file.                                                                   *
*                                                                                      *
* Happy Coding :)                                                                      *
****************************************************************************************/


#include "kfenum.h"

	.globl _CreateThread
_CreateThread:
	lea 4(%esp),%edx
	movl $0,%eax
	int $0xff
	ret

 	.globl _CreateProcess
_CreateProcess:
	lea 4(%esp),%edx
	movl $1,%eax
	int $0xff
	ret

 	.globl __idle
__idle:
	lea 4(%esp),%edx
	movl $2,%eax
	int $0xff
	ret

 	.globl __active
__active:
	lea 4(%esp),%edx
	movl $3,%eax
	int $0xff
	ret

 	.globl __halt
__halt:
	lea 4(%esp),%edx
	movl $4,%eax
	int $0xff
	ret

 	.globl _RunThread
_RunThread:
	lea 4(%esp),%edx
	movl $5,%eax
	int $0xff
	ret

 	.globl _SuspendThread
_SuspendThread:
	lea 4(%esp),%edx
	movl $6,%eax
	int $0xff
	ret

 	.globl _GetCurrentProcess
_GetCurrentProcess:
	lea 4(%esp),%edx
	movl $7,%eax
	int $0xff
	ret

 	.globl _GetCurrentThread
_GetCurrentThread:
	lea 4(%esp),%edx
	movl $8,%eax
	int $0xff
	ret

 	.globl _CriticalProcessStart
_CriticalProcessStart:
	lea 4(%esp),%edx
	movl $9,%eax
	int $0xff
	ret

 	.globl _CriticalProcessEnd
_CriticalProcessEnd:
	lea 4(%esp),%edx
	movl $10,%eax
	int $0xff
	ret

 	.globl _SpinLock
_SpinLock:
	lea 4(%esp),%edx
	movl $11,%eax
	int $0xff
	ret

 	.globl _SpinUnlock
_SpinUnlock:
	lea 4(%esp),%edx
	movl $12,%eax
	int $0xff
	ret

 	.globl _SpinLockVariable
_SpinLockVariable:
	lea 4(%esp),%edx
	movl $13,%eax
	int $0xff
	ret

 	.globl _InitLock
_InitLock:
	lea 4(%esp),%edx
	movl $14,%eax
	int $0xff
	ret

 	.globl _Lock
_Lock:
	lea 4(%esp),%edx
	movl $15,%eax
	int $0xff
	ret

 	.globl _LockX
_LockX:
	lea 4(%esp),%edx
	movl $16,%eax
	int $0xff
	ret

 	.globl _Unlock
_Unlock:
	lea 4(%esp),%edx
	movl $17,%eax
	int $0xff
	ret

 	.globl _AcquireLock
_AcquireLock:
	lea 4(%esp),%edx
	movl $18,%eax
	int $0xff
	ret

 	.globl _CreateLock
_CreateLock:
	lea 4(%esp),%edx
	movl $19,%eax
	int $0xff
	ret

 	.globl _DestroyLock
_DestroyLock:
	lea 4(%esp),%edx
	movl $20,%eax
	int $0xff
	ret

 	.globl _IsLocked
_IsLocked:
	lea 4(%esp),%edx
	movl $21,%eax
	int $0xff
	ret

 	.globl _ProcessIsRunning
_ProcessIsRunning:
	lea 4(%esp),%edx
	movl $22,%eax
	int $0xff
	ret

 	.globl _ThreadIsRunning
_ThreadIsRunning:
	lea 4(%esp),%edx
	movl $23,%eax
	int $0xff
	ret

 	.globl _FavourThread
_FavourThread:
	lea 4(%esp),%edx
	movl $24,%eax
	int $0xff
	ret

 	.globl _RetireThread
_RetireThread:
	lea 4(%esp),%edx
	movl $25,%eax
	int $0xff
	ret

 	.globl _IsCurrentThreadKernel
_IsCurrentThreadKernel:
	lea 4(%esp),%edx
	movl $26,%eax
	int $0xff
	ret

 	.globl _IsCurrentProcessKernel
_IsCurrentProcessKernel:
	lea 4(%esp),%edx
	movl $27,%eax
	int $0xff
	ret

 	.globl _IsThreadCritical
_IsThreadCritical:
	lea 4(%esp),%edx
	movl $28,%eax
	int $0xff
	ret

 	.globl _DestroyThread
_DestroyThread:
	lea 4(%esp),%edx
	movl $29,%eax
	int $0xff
	ret

 	.globl _GetThreadName
_GetThreadName:
	lea 4(%esp),%edx
	movl $30,%eax
	int $0xff
	ret

 	.globl _GetProcessName
_GetProcessName:
	lea 4(%esp),%edx
	movl $31,%eax
	int $0xff
	ret

 	.globl _GetCurrentProcessName
_GetCurrentProcessName:
	lea 4(%esp),%edx
	movl $32,%eax
	int $0xff
	ret

 	.globl _GetCurrentThreadName
_GetCurrentThreadName:
	lea 4(%esp),%edx
	movl $33,%eax
	int $0xff
	ret

 	.globl _CriticalSectionStart
_CriticalSectionStart:
	lea 4(%esp),%edx
	movl $34,%eax
	int $0xff
	ret

 	.globl _CriticalSectionEnd
_CriticalSectionEnd:
	lea 4(%esp),%edx
	movl $35,%eax
	int $0xff
	ret

 	.globl _KernelCriticalSectionStart
_KernelCriticalSectionStart:
	lea 4(%esp),%edx
	movl $36,%eax
	int $0xff
	ret

 	.globl _KernelCriticalSectionEnd
_KernelCriticalSectionEnd:
	lea 4(%esp),%edx
	movl $37,%eax
	int $0xff
	ret

 	.globl _IsKernelCriticalSection
_IsKernelCriticalSection:
	lea 4(%esp),%edx
	movl $38,%eax
	int $0xff
	ret

 	.globl _IsKernelProcess
_IsKernelProcess:
	lea 4(%esp),%edx
	movl $39,%eax
	int $0xff
	ret

 	.globl _IsKernelThread
_IsKernelThread:
	lea 4(%esp),%edx
	movl $40,%eax
	int $0xff
	ret

 	.globl _IsOSReady
_IsOSReady:
	lea 4(%esp),%edx
	movl $41,%eax
	int $0xff
	ret

 	.globl _SetThreadLog
_SetThreadLog:
	lea 4(%esp),%edx
	movl $42,%eax
	int $0xff
	ret

 	.globl _SetTimeOut
_SetTimeOut:
	lea 4(%esp),%edx
	movl $43,%eax
	int $0xff
	ret

 	.globl _SetTimerInterval
_SetTimerInterval:
	lea 4(%esp),%edx
	movl $44,%eax
	int $0xff
	ret

 	.globl _CancelTimer
_CancelTimer:
	lea 4(%esp),%edx
	movl $45,%eax
	int $0xff
	ret

 	.globl _SetCurrentThreadName
_SetCurrentThreadName:
	lea 4(%esp),%edx
	movl $46,%eax
	int $0xff
	ret

 	.globl _SetThreadName
_SetThreadName:
	lea 4(%esp),%edx
	movl $47,%eax
	int $0xff
	ret

 	.globl _VerifyProcess
_VerifyProcess:
	lea 4(%esp),%edx
	movl $48,%eax
	int $0xff
	ret

 	.globl _VerifyThread
_VerifyThread:
	lea 4(%esp),%edx
	movl $49,%eax
	int $0xff
	ret

 	.globl _GetProcessPrivateData
_GetProcessPrivateData:
	lea 4(%esp),%edx
	movl $50,%eax
	int $0xff
	ret

 	.globl _SetProcessPrivateData
_SetProcessPrivateData:
	lea 4(%esp),%edx
	movl $51,%eax
	int $0xff
	ret

 	.globl _GetProcessPrivateItem
_GetProcessPrivateItem:
	lea 4(%esp),%edx
	movl $52,%eax
	int $0xff
	ret

 	.globl _SetProcessPrivateItem
_SetProcessPrivateItem:
	lea 4(%esp),%edx
	movl $53,%eax
	int $0xff
	ret

 	.globl _InitializeProcessPrivateData
_InitializeProcessPrivateData:
	lea 4(%esp),%edx
	movl $54,%eax
	int $0xff
	ret

 	.globl _SetThreadPrivateData
_SetThreadPrivateData:
	lea 4(%esp),%edx
	movl $55,%eax
	int $0xff
	ret

 	.globl _GetThreadPrivateData
_GetThreadPrivateData:
	lea 4(%esp),%edx
	movl $56,%eax
	int $0xff
	ret

 	.globl _GetThreadPrivateItem
_GetThreadPrivateItem:
	lea 4(%esp),%edx
	movl $57,%eax
	int $0xff
	ret

 	.globl _SetThreadPrivateItem
_SetThreadPrivateItem:
	lea 4(%esp),%edx
	movl $58,%eax
	int $0xff
	ret

 	.globl _InitializeThreadPrivateData
_InitializeThreadPrivateData:
	lea 4(%esp),%edx
	movl $59,%eax
	int $0xff
	ret

 	.globl _VMMAllocateMemory
_VMMAllocateMemory:
	lea 4(%esp),%edx
	movl $60,%eax
	int $0xff
	ret

 	.globl _VMMReallocateMemory
_VMMReallocateMemory:
	lea 4(%esp),%edx
	movl $61,%eax
	int $0xff
	ret

 	.globl _VMMFreeMemory
_VMMFreeMemory:
	lea 4(%esp),%edx
	movl $62,%eax
	int $0xff
	ret

 	.globl _VMMReserve
_VMMReserve:
	lea 4(%esp),%edx
	movl $63,%eax
	int $0xff
	ret

 	.globl _VMMCommit
_VMMCommit:
	lea 4(%esp),%edx
	movl $64,%eax
	int $0xff
	ret

 	.globl _VMMGetMemorySize
_VMMGetMemorySize:
	lea 4(%esp),%edx
	movl $65,%eax
	int $0xff
	ret

 	.globl _VMMShareMemory
_VMMShareMemory:
	lea 4(%esp),%edx
	movl $66,%eax
	int $0xff
	ret

 	.globl _VMMProtect
_VMMProtect:
	lea 4(%esp),%edx
	movl $67,%eax
	int $0xff
	ret

 	.globl _WaitForEvent
_WaitForEvent:
	lea 4(%esp),%edx
	movl $68,%eax
	int $0xff
	ret

 	.globl _DoEvents
_DoEvents:
	lea 4(%esp),%edx
	movl $69,%eax
	int $0xff
	ret

 	.globl _WaitForEvents
_WaitForEvents:
	lea 4(%esp),%edx
	movl $70,%eax
	int $0xff
	ret

 	.globl _ProcessEvents
_ProcessEvents:
	lea 4(%esp),%edx
	movl $71,%eax
	int $0xff
	ret

 	.globl _EventsLoop
_EventsLoop:
	lea 4(%esp),%edx
	movl $72,%eax
	int $0xff
	ret

 	.globl _GetNumEvents
_GetNumEvents:
	lea 4(%esp),%edx
	movl $73,%eax
	int $0xff
	ret

 	.globl _AddEventToQueue
_AddEventToQueue:
	lea 4(%esp),%edx
	movl $74,%eax
	int $0xff
	ret

 	.globl _RegisterEventsClass
_RegisterEventsClass:
	lea 4(%esp),%edx
	movl $75,%eax
	int $0xff
	ret

 	.globl _SendProcessEvent
_SendProcessEvent:
	lea 4(%esp),%edx
	movl $76,%eax
	int $0xff
	ret

 	.globl _GetNextEvent
_GetNextEvent:
	lea 4(%esp),%edx
	movl $77,%eax
	int $0xff
	ret

 	.globl _EventsInQueue
_EventsInQueue:
	lea 4(%esp),%edx
	movl $78,%eax
	int $0xff
	ret

 	.globl _GetMaxEvents
_GetMaxEvents:
	lea 4(%esp),%edx
	movl $79,%eax
	int $0xff
	ret

 	.globl _Delay
_Delay:
	lea 4(%esp),%edx
	movl $80,%eax
	int $0xff
	ret

 	.globl _DelayUS
_DelayUS:
	lea 4(%esp),%edx
	movl $81,%eax
	int $0xff
	ret

 	.globl _GetTicksUS
_GetTicksUS:
	lea 4(%esp),%edx
	movl $82,%eax
	int $0xff
	ret

 	.globl _GetTicksMS
_GetTicksMS:
	lea 4(%esp),%edx
	movl $83,%eax
	int $0xff
	ret

 	.globl _SetInterruptVector
_SetInterruptVector:
	lea 4(%esp),%edx
	movl $84,%eax
	int $0xff
	ret

 	.globl _DisableInterrupts
_DisableInterrupts:
	lea 4(%esp),%edx
	movl $85,%eax
	int $0xff
	ret

 	.globl _EnableInterrupts
_EnableInterrupts:
	lea 4(%esp),%edx
	movl $86,%eax
	int $0xff
	ret

 	.globl __Scheduler
__Scheduler:
	lea 4(%esp),%edx
	movl $87,%eax
	int $0xff
	ret

 	.globl _OSReboot
_OSReboot:
	lea 4(%esp),%edx
	movl $88,%eax
	int $0xff
	ret

 	.globl _OSShutdown
_OSShutdown:
	lea 4(%esp),%edx
	movl $89,%eax
	int $0xff
	ret

 	.globl _GetFeatures
_GetFeatures:
	lea 4(%esp),%edx
	movl $90,%eax
	int $0xff
	ret

 	.globl _GetCurrentEXU
_GetCurrentEXU:
	lea 4(%esp),%edx
	movl $91,%eax
	int $0xff
	ret

 	.globl _GetSystemInformation
_GetSystemInformation:
	lea 4(%esp),%edx
	movl $92,%eax
	int $0xff
	ret

 	.globl _UiShowMessage
_UiShowMessage:
	lea 4(%esp),%edx
	movl $93,%eax
	int $0xff
	ret

 	.globl _SetUiProcess
_SetUiProcess:
	lea 4(%esp),%edx
	movl $94,%eax
	int $0xff
	ret

 	.globl _GetUiProcess
_GetUiProcess:
	lea 4(%esp),%edx
	movl $95,%eax
	int $0xff
	ret

 	.globl _GiSetPixel
_GiSetPixel:
	lea 4(%esp),%edx
	movl $96,%eax
	int $0xff
	ret

 	.globl _GiGetPixel
_GiGetPixel:
	lea 4(%esp),%edx
	movl $97,%eax
	int $0xff
	ret

 	.globl _GiDrawBox
_GiDrawBox:
	lea 4(%esp),%edx
	movl $98,%eax
	int $0xff
	ret

 	.globl _GiSetVideoParams
_GiSetVideoParams:
	lea 4(%esp),%edx
	movl $99,%eax
	int $0xff
	ret

 	.globl _GiGetVideoBPP
_GiGetVideoBPP:
	lea 4(%esp),%edx
	movl $100,%eax
	int $0xff
	ret

 	.globl _GiGetVideoHeight
_GiGetVideoHeight:
	lea 4(%esp),%edx
	movl $101,%eax
	int $0xff
	ret

 	.globl _GiGetVideoWidth
_GiGetVideoWidth:
	lea 4(%esp),%edx
	movl $102,%eax
	int $0xff
	ret

 	.globl _UiPrintStr
_UiPrintStr:
	lea 4(%esp),%edx
	movl $103,%eax
	int $0xff
	ret

 	.globl _UiPrintChar
_UiPrintChar:
	lea 4(%esp),%edx
	movl $104,%eax
	int $0xff
	ret

 	.globl _UiPrintWStr
_UiPrintWStr:
	lea 4(%esp),%edx
	movl $105,%eax
	int $0xff
	ret

 	.globl _UiPrintStrX
_UiPrintStrX:
	lea 4(%esp),%edx
	movl $106,%eax
	int $0xff
	ret

 	.globl _UiPrintWStrX
_UiPrintWStrX:
	lea 4(%esp),%edx
	movl $107,%eax
	int $0xff
	ret

 	.globl _UiClearScreen
_UiClearScreen:
	lea 4(%esp),%edx
	movl $108,%eax
	int $0xff
	ret

 	.globl _FsFindFileInit
_FsFindFileInit:
	lea 4(%esp),%edx
	movl $109,%eax
	int $0xff
	ret

 	.globl _FsFindFileDone
_FsFindFileDone:
	lea 4(%esp),%edx
	movl $110,%eax
	int $0xff
	ret

 	.globl _FsFindFile
_FsFindFile:
	lea 4(%esp),%edx
	movl $111,%eax
	int $0xff
	ret

 	.globl _FsGetFileInfo
_FsGetFileInfo:
	lea 4(%esp),%edx
	movl $112,%eax
	int $0xff
	ret

 	.globl _FsGetOpenFileInfo
_FsGetOpenFileInfo:
	lea 4(%esp),%edx
	movl $113,%eax
	int $0xff
	ret

 	.globl _FsVolumeExists
_FsVolumeExists:
	lea 4(%esp),%edx
	movl $114,%eax
	int $0xff
	ret

 	.globl _FsCharToUnicode
_FsCharToUnicode:
	lea 4(%esp),%edx
	movl $115,%eax
	int $0xff
	ret

 	.globl _FsUnicodeToChar
_FsUnicodeToChar:
	lea 4(%esp),%edx
	movl $116,%eax
	int $0xff
	ret

 	.globl _FsRead
_FsRead:
	lea 4(%esp),%edx
	movl $117,%eax
	int $0xff
	ret

 	.globl _FsWrite
_FsWrite:
	lea 4(%esp),%edx
	movl $118,%eax
	int $0xff
	ret

 	.globl _FsSetFilePosition
_FsSetFilePosition:
	lea 4(%esp),%edx
	movl $119,%eax
	int $0xff
	ret

 	.globl _FsGetFilePosition
_FsGetFilePosition:
	lea 4(%esp),%edx
	movl $120,%eax
	int $0xff
	ret

 	.globl _FsGetFileSize
_FsGetFileSize:
	lea 4(%esp),%edx
	movl $121,%eax
	int $0xff
	ret

 	.globl _FsDeleteFile
_FsDeleteFile:
	lea 4(%esp),%edx
	movl $122,%eax
	int $0xff
	ret

 	.globl _FsVolGetBytesPerUnit
_FsVolGetBytesPerUnit:
	lea 4(%esp),%edx
	movl $123,%eax
	int $0xff
	ret

 	.globl _FsIsUnicode
_FsIsUnicode:
	lea 4(%esp),%edx
	movl $124,%eax
	int $0xff
	ret

 	.globl _FsGetLastError
_FsGetLastError:
	lea 4(%esp),%edx
	movl $125,%eax
	int $0xff
	ret

 	.globl _FsSetLastError
_FsSetLastError:
	lea 4(%esp),%edx
	movl $126,%eax
	int $0xff
	ret

 	.globl _FsParsePath
_FsParsePath:
	lea 4(%esp),%edx
	movl $127,%eax
	int $0xff
	ret

 	.globl _FsOpenFile
_FsOpenFile:
	lea 4(%esp),%edx
	movl $128,%eax
	int $0xff
	ret

 	.globl _FsReadFile
_FsReadFile:
	lea 4(%esp),%edx
	movl $129,%eax
	int $0xff
	ret

 	.globl _FsWriteFile
_FsWriteFile:
	lea 4(%esp),%edx
	movl $130,%eax
	int $0xff
	ret

 	.globl _FsCloseFile
_FsCloseFile:
	lea 4(%esp),%edx
	movl $131,%eax
	int $0xff
	ret

 	.globl _DlFind
_DlFind:
	lea 4(%esp),%edx
	movl $132,%eax
	int $0xff
	ret

 	.globl _DlOpen
_DlOpen:
	lea 4(%esp),%edx
	movl $133,%eax
	int $0xff
	ret

 	.globl _DlSym
_DlSym:
	lea 4(%esp),%edx
	movl $134,%eax
	int $0xff
	ret

 	.globl _DlClose
_DlClose:
	lea 4(%esp),%edx
	movl $135,%eax
	int $0xff
	ret

 