#include "visual/graphic.h"
#include "visual/video.h"
#include "print.h"

typedef struct {
    PRINTSTRPROC		PrintStr;
    PRINTSTRXPROC		PrintStrX;
    PRINTCHARPROC		PrintChar;

	PRINTWSTRPROC		PrintWStr;
    PRINTWSTRXPROC		PrintWStrX;
//    PRINTWCHARPROC		PrintWChar;

} OUTPUTHANDLERS;

