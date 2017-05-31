#include <mtos.h>
#include <stdlib.h>

EXPORTSTART
	void pmmRegisterMemory(UINT64 address,UINT64 size,MWORD type);

//	UINT64    pmmAllocateMemoryMinMax(MWORD minSize,MWORD maxSize, MWORD mFlags, MWORD internalFlags, TH_PROCESS process,PMEMORY_ADDRESS addr);

	UINT64  pmmAllocateMemoryForProcess(TH_PROCESS process,MWORD memSize);
	MEMPTR  pmmAllocateKernelMemory(MWORD memSize,MWORD flags,MWORD iflags);

	BOOL    pmmReleaseDeviceMemory(UINT64 address,MWORD size);
	BOOL    pmmAllocateDeviceMemory(UINT64 address,MWORD size,MWORD flags);

//	void pmmRecordUsedMemory(UINT64 address,UINT64 size,MWORD type,MWORD flags,TH_PROCESS process);
//	void pmmRecordUnusedMemory(UINT64 address,UINT64 size,MWORD type,MWORD flags,TH_PROCESS process);
	UINT64	pmmGetBlockSize(UINT64 block);
	UINT64  pmmFreeMemory(UINT64 address,UINT64 mSize,TH_PROCESS process);
EXPORTEND

void *__CDECL malloc(size_t size) {
	MEMPTR p;
	if(size ==0) return 0;
	p = (MEMPTR) pmmAllocateMemoryForProcess(GetCurrentProcess(), size);

	return p;
}

void *__CDECL realloc(void *block, size_t newSize) {
	MEMPTR p;
	UINT64	size = pmmGetBlockSize(block);
	UINT64	aSize;

	if( newSize == 0) {
		free(block);
		return 0;
	}
	
	p = (MEMPTR) AllocateMemory(newSize);
	if (p && size) memmove(p,block,size);
	aSize = pmmGetBlockSize(p);
	free(block);
	return p;
}

void __CDECL free(void*ptr) {
	if (ptr==0)
		return;

	UINT64	aSize = pmmGetBlockSize(ptr);
//	printf("<<free:%x>>",aSize);
	pmmFreeMemory((UINT64)ptr,aSize, GetCurrentProcess());
}
