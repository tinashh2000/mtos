#pragma once
#pragma pack(1)

#ifdef _MTOS_SMALL	//Small systems

typedef UINT8	FS_VOLID;
typedef UINT8	FS_ID;
typedef UINT32	FS_FILESIZE;
typedef UINT32	FS_CLUSTER;
typedef UINT32	FS_LBAUNIT;
typedef UINT32	FS_CRC;
#define MAX_FILELENGTH 64

#else

typedef UINT32	FS_VOLID;
typedef UINT32	FS_ID;
typedef UINT64	FS_FILESIZE;
typedef UINT64	FS_CLUSTER;
typedef UINT64	FS_LBAUNIT;
typedef MWORD	FS_CRC;
typedef MWORD *	FILE_CONTEXT;



#define MAX_FILELENGTH 256

#endif

typedef struct {

	FS_CLUSTER	FoundCluster;
	FS_FILESIZE	FileSize;
	WORD32		FileAttributes;
	MWORD		FoundFlags;
	DATETIME_S	CreationDate;
	DATETIME_S	LastAccessDate;
	DATETIME_S	LastModifyDate;

	WCHAR	*CurrentPath;
	WCHAR	*FileName;

	FS_VOLID	VolId;
	MWORD		Flags;
	char	FSBuffer[64];

} FS_FINDFILECONTEXT;

typedef MWORD *	FILE_CONTEXT;

#define _FS_UNICODE

#define FS_FILE_TYPE_DIR	1
#define FS_FILE_TYPE_FILE	2

#ifdef _FS_UNICODE

typedef WCHAR*	FS_STR;
typedef WCHAR*	FS_PATH;
typedef WCHAR	FS_PATHCHAR;
typedef WCHAR	FS_CHAR;
#define FS_CHARSIZE	sizeof(WCHAR)
#define FS_CHARSZ(val) (val*sizeof(WCHAR))

#define FS_STRCAST(str) (WCHAR*)L##str
#define FS_CHARCAST(ch) (WCHAR) L##ch

#else

typedef CHAR*	FS_STR;
typedef CHAR*	FS_PATH;
typedef CHAR	FS_PATHCHAR;
typedef CHAR	FS_CHAR;
#define FS_CHARSIZE	sizeof(CHAR)
#define FS_CHARSZ(val) (val*sizeof(CHAR))

#define FS_STRCAST(str) (CHAR*) str
#define FS_CHARCAST(ch) (CHAR) ch

#endif

enum FILE_SYSTEM_ERRORS {
	FS_INVALIDHANDLE   = 1,
	FS_FILENOTFOUND,
	FS_ACCESSDENIED,
	FS_TOOMANYFILES,
	FS_INVALIDFUNC
};

//Flags used to open a file
#define FS_FILE_OPEN_READ		1
#define FS_FILE_OPEN_WRITE		2
#define FS_FILE_OPEN_RANDOM		(FS_FILE_OPEN_READ | FS_FILE_OPEN_WRITE)
#define FS_FILE_OPEN_APPEND		4
#define FS_FILE_OPEN_ERASE		8


//Flags for an opened file

#define	FS_OPENFILE_FLAG_READ		1
#define FS_OPENFILE_FLAG_WRITE		2
#define FS_OPENFILE_FLAG_EOF		4

//Flags for a filesystem
#define FS_FS_LOCKED    1
#define FS_FS_READONLY	2
#define FS_FS_REMOVABLE	4

#define FS_ATTR_RD		1
#define FS_ATTR_WR		2
#define FS_ATTR_EXE		4
#define FS_ATTR_SYS		8
#define FS_ATTR_HDN		16
#define FS_ATTR_DIR		32
#define FS_ATTR_DIRTY	128

EXPORTSTART

	BOOL FS_InitFindFileContext(FS_FINDFILECONTEXT* fcxt, FS_VOLID VolId, FS_PATH path);
	BOOL FS_FindFile(FS_FINDFILECONTEXT *fcxt, FS_PATH src);
	BOOL FS_VolumeExists(FS_VOLID VolId);

	void* FS_Read(FS_VOLID VolId,FS_LBAUNIT LBAUnit,LBAUNITS LBAUnits, void *destBuffer);
	void* FS_Write(FS_VOLID VolId,FS_LBAUNIT LBAUnit,LBAUNITS LBAUnits, void *srcBuffer);
	
	FS_FILESIZE	FS_GetFileSize(FILE_CONTEXT file);
	FS_FILESIZE	FS_GetFilePos(FILE_CONTEXT file);

	FS_FILESIZE	FS_SetContextFileSize(FILE_CONTEXT file, FS_FILESIZE size);
	FS_FILESIZE	FS_SetContextFilePos(FILE_CONTEXT file, FS_FILESIZE pos);
	
	FILE_CONTEXT	FS_OpenFile(FS_FINDFILECONTEXT *pfcxt, FS_PATH path, MWORD flags);

	
	MWORD 	FS_DeleteFile(char *filename);
	FS_FILESIZE	FS_GetFilePosition(FILE_CONTEXT file, MWORD origin);
	FS_VOLID	FS_GetCurrentVolume(void);
	UINT32	FS_VolGetBytesPerUnit(FS_VOLID VolId) ;
	void FS_SetCurrentVolume(void);
	
	BOOL	FS_IsUnicode(void);
	MWORD	FS_GetLastError(void);
	MWORD	FS_ReadFile(FILE_CONTEXT file, void *buffer, MWORD numBytes);
	MWORD	FS_WriteFile(FILE_CONTEXT file, void *buffer, MWORD numBytes);
	BOOL	FS_CloseFile(FILE_CONTEXT fc);
EXPORTEND
