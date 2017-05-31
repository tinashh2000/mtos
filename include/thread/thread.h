#pragma once
#define TF_CRITICAL				0x000001		//Avoid task switching
#define TF_PRIORITY				0x000002		//Priority
#define TF_READY				0x000004		//This thread is ready. A thread must be ready for it to be allowed in ready queues

typedef MWORD TH_HANDLE;
typedef MWORD TH_PROCESS;
typedef MWORD TH_THREAD;
typedef MWORD (*THREAD_PROC)(TH_THREAD thread,MEMPTR mAllocPTR,UINT32 mAllocSize,MWORD tWord1,MWORD tWord2);
typedef MWORD(*TIMERPROC)(MWORD param1,MWORD param2);


typedef struct {
	MWORD		L1;		//Level 1 lock, gives routines access to change parameters before locking L2.
	MWORD		L2;
	UINT64		Time;
	char        name[8];
	char		lockname[41];
	int			exu;
	TH_THREAD	Thread;
} LOCK;

enum THREAD_PRIORITY {
	THREAD_PRIORITY_SERVICE=0x00,
	THREAD_PRIORITY_IDLE=0x20,
	THREAD_PRIORITY_LOWEST=0x40,
	THREAD_PRIORITY_LOW=0x60,
	THREAD_PRIORITY_NORMAL= 0x80,
	THREAD_PRIORITY_HIGH=0xA0,
	THREAD_PRIORITY_HIGHEST=0xC0,
	THREAD_PRIORITY_REALTIME=0xE0
};

EXPORTSTART

TH_THREAD CreatePriorityThread(TH_PROCESS process,       // Parent process
THREAD_PROC thProc,  // Address within process
MWORD memAlloc,      // Memory to allocate
MWORD stackAlloc,    // Stack to allocate
MWORD flags,         // Flags
MWORD tWord1,        // Param1 for thread
MWORD tWord2         // Param2 for thread
);

TH_THREAD CreateThread(
char *ThreadName,		//Name of the thread
TH_PROCESS process,       // Parent process
THREAD_PROC thProc,  // Address within process
MWORD memAlloc,      // Memory to allocate
MWORD stackAlloc,    // Stack to allocate
MWORD flags,         // Flags
MWORD tWord1,        // Param1 for thread
MWORD tWord2         // Param2 for thread
);

TH_PROCESS CreateProcess(char *ProcessName, THREAD_PROC cEntry,MWORD cMemAlloc,MWORD cStackAlloc,UINT32 cPriority,MWORD cFlags,MWORD tWord1,MWORD tWord2);

void    _idle(void);
void    _active(void);
void	_halt(void);

UINT32  GetNumPhyCPUs(void);
UINT32  GetNumCores(void);
UINT32  GetNumEXUs(void);
UINT32  GetMaxEXU(void);
UINT32  GetNumCoresPerEXU(void);
UINT32  GetNumEXUsPerCore(void);
UINT32  GetCurrentEXU(void);
UINT32  GetEXUFamily(MWORD cpu);

BOOL RunThread(TH_THREAD th);
BOOL SuspendThread(TH_THREAD th);

TH_PROCESS  GetCurrentProcess(void);
TH_THREAD   GetCurrentThread(void);
BOOL CriticalProcessStart(void);
BOOL CriticalProcessEnd(void);


BOOL    SpinLock(LOCK *lock);
BOOL    SpinUnlock(LOCK *lock);
BOOL    KernelSpinLockVariable(MWORD *lock);
void    InitLock(LOCK *lock,char*name);
BOOL    IsVariableLocked(MWORD *var);
BOOL    UnlockVariable(MWORD* var);

BOOL    AcquireVariableLock(MWORD *var);
BOOL    LockVariable(MWORD* var);

BOOL    Lock(LOCK* lock);
BOOL    LockX(LOCK* lock,char *place);
BOOL    Unlock(LOCK *lock);
BOOL    AcquireLock(LOCK *lock);
BOOL    IsLocked(LOCK *lock);

BOOL	ProcessIsRunning(void);
void	FavourThread(TH_THREAD thread);
BOOL    ProcessIsRunning(void);
BOOL RetireThread(TH_THREAD th);
BOOL IsCurrentThreadKernel(void);
BOOL IsCurrentProcessKernel(void);
BOOL	IsThreadCritical(TH_THREAD t);
BOOL    CriticalProcessEnd(void);
BOOL    CriticalProcessStart(void);
BOOL SuspendThread(TH_THREAD th);
BOOL DestroyThread(TH_THREAD t);
BOOL RunThread(TH_THREAD th);
TH_THREAD   GetCurrentThread(void);
TH_PROCESS  GetCurrentProcess(void);
char *GetCurrentProcessName(void);
char *GetCurrentThreadName(void);
BOOL CriticalSectionStart(void);
BOOL CriticalSectionEnd(void);

BOOL	KernelCriticalSectionStart(void);
BOOL	KernelCriticalSectionEnd(void);

BOOL	IsKernelCriticalSection(void);

TH_PROCESS	GetCurrentProcess(void);
TH_THREAD	GetCurrentThread(void);
BOOL    IsKernelProcess(TH_PROCESS p);
BOOL    IsKernelThread(TH_THREAD t);

void	SetThreadLog(char *log);

MWORD	SetTimeOut(UINT32 msDelay, TIMERPROC TimerProc, MWORD param1, MWORD param2);
MWORD	SetTimerInterval(UINT32 msDelay, TIMERPROC TimerProc, MWORD param1, MWORD param2);
BOOL	CancelTimer(MWORD timer);

EXPORTEND
