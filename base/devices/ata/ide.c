#define _MTOXARCHBUILD
#include <mtox.h>
#include "ide.hxx"

LBAUNITS IdeReadSector(STOR_DEVID id, void *buffer,LBAUNIT lba, LBAUNITS numSectors)  {

	int basePort = IDEPorts[id];
	char *lbap = (char*) &lba;
	LBAUNITS rSize = numSectors * 512;

//	printf("<Read id%i:%x,size:%i,<%i,%i,%i,%i>%i,%x>",id,buffer,rSize,lbap[0],lbap[1],lbap[2],lbap[3],numSectors,basePort);
	outportb(basePort + 6,(lbap[3]) | 0xE0);
	outportb(basePort + 2,(numSectors) & 255);
	outportb(basePort + 3,lbap[0]);
	outportb(basePort + 4,(lbap[1]) & 0xff);
	outportb(basePort + 5,(lbap[2]) & 0xff);
	outportb(basePort + 7,0x20);
	while((inportb(basePort+7) & 8)==0);
	inportstringw(basePort + 0,buffer,rSize);
	return rSize;
}

LBAUNITS IdeWriteSector(STOR_DEVID id, void *buffer,LBAUNIT lba, LBAUNITS numSectors)  {

	int basePort = IDEPorts[id];
//	UINT32 numSectors = (size +511)/512;
//	UINT32 lba = (position/512);
	char *lbap = (char*) &lba;
	LBAUNITS rSize = numSectors * 512;

	outportb(basePort + 6,(lbap[3]) | 0x0E);
	outportb(basePort + 2,(numSectors) & 255);
	outportb(basePort + 3,lbap[0]);
	outportb(basePort + 4,(lbap[1]) & 0xff);
	outportb(basePort + 5,(lbap[2]) & 0xff);
	outportb(basePort + 7,0x30);
	while((inportb(basePort+7) & 8)==0);
	outportstringw(basePort + 0,buffer,rSize);
	return rSize;
}

UINT32	ProbeATAChannel(UINT32 c) {
	return HARDDISK;
}

BOOL	DetectIDE() {
	UINT32 type,c;
	STOR_DEV_DESC	sd;

	for (c=0;c<MAX_IDE_CHANNELS;c++) {
		type = ProbeATAChannel(c);
		if (type) {
			memset(&sd,0,sizeof(STOR_DEV_DESC));
			sd.BytesPerUnit = 512;
			sd.HardwareId = c;
			sd.Size = 0x10000000000;
			sd.Read = &IdeReadSector;
			sd.Write= &IdeWriteSector;
			if (type == HARDDISK) {
				StorageDevice_Inserted(&sd);
			}
		}
	}
	return TRUE;
}
