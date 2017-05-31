#include <mtos.h>
#include "ata.h"
BOOL ATAInit() {
	return TRUE;
	DetectIDE();
	DetectAHCI();
	return TRUE;
}
