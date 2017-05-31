#define _MTOX_THREADS
#include <mtox.h>
#include "apic.h"

void NMIInt() {
	EOI();
}

void updx(MWORD x) {
	MWORD ii = ((0x700 + (x + 48)) << 16) | (0x700 + (x + 48));
	*((unsigned int *)0xb8140) = ii;
	*((unsigned int *)0xb8144) = ii;
}

//extern THREADS_QUEUE *ThreadsQueue[MAX_CPUS];
int cnt=0;
MWORD *ApicTimerInterruptHandler() {

    MWORD *ret=0;
    MWORD exu = GetCurrentEXU();
	if (exu == -1)
		return 0;

//    DisableInterrupts();
    ApicTimer[exu].Ticks += 1;
    TicksUS[exu] += ApicTimer[exu].USPerTick;

	updx(1);
    ret = SchedulerX(exu);
	updx(9);

    return ret;
}