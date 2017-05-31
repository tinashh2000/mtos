#define _MTOX_THREADS

#include <mtox.h>
#include "vmm.h"

#ifdef _MTOX_PSE32

#define GLOBAL_FLAG			0x100
#define PS_FLAG				0x80
#define DIRTY_FLAG			0x40
#define ACCESSED_FLAG		0x20
#define CACHE_DISABLED_FLAG	0x10
#define WRITE_THROUGH_FLAG	0x08
#define SUPERVISOR_FLAG		0x04
#define WRITE_FLAG			0x02
#define PRESENT_FLAG		0x01

MWORD	GetPageSize() {
	return 4096;
}

BOOL InitGlobalPages() {

	INT32 cc;

    vmPH.PTAddress = 0;

    if ((vmPH.PTAddress = pmmAllocateKernelMemory(4096,0,MM_IFLAG_ALIGN4K | MM_IFLAG_BELOW4G))) {
        DWORD* ptr = (DWORD *) vmPH.PTAddress;
        DWORD data = PRESENT_FLAG | WRITE_FLAG | PS_FLAG | GLOBAL_FLAG; //PSE=1, 4MB pages

        for (cc=0;cc < 1024; cc++) {
			
            *ptr = data;
			if (data > 0xe0000000) {
//				printf("(<%x>)", data);
				*ptr = data | CACHE_DISABLED_FLAG;
			}
			
			ptr++;
            data+=0x400000; //Add by 4MB

        }
        return TRUE;
    }
    return FALSE;
}


MEMPTR xmmAllocateMemory(TH_PROCESS p, MWORD memSize, MWORD flags ) {
	return vmmReserveAddressSpace (p,memSize,0,flags);
}


/*
 * Commits memory to an address space. The memory in the address space either has to be free or reserved
 */

MEMPTR vmmCommitMemorySpace(TH_PROCESS p, MWORD commitSize, MWORD flags ) {
	return vmmReserveAddressSpace (p,commitSize,0,flags);
}


/*
 * Finds space enough within the processes' address space and reserves it for the process,
 * no other procedure can allocate to this reserved space
 */
 
MEMPTR	vmmReserveAddressSpace(TH_PROCESS p, MWORD commitSize, MWORD reserveSize, MWORD flags) {

	MWORD	PDEIdx, PTIdx, remainCommit = ALIGN_X(commitSize, 4096), remainReserve = ALIGN_X(reserveSize, 4096);
	MEMPTR	pages;
	DWORD	curPDE, *pCurPDE, *PDEs = I_PROCESS(p)->vmmData.PTBase;
	DWORD	resValue = 0xFFFFFFFE;	//Mark every thing else except for the PRESENT_BIT, this indicates that the page is reserved
	INT64	remainingSize = remainCommit + remainReserve;

	if (GetCurrentProcess() != p && !IsKernelProcess(p))
		return 0;
		
	if (I_PROCESS(p)->vmmData.PTBase == 0)
		vmmInitProcess_PageTables(p);
		
	if (I_PROCESS(p)->vmmData.PTBase == 0)
		return 0;

	AcquireVariableLock(&I_PROCESS(p)->vmmData.VMMLock);
		
	if ((pages = vmmFindAddressSpace(p, remainingSize, flags)) == 0) {
		UnlockVariable(&I_PROCESS(p)->vmmData.VMMLock);
		return 0;	//if we couldnt find an address space
	}
	
	cprintf("<<reservepages:%x,%x,%x>>",(UINT32)p,(UINT32)pages,(UINT32)I_PROCESS(p)->vmmData.PTBase);
	
	PDEIdx = (((MWORD)pages >> 22) & 0x3ff);	//get PDE and PT from address
	PTIdx = (((MWORD)pages >> 12) & 0x3ff);

	cprintf("<<PDEIdx:%x,%x, %x>>",PDEIdx,PTIdx,(((PDEIdx) << 22) | ((PTIdx) << 12)));

	if (PTIdx > 0) {	//if PT is non-zero,
		curPDE = PDEs[PDEIdx];
		cprintf("[(%x,%i)]",PDEIdx,PTIdx);
		if ( curPDE & PRESENT_FLAG ) {	//if PAGE is already present
			pCurPDE = (DWORD*)(curPDE & 0xFFFFF000);
			int cx = PTIdx + (remainingSize / 4096);
			if (cx > 1024) cx = 1024;

			for (int c=PTIdx; c < cx; c++) {

				if (remainingSize > remainReserve) {
					if ((pCurPDE[c] = pmmAllocateMemoryMinMax(4096, 4096, flags | MM_FLAG_PRIVILEGED, MM_IFLAG_ALIGN4K | MM_IFLAG_BELOW4G, p, 0))) {
						pCurPDE[c] |= WRITE_FLAG | PRESENT_FLAG | 0x80;
					}
					else
						break;
				}
				else
					pCurPDE[c] = resValue;

				remainingSize -= 4096;
				if (remainingSize <= 0) break;
			}
			PTIdx = 0;
			PDEIdx++;
		}
	}
	
	if (PTIdx == 0) {
		while (remainingSize > 0) {
			if (PDEs[PDEIdx] == 0 && remainingSize >= 0x400000) {

				if (remainingSize > remainReserve) {
					if ((PDEs[PDEIdx] = pmmAllocateMemoryMinMax(0x400000, 0x400000, flags | MM_FLAG_PRIVILEGED, MM_IFLAG_ALIGN4K | MM_IFLAG_BELOW4G, p, 0))) {
						PDEs[PDEIdx] |= PS_FLAG | WRITE_FLAG | PRESENT_FLAG;
					}
					else
						break;
				}
				else					
					PDEs[PDEIdx] = resValue;

				remainingSize -= 0x400000;
			}
			else if (PDEs[PDEIdx] == 0) {
				if ((curPDE = pmmAllocateMemoryMinMax(4096, 4096, flags | MM_FLAG_PRIVILEGED, MM_IFLAG_ALIGN4K | MM_IFLAG_BELOW4G, p, 0))) {
					pCurPDE = (DWORD*)curPDE;
					
					PDEs[PDEIdx] = curPDE | WRITE_FLAG | PRESENT_FLAG;

					int cx = remainingSize / 4096;

					for (int c=0;c<cx;c++) {
						if (remainingSize > remainReserve) {
							if ((pCurPDE[c] = pmmAllocateMemoryMinMax(4096, 4096, flags | MM_FLAG_PRIVILEGED, MM_IFLAG_ALIGN4K | MM_IFLAG_BELOW4G, p, 0))) {
								pCurPDE[c] |= WRITE_FLAG | PRESENT_FLAG;
							}
							else
								break;
						}
						else
							pCurPDE[c] = resValue;
							
						remainingSize -= 4096;
					}
				}
				else
					break;
			}
			else
				break;

			PDEIdx++;
		}
	}
	
	if (remainingSize) { //PTIdx can be nonzero even if remainSize is 0, so no need to test PTIdx
		printf("Rollback(%s,%i, %x)",__FILE__, __LINE__, remainingSize );
		while(1);
		//Rollback function
	}
	UnlockVariable(&I_PROCESS(p)->vmmData.VMMLock);
	return pages;
}

