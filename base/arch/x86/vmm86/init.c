#define _MTOX_THREADS

#include <mtox.h>
#include "vmm.h"

BOOL vmmInitProcess_PageTables(TH_PROCESS p) {

	if (IsKernelProcess(p)) {
		I_PROCESS(p)->vmmData.PTBase = vmPH.PTAddress;
		return TRUE;
	}
	else {
		if ((I_PROCESS(p)->vmmData.PTBase = vmmAllocatePageTables())) {
			UINT32 kernelPageTables = 4 * ((KernelMaxAddress + 0x3fffff) / 0x400000);
			memcpy(I_PROCESS(p)->vmmData.PTBase,vmPH.PTAddress,kernelPageTables);
			return TRUE;
		}
	}
//    if (I_PROCESS(p)->vmmData.PTBase == 0)
	return FALSE;
}

BOOL InitPaging() {
	KernelMaxAddress = pmmGetExtendedMemory() / 4;
    printf("Initializing Paging For EXU #%i: Max:%x,Ttl:%x:%x...\r\n", GetCurrentEXUID(), KernelMaxAddress, pmmGetExtendedMemory());
    SwitchPAE(0);
    SwitchPSE(1);
    SetPagesBase(vmPH.PTAddress);
    SwitchPaging(1);
    printf("Done\r\n");
    return TRUE;
}
