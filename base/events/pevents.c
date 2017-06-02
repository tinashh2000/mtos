#define _MTOX_EVENTS
#define _MTOX_THREADS
#define _MTOX_UI

#include <mtox.h>

MWORD EventsClassCounter = EVT_CUSTOM;

MWORD	RegisterEventsClass() {
	if (EventsClassCounter < 0xffff)
		return EventsClassCounter++;

	return 0;
}

PROCESS_EVENTS *GetEventsBuffer(TH_PROCESS p) {
    if (p) {
        if (I_PROCESS(p)->Events == 0) {
            if ((I_PROCESS(p)->Events = (PROCESS_EVENTS *) AllocateMemory(8192))) {
                I_PROCESS(p)->Events->numEvents = 0;
				I_PROCESS(p)->Events->firstEvent = 0;
				I_PROCESS(p)->Events->lastEvent = 0;
				I_PROCESS(p)->Events->writeLock = 0;
				I_PROCESS(p)->Events->readLock = 0;
                I_PROCESS(p)->Events->maxEvents = (8192 - sizeof(PROCESS_EVENTS)) / sizeof (PROCESS_EVENT);
//                p->psEvents->evt = (PROCESS_EVENT*) ((&p->psEvents) + sizeof(PROCESS_EVENTS));
//                printf("ad %x,%x, %x",p->psEvents,&p->psEvents->evt,&p->psEvents->evt[0]);
            }
        }
        return I_PROCESS(p)->Events;
    }
    return NULL;
}

/*
Called by a thread. This function blocks the thread until there are events on the process' queue. Note that there is only 1 queue for events for each process. Only 1 thread must be assigned to check the events while the other threads are also either waiting to act on events or are doing something else.
*/
BOOL    WaitForEvents() {

    TH_PROCESS p =  GetCurrentProcess();
	PROCESS_EVENTS *pEvt;

    if ((pEvt = GetEventsBuffer(p)) == 0)
		return FALSE;
		
	while (pEvt->numEvents == 0) {
//		printf("{-}");
		WaitingForEvent(GetCurrentThread());
//		printf("{=%x}", pEvt->numEvents);

	}
//	EndWaiting();

	return TRUE;

}

BOOL	EventsInQueue() {
    TH_PROCESS p =  GetCurrentProcess();
	PROCESS_EVENTS *pEvt;
    if ((pEvt = GetEventsBuffer(p)) == 0)
		return FALSE;
		
	if (pEvt->numEvents > 0) {
		cprintf("<@ev>");
		return TRUE;
	}
    return FALSE;
}


int instx=0;
LOCK	evtHandlerLock;

BOOL	GetNextEvent(PROCESS_EVENT *gEvt) {

	PROCESS_EVENTS *pEvt;
	if ((pEvt = GetEventsBuffer(GetCurrentProcess()))) {

		LockVariable(&pEvt->readLock);
		UINT32 c, d, nxEvt, mouseDontConsolidate = 0;
		UINT32 numProcessedEvents = 0;
		UINT16	lastEventType = 0;

		if (pEvt->numEvents > 0) {
			PROCESS_EVENT *evt, *tEvt;
			c = pEvt->firstEvent;
			evt = &pEvt->evt[c];

			memcpy((void*) gEvt, (void*) evt, sizeof(PROCESS_EVENT));
			evt->eWord6 = c;

			pEvt->firstEvent++;
			pEvt->numEvents--;
			if (pEvt->firstEvent >= (pEvt->maxEvents)) {
				pEvt->firstEvent = 0;
			}

			lastEventType = evt->EventClass;
		}

		UnlockVariable(&pEvt->readLock);
		return TRUE;
	}
	return FALSE;
}


void    ProcessEvents() {
	PROCESS_EVENTS *pEvt;
	instx++;

	printf("ProcessEvents");
	while (1) 
		;
    if ((pEvt = GetEventsBuffer(GetCurrentProcess()))) {
		
        if (pEvt->numEvents > 0) {
			LockVariable(&pEvt->readLock);
            UINT32 c,d,nxEvt,mouseDontConsolidate=0;
			UINT32 numProcessedEvents = 0;
			UINT16	lastEventType=0;
            while (pEvt->numEvents > 0) {
				PROCESS_EVENT *evt,*tEvt;
				c = pEvt->firstEvent;
                evt = &pEvt->evt[c];
///
				pEvt->firstEvent++;
				pEvt->numEvents--;
                if (pEvt->firstEvent >= (pEvt->maxEvents)) {
					pEvt->firstEvent = 0;
                }
				
				lastEventType = evt->EventClass;
            }
			UnlockVariable(&pEvt->readLock);
        }
    }
}


void    EventsLoop() {
    while(ProcessIsRunning()) {
        WaitForEvents();
        ProcessEvents();
    }
    return;
}


void    DoEvents() {
    if (ProcessIsRunning()) {
        if (EventsInQueue())
			ProcessEvents();
    }
    return;
}

/*
SendProcessEvent passes information to processes.
It can be called from an INT handler

TODO:   Remove LockVariable which waits for a lock to be free. Instead use, AcquireVariableLock which does not block
*/

void    SendProcessEvent(TH_PROCESS p,PROCESS_EVENT* evt) {
	PROCESS_EVENTS *pEvt;
	UINT32	lastEvt;
	PROCESS_EVENT *lastEvtx;
    if ((pEvt = GetEventsBuffer(p))) {
        UINT32 idx = pEvt->lastEvent;
        BOOL    bAddEvent = TRUE;
		LockVariable(&pEvt->writeLock);
		if (pEvt->numEvents < pEvt->maxEvents) {
			memcpy((void*)&pEvt->evt[idx], (void*)evt, sizeof(PROCESS_EVENT));
			pEvt->numEvents++;
			pEvt->lastEvent++;
//			printf("\r\n<ev:%x,%i,%i,%i, hd:%x, %i>", p, pEvt->evt[idx].EventID, idx, I_PROCESS(p)->EventWaitQueue.NumEntries, I_PROCESS(p)->EventWaitQueue.xl.listHead, I_PROCESS(p)->EventWaitQueue.xl.numItems);
			if (I_PROCESS(p)->EventWaitQueue.NumEntries) {
				EndWaitingForEvent(p);
			}
			if (pEvt->lastEvent >= pEvt->maxEvents) pEvt->lastEvent = 0;
		}
		else
			printf("<<Overflow>>");
		UnlockVariable(&pEvt->writeLock);
    }
    return;
}

