#pragma once

#include <mtos.h>

IMPORT SYS_EVENT *eventsQueue;
IMPORT UINT32  numEvents;
IMPORT UINT32  maxEvents;

IMPORT BOOL    bEventOccured;
IMPORT TH_THREAD hEventsThread;

EXPORTSTART
	void InitEvents(void);
	MWORD GetEventsAccess(void);
	MWORD ReleaseEventsAccess(void);

	MWORD PendingEvents(void);
	void AddEventToQueue(SYS_EVENT *event);
	void RunEventsQueue(void);
	PROCESS_MSGS *GetMessagesBuffer(TH_PROCESS p);
	MWORD EventsCount(void);
EXPORTEND