//#define vmmAllocateMemory(param) vmmAllocateMemoryForProcess(GetCurrentProcess(),param)
//#define vmmReallocateMemory(oldptr,newsize) vmmReallocateMemoryForProcess(GetCurrentProcess(),oldptr,newsize)

EXPORTSTART

MEMPTR  AllocateHandle(TH_THREAD thread, MWORD size);
MEMPTR  GetHandleData(MWORD handle);
void    SetMemory(MEMPTR mptr,DWORD value, DWORD size);

MEMPTR  AllocateMemory(MWORD memSize);
MEMPTR  ReallocateMemory(MEMPTR ptr,MWORD newSize);
BOOL	FreeMemory(MEMPTR mem);

MEMPTR  vmmAllocateMemoryForProcess(TH_PROCESS process,MWORD memSize);
MEMPTR  vmmAllocateMemoryForThread(TH_THREAD process,MWORD memSize);
MEMPTR  vmmAllocateMemoryValue(MWORD memSize,MWORD value);

BOOL    vmmFreeMemory(MEMPTR mem);
BOOL	vmmFreeMemoryForProcess(TH_PROCESS p,MEMPTR mem);

void	memset32(void *dest,MWORD value,MWORD numWords); //unlike memset, it sets 32-bit values
void	memsetvalue(void *dest, MWORD value, UINT32 numBytes, UINT32 valueSize ); //unlike memset, it sets a value of either 1,2, or 4 bytes

void	OXListMemory(void);
void	OXListUsedMemory(void);
void	OXListUnusedMemory(void);
void	OXListMemorySummary(void);
void	OXListThreads(void);
void	OXListProcesses(void);
EXPORTEND


