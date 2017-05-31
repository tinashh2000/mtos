#define _MTOXARCHBUILD

#define _MTOX_THREADS
#define _MTOX_MMMGR
#define _MTOX_SYS
  
#include <mtox.h>
#include "initap.hxx"

extern LOADER_PARAMS LoaderParams;

void    APEntryPoint() {

    MWORD ThisCPUID;
    MWORD cpuNum;
	MWORD mttest;
    ThisCPUID = GetCurrentEXUID();
	DisableInterrupts(); //Must already be disabled but to be sure
//	while (1);
	LockVariable(&APInitLock);
    InitAP();
	InitPaging();
	cpuNum = RegisterEXU(X86_CPU, INTEL_X86, ThisCPUID, ThisCPUID);
	ApicInit();
	printf("\r\nInitAPIC OK...");
	UnlockVariable(&APInitLock);

	EnableInterrupts();
	while (1);
	DisableInterrupts();
	while (1) {
		*((char *)0xb8180 + (cpuNum * 4)) += 1;;
	}
}

void InitAPs() {
    UINT32 APVector;

	APVector = ((MWORD) LoaderParams.APVector) >> 12;

    EnableInterrupts();

	printf("<<InitAPs Cmd: %i>>", GetTicksMS());
    ApicWriteRegister(APIC_INTR_COMMAND_1,0xC4500);
    Delay(1000);
    ApicWriteRegister(APIC_INTR_COMMAND_1,0xC4600 | APVector);
	Delay(1000);
	printf("<<InitAPs Exit>>");
}
