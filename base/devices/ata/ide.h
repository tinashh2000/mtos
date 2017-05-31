#pragma once

EXPORTSTART

LBAUNITS IdeReadSector(STOR_DEVID id, void *buffer,LBAUNIT lba, LBAUNITS numSectors);
LBAUNITS IdeWriteSector(STOR_DEVID id, void *buffer,LBAUNIT lba, LBAUNITS numSectors);
UINT32	ProbeATAChannel(UINT32 c);
BOOL	DetectIDE(void);

EXPORTEND