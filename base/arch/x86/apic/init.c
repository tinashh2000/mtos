#define _MTOX_THREADS
#include <mtox.h>
#include "apic.h"

BOOL    ApicTestRSDPTable(void *p) {
    CHARPTR  b = (CHARPTR) p;
    UINT8 c,checksum=0;

    //Test the whole APIC2.0 table
    for (c=0;c<sizeof(RSDPDESCRIPTOR);c++){
        checksum += b[c];
    }
    if (checksum == 0) {
        //Checksum is already 0;
        for (c=0;c<20;c++){     //Test the ACPI1 Table
            checksum += b[c];
        }
        if (checksum==0) {
            return TRUE;   
        }
    }
    return FALSE;
}

RSDPDESCRIPTOR* ApicFindTables() {
    UINT32 *p = (UINT32 *) (*((UINT32*) 0x40E) & 0xFFFF);
    UINT32 *q = (UINT32 *) p + (1024/sizeof(UINT32));
    BOOL    bFound = FALSE;

    for (;p < q;p+=4) {
        if (p[0] == ' DSR' && p[1] == ' RTP' && ApicTestRSDPTable(p)) {
            return (RSDPDESCRIPTOR*) p;
        }
    }

    p = (UINT32 *) 0xE0000;
    q = (UINT32 *) 0xFFFFF;

    for (;p < q;p+=4) {
        if (p[0] == ' DSR' && p[1] == ' RTP' && ApicTestRSDPTable(p)) {
            return (RSDPDESCRIPTOR*) p;
        }
    }
    return NULL;
}

void ApicSetTimer(MWORD divisor,UINT64 initCount,MWORD vector) {
    MWORD APIC_Addr = ApicGetBase();
	DisableInterrupts();

	*((MWORD *) (APIC_Addr + APIC_TIMER_DIVIDE_CONFIG)) = divisor;
    *((MWORD *) (APIC_Addr + APIC_INITIAL_TIMER_COUNT)) = (MWORD) initCount;
	*((MWORD *) (APIC_Addr + APIC_LVT_TIMER)) = vector | APIC_TIMER_PERIODIC;
}

void ApicInitTimer() {
    MWORD APIC_Addr = ApicGetBase();
	UINT64	diff = -1;
	UINT64	InitialTicks, CurrentTicks, TickTime; //, ApicTime;
	MWORD	val;
	BOOL	bTimeOut=FALSE;
    UINT32  cpu=GetCurrentEXU();

	printf("<<ex:%i>>", cpu);
	DisableInterrupts();

    SetInterruptVector(APIC_TIMER_INT_VECTOR,((INTHANDLER) ApicTimerInterruptHandler));

	*((MWORD *) (APIC_Addr + APIC_LVT_TIMER)) = 0x90;
    *((MWORD *)(APIC_Addr + APIC_TIMER_DIVIDE_CONFIG)) = APIC_TIMER_DIVIDE_CONFIG_64;

	EnableInterrupts();

	*((MWORD *) (APIC_Addr + APIC_INITIAL_TIMER_COUNT)) = -1;

//    while ((InitialTicks = GetTicksMS()) == 0);
	InitialTicks = GetTicksMS();
	while (diff > 0) {
		diff--;
		if (diff == 0)
			bTimeOut = TRUE;

        CurrentTicks = GetTicksMS();
        if ((TickTime = (CurrentTicks - InitialTicks)) >= 3) {
			*((MWORD *) (APIC_Addr + APIC_LVT_TIMER)) = APIC_LVT_MASKED;
			val = *((MWORD *) (APIC_Addr + APIC_CURRENT_TIMER_COUNT));
			break;
		}
	}

	if (bTimeOut) {
		printf("timeout");
		while(1);
		return;
	}
	
	DisableInterrupts();

	// = (CurrentTicks-InitialTicks);

	ApicTimer[cpu].CountersPerMS = ((UINT32)(((-1 - val)) / TickTime));
    ApicTimer[cpu].TicksPerMS = 1;     //Number of times it ticks per milli
    ApicTimer[cpu].USPerTick  = 1000;   //Number of microseconds per tick,

	if (ApicTimer[cpu].CountersPerMS == 0)
		ApicTimer[cpu].CountersPerMS = 1;

    ApicSetTimer(APIC_TIMER_DIVIDE_CONFIG_64,ApicTimer[cpu].CountersPerMS,0x90);
    ApicTimer[cpu].Ticks=0;

//printf("<ApicCPMS:cpms:%i,val:%i,ticktim:%i,initTicks:%i,curTicks:%i>", (UINT32) ApicTimer[cpu].CountersPerMS, (UINT32)val, (UINT32)TickTime, (UINT32)InitialTicks,(UINT32)CurrentTicks);
	
}

