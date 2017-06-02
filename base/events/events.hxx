SYS_EVENT *eventsQueue;
UINT32  numEvents;
UINT32  maxEvents;

BOOL    bEventOccured;
TH_THREAD hEventsThread;
RESOURCE    EventsWrite;
