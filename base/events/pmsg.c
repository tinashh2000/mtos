#define _MTOX_EVENTS
#define _MTOX_THREADS
#define _MTOX_UI

#include <mtox.h>

PROCESS_MSGS *GetMessagesBuffer(TH_PROCESS p) {
    if (p) {
        if (I_PROCESS(p)->Messages == 0) {
            if ((I_PROCESS(p)->Messages = (PROCESS_MSGS *) AllocateMemory(8192))) {
                I_PROCESS(p)->Messages->numMsgs = 0;
                I_PROCESS(p)->Messages->maxMsgs = (8192 - sizeof(PROCESS_MSGS)) / sizeof (PROCESS_MSG);
//                p->psMessages->msg = (PROCESS_MSG*) ((&p->psMessages) + sizeof(PROCESS_MSGS));
            }
        }
        return I_PROCESS(p)->Messages;
    }
    return NULL;
}
