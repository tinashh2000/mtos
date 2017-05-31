#define _MTOXARCHBUILD

#define _MTOX_THREADS
#define _MTOX_MMMGR
#define _MTOX_SYS
  
#include <mtox.h>

#include "i386.hxx"

MWORD *TimerInterruptHandler() {

	MWORD *ret = 0;
	MWORD exu = GetCurrentEXU();
	if (exu == -1)
		return 0;

	ret = SchedulerX(exu);

	return ret;
}

UINT32  GetCurrentEXUID() {
 
    X86REGS xr;
    xr.rAX = 1;
    xr.rCX = 0;
    xCPUID(&xr);

    return  (xr.rBX >> 24) & 0xFF;

}

void ArchInit(VOIDPROC InitOS_Proc) {
    UINT32 cpuNum;
    MWORD ThisCPUID;

	InitOS_ProcX = InitOS_Proc;	//Stack will be changed
//    memset( &LastFPUThread[0],0,sizeof(TH_THREAD) * MAX_CPUS);

    ThisCPUID = GetCurrentEXUID();

    Init386();

    DisableInterrupts();

	cpuNum = RegisterEXU(X86_CPU,INTEL_X86,ThisCPUID,ThisCPUID);
    InitVMM();

    InitPaging();
	
	ApicInit();

	printf("<<\033000100000044System EXU # %i / %i:%i Detected, ID:%x\033000100ffffff>>\r\n",cpuNum,GetCurrentEXU(),GetCurrentEXUID(),ThisCPUID);

	SetInterruptVector(0x91, ((INTHANDLER)TimerInterruptHandler));

    GetEXUInfo();
	ResetTimers();

	InitOS_ProcX();
}

void*	ArchGetReservedMemoryAddresses() {
	return (void *) &preReservedAddress;
}

BOOL	FreeThreadContext(TH_THREAD th) {
	EXUCONTEXT *cc =&I_THREAD(th)->context;
	vmmFreeMemoryForProcess(I_THREADPROCESS(th), cc->stack);
	return true;
}

BOOL	InitProcessContext(TH_PROCESS p) {
	if (!vmmInitProcess_PageTables(p)) return FALSE;
	return TRUE;
}

BOOL InitThreadContext(TH_THREAD t,MWORD ePoint,MWORD dStackSize,MWORD dMAllocSize,MWORD tWord1,MWORD tWord2) {
    MEMPTR  tStack;
    MEMPTR  tMAlloc;
    MWORD *StackTop;
    EXUCONTEXT *cc =&I_THREAD(t)->context;

    if (t == 0) return FALSE;

	if (I_THREADPPROCESS(t)->NumThreads == 0) {
		if (!vmmInitProcess_PageTables(I_THREADPROCESS(t))) return FALSE;
    }
	
    if (dStackSize > 0) {
        tStack = vmmAllocateMemoryForThread( I_THREADPROCESS(t),dStackSize);
        if (tStack == NULL) return FALSE;
    }

    if (dMAllocSize > 0) {
        tMAlloc = vmmAllocateMemoryForThread( I_THREADPROCESS(t), dMAllocSize);
        if (tMAlloc == NULL) {
            vmmFreeMemoryForProcess(I_THREADPROCESS(t),tStack);
            return FALSE;
        }
    }
	
	
    StackTop = (MWORD *)((MWORD)((CHARPTR)tStack + dStackSize - (sizeof(MWORD) * 16)) & (~0x0F));
//	printf("stk:%x",StackTop);

	StackTop[0] = 0;  //return Address
	StackTop[1] = (MWORD) t;
	StackTop[2] = (MWORD) tMAlloc;
	StackTop[3] = dMAllocSize;
	StackTop[4] = tWord1;
	StackTop[5] = tWord2;

	InitContext86(cc, ePoint, StackTop, I_THREADPPROCESS(t)->vmmData.PTBase, IsKernelThread(t) ? 0:3);
//	printf("priv:%i",(IsKernelThread(t) ? 0:3));

	return TRUE;
}

void    GetEXUVendorString(CHARPTR str) {
    X86REGS xr;
    MWORD *vs = (MWORD *) str;

    if (str==NULL) return;

    memset(&xr,0,sizeof(X86REGS));

    xr.rAX = 0;
    xr.rCX = 0;
    xCPUID(&xr);

    vs[0] = xr.rBX;
    vs[1] = xr.rDX;
    vs[2] = xr.rCX;

    str[13] = 0;

    return;
}

MWORD   GetEXUVendor() {
    char    VendorString[13];
    GetEXUVendorString((char *) &VendorString);
    if ( strcmp((char*)&VendorString[0],"GenuineIntel") == 0) {
        return INTEL_X86;
    }
    else if ( strcmp((char*)&VendorString[0],"AuthenticAMD") == 0 ) {
        return AMD_X86;
    }
    else if ( strcmp((char*)&VendorString[0],"VIA VIA VIA") == 0 ) {
        return VIA_X86;
    }
    else
        return GENERIC_X86;
}

BOOL   GetEXUInfo() {
    MWORD ven = GetEXUVendor();
    X86REGS xr;
    memset(&xr,0,sizeof(X86REGS));

	AMDCPU *amd  =  (AMDCPU*) &CPUsInfo;

    if (1 || ven == AMD_X86) {
        xr.rAX = 0;
        xCPUID(&xr);
        amd->LastCPUIDFunc = xr.rAX;
        xr.rAX = 1;
        xr.rCX = 0;
        xCPUID(&xr);
        amd->bHTT = (xr.rDX & 0x10000000) ? TRUE:FALSE;
        amd->NumLogicalCPUs = (xr.rBX >> 16) & 0xFF;

        xr.rAX = 0x80000000;
        xCPUID(&xr);
        amd->LastCPUIDExtFunc = xr.rAX;
        xr.rAX = 0x80000008;
        xCPUID(&xr);
        amd->ApicIDCoreIDSize = (xr.rCX >> 12) & 0x0F;
        amd->NumCores = xr.rCX & 0xFF;
        if (amd->ApicIDCoreIDSize > 0) {
            amd->MaxCores = 1 << amd->ApicIDCoreIDSize;
        }
        else {
            amd->MaxCores = amd->NumCores + 1;
        }

        amd->NumCores++;
        amd->NumThreadsPerCore = (amd->bHTT)?
        ((amd->bCmpLegacy)?1:(UINT16) (amd->NumLogicalCPUs/amd->NumCores)):1;

        printf("NC:%i,TPC:%i\r\n",amd->NumCores,amd->NumThreadsPerCore);
    }
    else if (ven == INTEL_X86) {
    }
    else if (ven == VIA_X86) {
    }
    return TRUE;
}

void ArchReboot() {
	DisableInterrupts();
	UINT8 good = 0x02;
	while (good & 0x02)
		good = inportb(0x64);
	outportb(0x64, 0xFE);
	__asm hlt;
	while (1);
}

void ArchShutdown() {
	DisableInterrupts();
	UINT8 good = 0x02;
	while (good & 0x02)
		good = inportb(0x64);
	outportb(0x64, 0xFE);
	__asm hlt;
	while (1);
}