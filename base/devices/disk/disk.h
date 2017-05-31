#pragma once

#include <mtox.h>
#pragma pack(1)

#define MAX_DRIVES	256

#define _STORAGE_DEVICE_PTR struct _STORAGE_DEVICE*

typedef struct {

	UINT32		BytesPerUnit;	//Typically bytes per sector, it is 512 for IDE drives. For memory mapped devices, it can be 1.
	STOR_DEVID	HardwareId;		//ID to identify the disk to its hardware. Eg. IDE0 = 0, IDE3 =3
	UINT64		Size;

	STOR_DEV_READ_PROC	Read;
	STOR_DEV_WRITE_PROC	Write;
	STOR_DEV_EJECT_PROC	Eject;
	STOR_DEV_WAKE_PROC	Wake;
	STOR_DEV_SLEEP_PROC	Sleep;

} STOR_DEV_DESC;

typedef struct _STORAGE_DEVICE {

	UINT32		BytesPerUnit;	//Typically bytes per sector, it is 512 for IDE drives. For memory mapped devices, it can be 1.
	STOR_DEVID	HardwareId;		//ID to identify the disk to its hardware. Eg. IDE0 = 0, IDE3 =3
	UINT64		Size;

	STOR_DEV_READ_PROC	Read;
	STOR_DEV_WRITE_PROC	Write;
	STOR_DEV_EJECT_PROC	Eject;
	STOR_DEV_WAKE_PROC	Wake;
	STOR_DEV_SLEEP_PROC	Sleep;

	UINT32				OS_Id;	//OS id
	UINT32				Flags;
	char				DeviceBus[SIZE_BUSNAME];
	char				DeviceAddress[SIZE_DEVADDRESS];
	UINT8				HardwareInfo[SIZE_HARDWAREINFO];
} 	STOR_DEV;

EXPORTSTART

	BOOL	StorageDevice_Inserted(STOR_DEV_DESC *sd);
	UINT32	StorageDevice_GetBytesPerUnit(STOR_DEVID diskid);
	BOOL	StorageDevice_Removed(STOR_DEVID diskid);
	LBAUNITS	StorageDevice_Read(STOR_DEVID diskid,void *buffer,LBAUNIT LBAUnit,LBAUNITS numUnits);
	LBAUNITS	StorageDevice_ReadAbs(STOR_DEVID diskid,void *buffer,UINT64 position,LBAUNITS size) ;
	LBAUNITS	StorageDevice_Write(STOR_DEVID diskid, void *buffer, UINT64 LBAUnit, LBAUNITS numUnits);
	LBAUNITS	StorageDevice_WriteAbs(STOR_DEVID diskid, void *buffer, UINT64 position, LBAUNITS size);
	BOOL	StorageDevice_Sleep(STOR_DEVID diskid);
	BOOL	StorageDevice_Wakeup(STOR_DEVID diskid);
	BOOL	StorageDevice_Eject(STOR_DEVID diskid);
	
EXPORTEND

//#pragma options align=reset
