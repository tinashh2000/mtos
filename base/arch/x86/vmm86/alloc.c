#define _MTOX_THREADS

#include <mtox.h>
#include "vmm.h"

MEMPTR  vmmAllocatePageTables() {
    MEMPTR memptr = pmmAllocateKernelMemory(4096,0,MM_IFLAG_ALIGN4K | MM_IFLAG_BELOW4G);
	if (memptr) {
		memset(memptr,0,4096);
	}
	return memptr;
}

MEMPTR  vmmAllocateKernelMemory(MWORD size, MWORD flags,MWORD iFlags) {
    return (MEMPTR) pmmAllocateMemoryMinMax(size, size, flags | MM_FLAG_PRIVILEGED, iFlags | MM_IFLAG_ALIGN4K | MM_IFLAG_BELOW4G, GetCurrentProcess(),NULL);
}

MEMPTR	vmmAllocateMemoryForProcess(TH_PROCESS p,MWORD size) {
	MEMPTR pp =  (MEMPTR)pmmAllocateMemoryMinMax(size, size, MM_FLAG_PRIVILEGED, MM_IFLAG_ALIGN4K | MM_IFLAG_BELOW4G, p, NULL);
	return pp;

	if (IsKernelProcess(p)) {

		if (IsCurrentProcessKernel()) {
			if (myvar == 33)
				return (MEMPTR)pmmAllocateMemoryMinMax(size, size,  MM_FLAG_PRIVILEGED,  MM_IFLAG_ALIGN4K | MM_IFLAG_BELOW4G, p, NULL);
			else
				return vmmAllocateKernelMemory(size,0,0);
		}
		printf("vfail");
		return NULL;
    }
	printf("(va<->)");
	return vmmAllocateKernelMemory(size, 0, 0);
	return xmmAllocateMemory(p,size,0);
}

MEMPTR	vmmReallocateMemoryForProcess(TH_PROCESS p,MEMPTR ptr,MWORD size) {
	return 0;
}

MEMPTR	vmmAllocateMemoryForThread(TH_THREAD th, MWORD size) {
	if (IsKernelProcess(th)) {
		if (IsCurrentProcessKernel()) {
			return (MEMPTR) pmmAllocateMemoryMinMax(size, size, MM_FLAG_THREADLOCAL | MM_FLAG_PRIVILEGED, MM_IFLAG_ALIGN4K | MM_IFLAG_BELOW4G, GetCurrentThread(),NULL);
		}
		return NULL;
    }
	return (MEMPTR) pmmAllocateMemoryMinMax(size, size, MM_FLAG_THREADLOCAL | MM_FLAG_PRIVILEGED, MM_IFLAG_ALIGN4K | MM_IFLAG_BELOW4G, GetCurrentThread(),NULL);
	return xmmAllocateMemory(th,size,MM_FLAG_THREADLOCAL);
}