void ApicInit() {
//	MWORD val;
	MWORD APIC_Addr;
    RSDPDESCRIPTOR* rsdp = ApicFindTables();

//    if (rsdp == NULL)
//        FatalError("ACPI Tables Not Found");

	DisableInterrupts();

    APIC_Addr = ApicReadMSR() & ~0xFFF; 

	APIC_BASE[GetCurrentEXU()] = APIC_Addr;	
    ApicEnable(TRUE);

    *((MWORD *) (APIC_Addr + APIC_DEST_FORMAT)) = 0xFFFFFFFF;

    *((MWORD *) (APIC_Addr + APIC_LVT_LINT0)) = (*((MWORD *) (APIC_Addr + APIC_LVT_LINT0)) & 0xFFFE58FF) | (APIC_DELIVERY_MODE_ExtINT);
    *((MWORD *) (APIC_Addr + APIC_LVT_LINT1)) = (*((MWORD *) (APIC_Addr + APIC_LVT_LINT1)) & 0xFFFE58FF) | (APIC_DELIVERY_MODE_NMI);

	*((MWORD *) (APIC_Addr + APIC_TASK_PRIORITY)) = 0;
	*((MWORD *) (APIC_Addr + APIC_SPURIOUS_INTR_VECTOR)) = 0xFF | APIC_ENABLE;

 
	*((MWORD *) (APIC_Addr + APIC_ERROR_STATUS)) = 0;
	*((MWORD *) (APIC_Addr + APIC_ERROR_STATUS)) = 0;

	*((MWORD *) (APIC_Addr + APIC_EOI)) = 0;
	

    *((MWORD *) (APIC_Addr + APIC_LVT_THERMAL_SENSOR)) = 0x10000;   //Disable
	*((MWORD *) (APIC_Addr + APIC_LVT_PERFMON_COUNTERS)) = 0x10000; 	//Disable
	*((MWORD *) (APIC_Addr + APIC_LVT_ERROR)) = 0x10000; 	//Disable

    ApicInitTimer();

	printf("InitAPIC");

	printf("<<%x,%x>>", APIC_Addr,GetCurrentEXUID());
	printf("\r\nInit APIC for EXU #%i APIC V%i, Addr:%x,LINT0:%x,LINT1:%x\r\n", GetCurrentEXUID(), rsdp->Revision + 1,
		*((MWORD *)(APIC_Addr + APIC_ID)),
		*((MWORD *)(APIC_Addr + APIC_LVT_LINT0)),
		*((MWORD *)(APIC_Addr + APIC_LVT_LINT1)));


    Disable8259();
	printf("\r\nDisableInts(%i)",GetCurrentEXUID());

#ifdef _MTOX_X86_IOAPIC
	IoApicInit();
#endif
	printf("\r\nDoneInit(%i)", GetCurrentEXUID());

//    SetInterruptVector(APIC_IRQBASE + 2,NMIInt);
//    IoApicWriteRedirEntry( &ioapic, 2, 2 + APIC_IRQBASE, IOAPIC_DELIVERY_NMI, IOAPIC_FLAG_LEVELSENSE | IOAPIC_FLAG_HIGHACTIVE, ApicGetID() );

}

