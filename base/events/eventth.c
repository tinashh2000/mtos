#define _MTOX_EVENTS
#define _MTOX_THREADS

#include <mtox.h>

MWORD EventsThreadProc(TH_THREAD thread,MEMPTR mAllocPTR,UINT32 mAllocSize,MWORD tWord1,MWORD tWord2) {
//    char buf[32];
    UINT32  cc=0;
	printf("eventsproc");
    while (1) {
        if (numEvents > 0) {
            UINT32 c=0;
            while (c < numEvents) {
                MWORD evType = eventsQueue[c].EventType;

                if (evType != 0) ExecEvent(&eventsQueue[c]);
                c++;

                if (c > (maxEvents/2)) {
                    GetEventsAccess();
                    if (c < numEvents) {
                        memmove(&eventsQueue[0],&eventsQueue[c],(numEvents-c)* sizeof(SYS_EVENT));
                        numEvents = numEvents - c;
                        c=0;
                    }
                    ReleaseEventsAccess();
                }
            }

            if (c >= numEvents) {
                GetEventsAccess();
                if (c < numEvents) {
                    memmove(&eventsQueue[0],&eventsQueue[c],(numEvents-c)* sizeof(SYS_EVENT));
                    numEvents = numEvents - c;
                    c=0;
                }
                else
                    numEvents = 0;
                ReleaseEventsAccess();
            }
            else
                numEvents=0;

        }
//        SuspendThread(GetCurrentThread());
//        PrintStrXY(5,0,xsprintf((char*)&buf,"<%i>",cc));
        cc++;
    }
}

MWORD EventsCount() {
    return numEvents;
}

void ExecEvent(SYS_EVENT* evt) {
    switch (evt->EventType) {
        case 0:
            break;
       case EVT_TIMER_EVENT:
           switch (evt->eWord1) {
               case TIMER_TIMEOUT:
                   break;
               case TIMER_TICK:
                   break;
           }
           break;
       case EVT_POWER_EVENT:
           break;
           break;
		}

}
