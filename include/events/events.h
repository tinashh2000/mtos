typedef struct {
    MWORD   EventType;
    MWORD   eWord1;
    MWORD   eWord2;
    MWORD   eWord3;
    MWORD   eWord4;
    MWORD   eWord5;
} SYS_EVENT;

typedef struct {
    UINT16  EventClass;
    UINT16  EventID;
    MWORD   EventTime;
    MWORD   eWord1;
    MWORD   eWord2;
    MWORD   eWord3;
    MWORD   eWord4;
    MWORD   eWord5;
    MWORD   eWord6;
} PROCESS_EVENT;

typedef struct {
    MWORD   MsgType;
    MWORD   mWord1;
    MWORD   mWord2;
    MWORD   mWord3;
    MWORD   mWord4;
    MWORD   mWord5;
} SYS_MSG;

typedef struct {
    UINT16  MsgClass;
    UINT16  MsgID;
    MWORD   MsgTime;
    MWORD   mWord1;
    MWORD   mWord2;
    MWORD   mWord3;
    MWORD   mWord4;
    MWORD   mWord5;
    MWORD   mWord6;
} PROCESS_MSG;

typedef struct {
    UINT32  numEvents;
    UINT32  maxEvents;
    UINT32  firstEvent;
	UINT32	lastEvent;
    MWORD   readLock;
	MWORD	writeLock;
	TH_THREAD	waitingThread;	//Thread waiting for events
    PROCESS_EVENT   evt[];
} PROCESS_EVENTS;

typedef struct {
    UINT32  numMsgs;
    UINT32  maxMsgs;
    UINT32  lastMsg;
    MWORD   Locked;
    PROCESS_MSG msg[];
} PROCESS_MSGS;

enum EVENT_TYPES {
    EVT_MOUSE_EVENT=1,
    EVT_KEYBOARD_EVENT,
    EVT_TOUCH_EVENT,
    EVT_TIMER_EVENT,
    EVT_POWER_EVENT,
	EVT_CUSTOM = 0x1000
};

#define MTOS_CUSTOM_EVENTS	0xA000

enum TOUCH_EVENTS {
    TOUCH_DEPRESS=0x100,
    TOUCH_RELEASE
};

enum TIMER_EVENTS {
    TIMER_TIMEOUT=0x120,
    TIMER_TICK
};

enum KEYBOARD_EVENTS {
	KEYBOARD_INSERTED=0x130,
	KEYBOARD_REMOVED,
    KEY_DEPRESS,
    KEY_RELEASE,
    KEY_PRESS
};

enum MOUSE_EVENTS {
	MOUSE_INSERTED=0x140,
	MOUSE_REMOVED,
    MOUSE_CHANGE_STATE,
    MOUSE_MOVE,
    MOUSE_OVER,
    MOUSE_OUT,
    MOUSE_SCROLL,
    MOUSE_LEFTPRESS,
    MOUSE_LEFTRELEASE,
    MOUSE_MIDPRESS,
    MOUSE_MIDRELEASE,
    MOUSE_RIGHTPRESS,
    MOUSE_RIGHTRELEASE,
    MOUSE_4THPRESS,
    MOUSE_4THRELEASE,
    MOUSE_5THPRESS,
    MOUSE_5THRELEASE,
    MOUSE_LEFTCLICK,
    MOUSE_RIGHTCLICK,
    MOUSE_DBLCLICK,
};

EXPORTSTART

    void RunEventsQueue(void);
    void AddEventToQueue(SYS_EVENT *event);
    void WaitForEvent(SYS_EVENT *rsrc);
    void DoEvents(void);
	MWORD	RegisterEventsClass(void);
	void SendProcessEvent(TH_PROCESS p,PROCESS_EVENT* evt);
    MWORD EventsThread(TH_THREAD thread,MEMPTR mAllocPTR,UINT32 mAllocSize,MWORD tWord1,MWORD tWord2);
    MWORD PendingEvents(void);
    MWORD EventsThreadProc(TH_THREAD thread,MEMPTR mAllocPTR,UINT32 mAllocSize,MWORD tWord1,MWORD tWord2);

    PROCESS_EVENTS *GetEventsBuffer(TH_PROCESS p);
    BOOL    WaitForEvents(void);
    void    ProcessEvents(void);
	BOOL	GetNextEvent(PROCESS_EVENT *gEvt);
    void    EventsLoop(void);
	
	void    DoEvents(void);
	BOOL	EventsInQueue(void);

EXPORTEND
