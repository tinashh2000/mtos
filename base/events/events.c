#define _MTOX_EVENTS
#define _MTOX_THREADS
#define _MTOX_UI

#include <mtox.h>

#include "events.hxx"

void InitEvents() {
    if ((eventsQueue = (SYS_EVENT *) AllocateMemory(sizeof(SYS_EVENT) * 4096))) {
		numEvents=0;
        maxEvents=4096;
//        InitResource(&EventsWrite);
//        hEventsThread = CreateThread("EventsThread",GetCurrentProcess(),EventsThreadProc,0,16384,TF_READY,4096,0x87654321);
    }

	if (eventsQueue || maxEvents)
		return;

}

MWORD GetEventsAccess() {
//    GetResource(&EventsWrite);
    return TRUE;
}

MWORD ReleaseEventsAccess() {
//    return ReleaseResource(&EventsWrite);
    return 0;
}

MWORD PendingEvents() {
    return numEvents;
}

void AddEventToQueue(SYS_EVENT *event) {
    UINT32 idx = numEvents;
    UINT32 idx2=idx-1;
    BOOL   bAddEvent = TRUE;

    GetEventsAccess();

	if (0 &&    idx > 0 &&
            event->EventType==EVT_MOUSE_EVENT &&
            eventsQueue[idx2].EventType ==EVT_MOUSE_EVENT &&
            event->eWord1 ==MOUSE_MOVE &&
            eventsQueue[idx2].eWord1 ==MOUSE_MOVE &&
            event->eWord2 == eventsQueue[idx2].eWord2
            ) {

            eventsQueue[idx2].eWord3 += event->eWord3;
            eventsQueue[idx2].eWord4 += event->eWord4;
            bAddEvent=FALSE;
    }

    if (bAddEvent) {
        eventsQueue[idx].EventType= event->EventType;
        eventsQueue[idx].eWord1   = event->eWord1;
        eventsQueue[idx].eWord2   = event->eWord2;
        eventsQueue[idx].eWord3   = event->eWord3;
        eventsQueue[idx].eWord4   = event->eWord4;
        eventsQueue[idx].eWord5   = event->eWord5;
        numEvents++;
		cprintf("nevt:%x",numEvents);
    }
    ReleaseEventsAccess();
}

void RunEventsQueue() {
//    RunThread(hEventsThread);
	__asm {
		nop
		nop
		nop
		nop
		nop
		nop
		int 3
		nop
		nop
		nop
		nop
		nop
		nop
	}
}
  