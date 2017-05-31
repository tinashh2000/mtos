#define DISK_RESET             0       ;Reset the disk system
#define DISK_READ              1
#define DISK_WRITE             2
#define DISK_WRITEVERIFY       3
#define DISK_VERIFY            4

#define DISK_GETDISKPARAM      10
#define DISK_CHECKREMOVED      11

#define DISK_READERROR         1
#define DISK_WRITERROR         2
#define DISK_ACCESSERROR       3
#define DISK_SEEKERROR         4
#define DISK_INVALIDSECTOR     5
#define DISK_BADADDRESS        6
#define DISK_WRITEPROTECTED    10
#define DISK_RESETFAIL         11
#define DISK_MEDIACHANGE       12
#define DISK_FAIL              13
#define DISK_DMAFAIL           14
#define DISK_INVALIDMEDIA      15
#define DISK_NOTREADY          16
#define DISK_LOCKED            10
#define DISK_INVALIDFUNC       11


#define DISK_REMOVABLE		1
#define	DISK_READONLY		2
#define	DISK_FLAG_INSERTED	4

//#define DISK_

#define SIZE_BUSNAME		4
#define SIZE_DEVADDRESS		16
#define	SIZE_HARDWAREINFO	16

typedef UINT32 STOR_DEVID;
//typedef	MWORD LBAUNITS;	//Maximum size per transfer
typedef UINT32 LBAUNIT;
typedef UINT32 LBAUNITS;	//measure used to count sectors, or units per transfer

enum {
	CD_ROM	=	1,
	CD_RW,
	DVD_COMBO,
	HARDDISK
};

typedef LBAUNITS(*STOR_DEV_READ_PROC)(STOR_DEVID diskid,void *buffer,LBAUNIT LBAUnit,LBAUNITS numUnits);
typedef LBAUNITS(*STOR_DEV_WRITE_PROC)(STOR_DEVID diskid,void *buffer,LBAUNIT LBAUnit,LBAUNITS numUnits);
typedef BOOL(*STOR_DEV_EJECT_PROC)(STOR_DEVID diskid);
typedef BOOL(*STOR_DEV_SLEEP_PROC)(STOR_DEVID diskid);
typedef BOOL(*STOR_DEV_WAKE_PROC)(STOR_DEVID diskid);
