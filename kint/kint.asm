#include "kfenum.inc"

CreateThread:
	mov edx,esp
	mov eax, KF_CREATE_THREAD
	 int 0x60

 CreateProcess:
	mov edx,esp
	mov eax, KF_CREATE_PROCESS
	 int 0x60

 _idle:
	mov edx,esp
	mov eax, KF__IDLE
	 int 0x60

 _active:
	mov edx,esp
	mov eax, KF__ACTIVE
	 int 0x60

 _halt:
	mov edx,esp
	mov eax, KF__HALT
	 int 0x60

 RunThread:
	mov edx,esp
	mov eax, KF_RUNTHREAD
	 int 0x60

 SuspendThread:
	mov edx,esp
	mov eax, KF_SUSPENDTHREAD
	 int 0x60

 GetCurrentProcess:
	mov edx,esp
	mov eax, KF_GETCURRENTPROCESS
	 int 0x60

 GetCurrentThread:
	mov edx,esp
	mov eax, KF_GETCURRENTTHREAD
	 int 0x60

 CriticalProcessStart:
	mov edx,esp
	mov eax, KF_CRITICALPROCESSSTART
	 int 0x60

 CriticalProcessEnd:
	mov edx,esp
	mov eax, KF_CRITICALPROCESSEND
	 int 0x60

 SpinLock:
	mov edx,esp
	mov eax, KF_SPINLOCK
	 int 0x60

 SpinUnlock:
	mov edx,esp
	mov eax, KF_SPINUNLOCK
	 int 0x60

 SpinLockVariable:
	mov edx,esp
	mov eax, KF_KESPINLOCKVARIABLE
	 int 0x60

 InitLock:
	mov edx,esp
	mov eax, KF_INITLOCK
	 int 0x60

 Lock:
	mov edx,esp
	mov eax, KF_LOCK
	 int 0x60

 LockX:
	mov edx,esp
	mov eax, KF_LOCKX
	 int 0x60

 Unlock:
	mov edx,esp
	mov eax, KF_UNLOCK
	 int 0x60

 AcquireLock:
	mov edx,esp
	mov eax, KF_ACQUIRELOCK
	 int 0x60

 CreateLock:
	mov edx,esp
	mov eax, KF_CREATELOCK
	 int 0x60

 DestroyLock:
	mov edx,esp
	mov eax, KF_DESTROYLOCK
	 int 0x60

 IsLocked:
	mov edx,esp
	mov eax, KF_ISLOCKED
	 int 0x60

 ProcessIsRunning:
	mov edx,esp
	mov eax, KF_PROCESSISRUNNING
	 int 0x60

 ThreadIsRunning:
	mov edx,esp
	mov eax, KF_THREADISRUNNING
	 int 0x60

 FavourThread:
	mov edx,esp
	mov eax, KF_FAVOURTHREAD
	 int 0x60

 RetireThread:
	mov edx,esp
	mov eax, KF_RETIRETHREAD
	 int 0x60

 IsCurrentThreadKernel:
	mov edx,esp
	mov eax, KF_ISCURRENTTHREADKERNEL
	 int 0x60

 IsCurrentProcessKernel:
	mov edx,esp
	mov eax, KF_ISCURRENTPROCESSKERNEL
	 int 0x60

 IsThreadCritical:
	mov edx,esp
	mov eax, KF_ISTHREADCRITICAL
	 int 0x60

 DestroyThread:
	mov edx,esp
	mov eax, KF_DESTROYTHREAD
	 int 0x60

 GetThreadName:
	mov edx,esp
	mov eax, KF_GETTHREADNAME
	 int 0x60

 GetProcessName:
	mov edx,esp
	mov eax, KF_GETPROCESSNAME
	 int 0x60

 GetCurrentProcessName:
	mov edx,esp
	mov eax, KF_GETCURRENTPROCESSNAME
	 int 0x60

 GetCurrentThreadName:
	mov edx,esp
	mov eax, KF_GETCURRENTTHREADNAME
	 int 0x60

 CriticalSectionStart:
	mov edx,esp
	mov eax, KF_CRITICALSECTIONSTART
	 int 0x60

 CriticalSectionEnd:
	mov edx,esp
	mov eax, KF_CRITICALSECTIONEND
	 int 0x60

 KernelCriticalSectionStart:
	mov edx,esp
	mov eax, KF_KERNELCRITICALSECTIONSTART
	 int 0x60

 KernelCriticalSectionEnd:
	mov edx,esp
	mov eax, KF_KERNELCRITICALSECTIONEND
	 int 0x60

 IsKernelCriticalSection:
	mov edx,esp
	mov eax, KF_ISKERNELCRITICALSECTION
	 int 0x60

 IsKernelProcess:
	mov edx,esp
	mov eax, KF_ISKERNELPROCESS
	 int 0x60

 IsKernelThread:
	mov edx,esp
	mov eax, KF_ISKERNELTHREAD
	 int 0x60

 IsOSReady:
	mov edx,esp
	mov eax, KF_ISOSREADY
	 int 0x60

 SetThreadLog:
	mov edx,esp
	mov eax, KF_SETTHREADLOG
	 int 0x60

 SetTimeOut:
	mov edx,esp
	mov eax, KF_SETTIMEOUT
	 int 0x60

 SetTimerInterval:
	mov edx,esp
	mov eax, KF_SETTIMERINTERVAL
	 int 0x60

 CancelTimer:
	mov edx,esp
	mov eax, KF_CANCELTIMER
	 int 0x60

 SetCurrentThreadName:
	mov edx,esp
	mov eax, KF_SETCURRENTTHREADNAME
	 int 0x60

 SetThreadName:
	mov edx,esp
	mov eax, KF_SETTHREADNAME
	 int 0x60

 GetProcessPrivateData:
	mov edx,esp
	mov eax, KF_GETPROCESSPRIVATEDATA
	 int 0x60

 SetProcessPrivateData:
	mov edx,esp
	mov eax, KF_SETPROCESSPRIVATEDATA
	 int 0x60

 GetProcessPrivateItem:
	mov edx,esp
	mov eax, KF_GETPROCESSPRIVATEITEM
	 int 0x60

 SetProcessPrivateItem:
	mov edx,esp
	mov eax, KF_SETPROCESSPRIVATEITEM
	 int 0x60

 InitializeProcessPrivateData:
	mov edx,esp
	mov eax, KF_INITIALIZEPROCESSPRIVATEDATA
	 int 0x60

 SetThreadPrivateData:
	mov edx,esp
	mov eax, KF_SETTHREADPRIVATEDATA
	 int 0x60

 GetThreadPrivateData:
	mov edx,esp
	mov eax, KF_GETTHREADPRIVATEDATA
	 int 0x60

 GetThreadPrivateItem:
	mov edx,esp
	mov eax, KF_GETTHREADPRIVATEITEM
	 int 0x60

 SetThreadPrivateItem:
	mov edx,esp
	mov eax, KF_SETTHREADPRIVATEITEM
	 int 0x60

 InitializeThreadPrivateData:
	mov edx,esp
	mov eax, KF_INITIALIZETHREADPRIVATEDATA
	 int 0x60

 VMMAllocateMemory:
	mov edx,esp
	mov eax, KF_VMMALLOCATEMEMORY
	 int 0x60

 VMMReallocateMemory:
	mov edx,esp
	mov eax, KF_VMMREALLOCATEMEMORY
	 int 0x60

 VMMFreeMemory:
	mov edx,esp
	mov eax, KF_VMMFREEMEMORY
	 int 0x60

 VMMReserve:
	mov edx,esp
	mov eax, KF_VMMRESERVE
	 int 0x60

 VMMGetMemorySize:
	mov edx,esp
	mov eax, KF_VMMGETMEMORYSIZE
	 int 0x60

 VMMShareMemory:
	mov edx,esp
	mov eax, KF_VMMSHAREMEMORY
	 int 0x60

 WaitForEvent:
	mov edx,esp
	mov eax, KF_WAITFOREVENT
	 int 0x60

 DoEvents:
	mov edx,esp
	mov eax, KF_DOEVENTS
	 int 0x60

 WaitForEvents:
	mov edx,esp
	mov eax, KF_WAITFOREVENTS
	 int 0x60

 ProcessEvents:
	mov edx,esp
	mov eax, KF_PROCESSEVENTS
	 int 0x60

 EventsLoop:
	mov edx,esp
	mov eax, KF_EVENTSLOOP
	 int 0x60

 GetNumEvents:
	mov edx,esp
	mov eax, KF_GETNUMEVENTS
	 int 0x60

 AddEventToQueue:
	mov edx,esp
	mov eax, KF_ADDEVENTTOQUEUE
	 int 0x60

 RegisterEventsClass:
	mov edx,esp
	mov eax, KF_REGISTEREVENTSCLASS
	 int 0x60

 SendProcessEvent:
	mov edx,esp
	mov eax, KF_SENDPROCESSEVENT
	 int 0x60

 GetNextEvent:
	mov edx,esp
	mov eax, KF_GETNEXTEVENT
	 int 0x60

 EventsInQueue:
	mov edx,esp
	mov eax, KF_EVENTSINQUEUE
	 int 0x60

 GetMaxEvents:
	mov edx,esp
	mov eax, KF_GETMAXEVENTS
	 int 0x60

 Delay:
	mov edx,esp
	mov eax, KF_DELAY
	 int 0x60

 DelayUS:
	mov edx,esp
	mov eax, KF_DELAYUS
	 int 0x60

 GetTicksUS:
	mov edx,esp
	mov eax, KF_GETTICKSUS
	 int 0x60

 GetTicksMS:
	mov edx,esp
	mov eax, KF_GETTICKSMS
	 int 0x60

 SetInterruptVector:
	mov edx,esp
	mov eax, KF_SETINTERRUPTVECTOR
	 int 0x60

 DisableInterrupts:
	mov edx,esp
	mov eax, KF_DISABLEINTERRUPTS
	 int 0x60

 EnableInterrupts:
	mov edx,esp
	mov eax, KF_ENABLEINTERRUPTS
	 int 0x60

 _Scheduler:
	mov edx,esp
	mov eax, KF__SCHEDULER
	 int 0x60

 OSReboot:
	mov edx,esp
	mov eax, KF_OSREBOOT
	 int 0x60

 OSShutdown:
	mov edx,esp
	mov eax, KF_OSSHUTDOWN
	 int 0x60

 GetFeatures:
	mov edx,esp
	mov eax, KF_GETFEATURES
	 int 0x60

 GetCurrentEXU:
	mov edx,esp
	mov eax, KF_GETCURRENTEXU
	 int 0x60

 GetSystemInformation:
	mov edx,esp
	mov eax, KF_GETSYSTEMINFORMATION
	 int 0x60

 UiShowMessage:
	mov edx,esp
	mov eax, KF_UISHOWMESSAGE
	 int 0x60

 SetUiProcess:
	mov edx,esp
	mov eax, KF_SETUIPROCESS
	 int 0x60

 GetUiProcess:
	mov edx,esp
	mov eax, KF_GETUIPROCESS
	 int 0x60

 GiSetPixel:
	mov edx,esp
	mov eax, KF_GISETPIXEL
	 int 0x60

 GiGetPixel:
	mov edx,esp
	mov eax, KF_GIGETPIXEL
	 int 0x60

 GiDrawBox:
	mov edx,esp
	mov eax, KF_GIDRAWBOX
	 int 0x60

 GiSetVideoParams:
	mov edx,esp
	mov eax, KF_GISETVIDEOPARAMS
	 int 0x60

 GiGetVideoBPP:
	mov edx,esp
	mov eax, KF_GIGETVIDEOBPP
	 int 0x60

 GiGetVideoHeight:
	mov edx,esp
	mov eax, KF_GIGETVIDEOHEIGHT
	 int 0x60

 GiGetVideoWidth:
	mov edx,esp
	mov eax, KF_GIGETVIDEOWIDTH
	 int 0x60

 UiPrintStr:
	mov edx,esp
	mov eax, KF_UIPRINTSTR
	 int 0x60

 UiPrintChar:
	mov edx,esp
	mov eax, KF_UIPRINTCHAR
	 int 0x60

 UiPrintWStr:
	mov edx,esp
	mov eax, KF_UIPRINTWSTR
	 int 0x60

 UiPrintStrX:
	mov edx,esp
	mov eax, KF_UIPRINTSTRX
	 int 0x60

 UiPrintWStrX:
	mov edx,esp
	mov eax, KF_UIPRINTWSTRX
	 int 0x60

 UiClearScreen:
	mov edx,esp
	mov eax, KF_UICLEARSCREEN
	 int 0x60

 FS_FindFileInit:
	mov edx,esp
	mov eax, KF_FS_FINDFILEINIT
	 int 0x60

 FS_FindFileDone:
	mov edx,esp
	mov eax, KF_FS_FINDFILEDONE
	 int 0x60

 FS_FindFile:
	mov edx,esp
	mov eax, KF_FS_FINDFILE
	 int 0x60

 FS_GetFileInfo:
	mov edx,esp
	mov eax, KF_FS_GETFILEINFO
	 int 0x60

 FS_GetOpenFileInfo:
	mov edx,esp
	mov eax, KF_FS_GETOPENFILEINFO
	 int 0x60

 FS_VolumeExists:
	mov edx,esp
	mov eax, KF_FS_VOLUMEEXISTS
	 int 0x60

 FS_CharToUnicode:
	mov edx,esp
	mov eax, KF_FS_CHARTOUNICODE
	 int 0x60

 FS_UnicodeToChar:
	mov edx,esp
	mov eax, KF_FS_UNICODETOCHAR
	 int 0x60

 FS_Read:
	mov edx,esp
	mov eax, KF_FS_READ
	 int 0x60

 FS_Write:
	mov edx,esp
	mov eax, KF_FS_WRITE
	 int 0x60

 FS_SetFilePos:
	mov edx,esp
	mov eax, KF_FS_SETFILEPOS
	 int 0x60

 FS_GetFileSize:
	mov edx,esp
	mov eax, KF_FS_GETFILESIZE
	 int 0x60

 FS_GetFilePos:
	mov edx,esp
	mov eax, KF_FS_GETFILEPOS
	 int 0x60

 FS_DeleteFile:
	mov edx,esp
	mov eax, KF_FS_DELETEFILE
	 int 0x60

 FS_GetFilePosition:
	mov edx,esp
	mov eax, KF_FS_GETFILEPOSITION
	 int 0x60

 FS_VolGetBytesPerUnit:
	mov edx,esp
	mov eax, KF_FS_VOLGETBYTESPERUNIT
	 int 0x60

 FS_IsUnicode:
	mov edx,esp
	mov eax, KF_FS_ISUNICODE
	 int 0x60

 FS_GetLastError:
	mov edx,esp
	mov eax, KF_FS_GETLASTERROR
	 int 0x60

 FS_SetLastError:
	mov edx,esp
	mov eax, KF_FS_SETLASTERROR
	 int 0x60

 FS_ParsePath:
	mov edx,esp
	mov eax, KF_FS_PARSEPATH
	 int 0x60

 FS_OpenFile:
	mov edx,esp
	mov eax, KF_FS_OPENFILE
	 int 0x60

 FS_ReadFile:
	mov edx,esp
	mov eax, KF_FS_READFILE
	 int 0x60

 FS_WriteFile:
	mov edx,esp
	mov eax, KF_FS_WRITEFILE
	 int 0x60

 FS_CloseFile:
	mov edx,esp
	mov eax, KF_FS_CLOSEFILE
	 int 0x60

 