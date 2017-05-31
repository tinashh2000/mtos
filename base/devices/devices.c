#define _MTOX_SYS
#define _MTOX_UI

#include <mtox.h>
#include "devices.h"

void InitDevices() {
	cprintf("ATAInit");
	ATAInit();

    cprintf("i8042\r\n");
    i8042Init();

    cprintf("Devices Ready\r\n");

}

