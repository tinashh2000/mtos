#include <mtos.h>
#include "../disk/disk.h"


#include "ide.h"


#define MAX_IDE_CHANNELS 1
int IDEPorts[4] = { 0x1F0, 0x170, 0x1E8, 0x168};
