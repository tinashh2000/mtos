#define _MTOX_FILESYS

#include "disk.h"
UINT32 Disk_MaxOSID = 0;

#define STORDEV_VERIFYID(diskid) (diskid > 0 && diskid <= Disk_MaxOSID )

#include "disk.hxx"
BOOL	StorageDevice_Inserted(STOR_DEV_DESC *sd) {
	UINT32 c;
	for (c=0;c<MAX_DRIVES;c++) {
		if (Storage_Devices[c].OS_Id == 0) {
			STOR_DEV *xsd = &Storage_Devices[c];
			xsd->OS_Id = c + 1;
			xsd->Flags = DISK_FLAG_INSERTED;
			cprintf("<Disk Inserted %x,%i .....sz:%i,%x %x ", xsd->OS_Id, c, sizeof(STOR_DEV_DESC), ((char *)&xsd->OS_Id), ((char*)&xsd->BytesPerUnit));


			memcpy(xsd,sd,sizeof(STOR_DEV_DESC));
//			printf("<Disk Inserted %x,%c,>",xsd->OS_Id,c);

			if ( Disk_MaxOSID < xsd->OS_Id ) Disk_MaxOSID = xsd->OS_Id;

//			printf("<Disk Inserted %x,%c,>",xsd->OS_Id,c);


			if (!FS_DontMountList(xsd->OS_Id)) {
				cprintf("<Mount,,,>");
				FS_Mount(xsd->OS_Id);
//				FS_Mount(xsd->OS_Id);
				cprintf("<Mount End>");
			}
			return true;
		}
	}
	return false;
}

UINT32	StorageDevice_GetBytesPerUnit(STOR_DEVID diskid) {
	STOR_DEV *xsd;
	if (STORDEV_VERIFYID(diskid)) {
		xsd = &Storage_Devices[diskid - 1];
//		printf("<bbpu:%i,%i>",diskid,xsd->BytesPerUnit);
		if (xsd->Flags & DISK_FLAG_INSERTED) {
			return xsd->BytesPerUnit;
		}
	}
	return 0;
}

BOOL	StorageDevice_Removed(STOR_DEVID diskid) {
	STOR_DEV *xsd = &Storage_Devices[diskid - 1];
	if (STORDEV_VERIFYID(diskid) && xsd->Flags & DISK_FLAG_INSERTED) {
		FS_Unmount(xsd->OS_Id);
		xsd->Flags = 0;
		return TRUE;
	}
	return FALSE;
}

LBAUNITS	StorageDevice_Read(STOR_DEVID diskid,void *buffer,LBAUNIT LBAUnit,LBAUNITS numUnits) {
	STOR_DEV *xsd = &Storage_Devices[diskid - 1];
	if (STORDEV_VERIFYID(diskid) && xsd->Flags & DISK_FLAG_INSERTED) {
		return xsd->Read(xsd->HardwareId,buffer,LBAUnit,numUnits);
	}
	return 0;
}

LBAUNITS	StorageDevice_ReadAbs(STOR_DEVID diskid,void *buffer,UINT64 position,LBAUNITS size) {
	STOR_DEV *xsd = &Storage_Devices[diskid - 1];
	if (STORDEV_VERIFYID(diskid) && xsd->Flags & DISK_FLAG_INSERTED) {
		UINT32 bpu = xsd->BytesPerUnit;
		UINT64 npos = (position/bpu);
		UINT32 nsize = (size+bpu-1)/bpu;
		return xsd->Read(xsd->HardwareId,buffer,npos,nsize);
	}
	return 0;
}

LBAUNITS	StorageDevice_Write(STOR_DEVID diskid, void *buffer, UINT64 LBAUnit, LBAUNITS numUnits) {
	STOR_DEV *xsd = &Storage_Devices[diskid - 1];
	if (STORDEV_VERIFYID(diskid) && xsd->Flags & DISK_FLAG_INSERTED) {
		return xsd->Write(xsd->HardwareId,buffer,LBAUnit,numUnits);
	}
	return TRUE;
}

LBAUNITS	StorageDevice_WriteAbs(STOR_DEVID diskid, void *buffer, UINT64 position, LBAUNITS size) {
	STOR_DEV *xsd = &Storage_Devices[diskid - 1];
	if (STORDEV_VERIFYID(diskid) && xsd->Flags & DISK_FLAG_INSERTED) {
		UINT32 bpu = xsd->BytesPerUnit;
		UINT64 npos = (position/bpu);
		UINT32 nsize = (size+bpu-1)/bpu;
		return xsd->Write(xsd->HardwareId,buffer,npos,nsize);
	}
	return TRUE;
}

BOOL	StorageDevice_Sleep(STOR_DEVID diskid) {
	STOR_DEV *xsd = &Storage_Devices[diskid - 1];
	if (STORDEV_VERIFYID(diskid) && xsd->Flags & DISK_FLAG_INSERTED) {
		Storage_Devices[diskid].Sleep(xsd->HardwareId);
	}
	return TRUE;
}

BOOL	StorageDevice_Wakeup(STOR_DEVID diskid) {
	STOR_DEV *xsd = &Storage_Devices[diskid - 1];
	if (STORDEV_VERIFYID(diskid) && xsd->Flags & DISK_FLAG_INSERTED) {
		Storage_Devices[diskid].Wake(xsd->HardwareId);
	}
	return TRUE;
}


BOOL	StorageDevice_Eject(STOR_DEVID diskid) {
	STOR_DEV *xsd = &Storage_Devices[diskid - 1];
	if (STORDEV_VERIFYID(diskid) && xsd->Flags & DISK_FLAG_INSERTED) {
		Storage_Devices[diskid].Eject(xsd->HardwareId);
	}
	return TRUE;
}
