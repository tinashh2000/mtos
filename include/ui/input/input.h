typedef MWORD (*MOUSEHANDLERPROC)(UINT32 evt,UINT32 mouseIdnButtons,INT32 x,INT32 y,INT32 scrollAmount);
typedef MWORD (*KEYBOARDHANDLERPROC)(MWORD keyboardId,MWORD evt,MWORD evWord1,MWORD evWord2);
typedef MWORD (*TOUCHHANDLERPROC)(MWORD touchId,MWORD evt,MWORD evWord1,MWORD evWord2,MWORD evWord3);

typedef struct {
    MOUSEHANDLERPROC    MouseHandler;
    KEYBOARDHANDLERPROC KeyboardHandler;
    TOUCHHANDLERPROC    TouchHandler;    
} INPUTHANDLERS;


/*

Defined by primary module to receive mouse,touch,key messages
If non exists, a module with blank parameters can be used

*/

#include "keyboard.h"