/*
 * Just finds a free address space. The process VMMLock must be locked before calling this function
 * After this function finds a free address space, it returns the first address of the free address space
 */

MEMPTR	vmmFindAddressSpace(TH_PROCESS p,MWORD size, MWORD flags) {
	MEMPTR	pBase = ((PROCESS*)p)->vmmData.PTBase;
	MWORD	cx = (KernelMaxAddress / 0x400000);	//Search for a free address at 4MB boundary, start here
	MWORD	cy = (0xffffffff / 0x400000);	//End address
	MWORD 	y;
	DWORD *ptr = (DWORD*)pBase;
	DWORD *px, *py;
	MWORD	PDEIdx=0, PTIdx=0;	
	INT64	remainingSize=size;

	cprintf("<fas:%x>",pBase);
	for (int c = cx; c < cy; c++) {
		MEMPTR	p = (MEMPTR) ptr[c];
		if (p == 0) {	//Do we have a free slot
			cprintf("<<%x>>",c);
			if (PDEIdx == 0) {	//If this is the first free slot
				remainingSize = size;	//Reset values
				PDEIdx = c + 1;
				PTIdx = 1;
			}
			remainingSize -= (remainingSize >= 0x400000 ? 0x400000 : remainingSize);	//We may allocate 4MB to this
		}
		else if (((MWORD)p & PRESENT_FLAG)) {	//page has to be present
			if (((MWORD)p & PS_FLAG) == 0) {	//page must not map to 4MB
				px = (DWORD*) ((MWORD) p & 0xfffff000);
				for (y = 0;y < 1024;y++) {		//Run all entries
					if (px[y] == 0) {
						cprintf("<(%x,%x)>",c,y);
						if (PDEIdx == 0) {	//If this is the first free 4K
							remainingSize = size;	//Reset values
							PDEIdx = c + 1;
							PTIdx = y + 1;
						}
						remainingSize -= (remainingSize >= 4096 ? 4096 : remainingSize);
					}
					else {
						PDEIdx = 0;		//If PD is occupied
					}
				}
			}
		}		
		if (remainingSize <= 0)
			break;
		ptr++;
	}
	
	if (remainingSize == 0) {
		return (MEMPTR) (((PDEIdx - 1) << 22) | ((PTIdx - 1) << 12)) ;
	}
	
	return 0;
}

BOOL    vmmFreeMemoryForProcess(TH_PROCESS p,MEMPTR mem) {
	
    return TRUE;
}

#endif