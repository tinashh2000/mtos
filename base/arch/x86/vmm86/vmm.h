#pragma once

#define _MTOX_PSE32 1

typedef struct {
	MWORD	PagesSize;
    MEMPTR  PTAddress;
	MWORD	NumL4PerPage;
	MWORD	NumL3PerPage;
	MWORD	NumL2PerPage;
	MWORD	NumL1PerPage;
	MWORD	NumL4;
	MWORD	NumL3;
	MWORD	NumL2;
	MWORD	NumL1;
	MWORD	L4Addr;
	MWORD	L3Addr;
	MWORD	L2Addr;
	MWORD	L1Addr;
} PAGE_HEADERS;

EXPORTSTART
	BOOL    InitVMM(void);
	MEMPTR  vmmAllocatePageTables(void);
	BOOL	InitGlobalPages(void);
	BOOL InitPaging(void);
	BOOL vmmInitProcess_PageTables(TH_PROCESS p);
	MEMPTR	xmmAllocateMemory(TH_PROCESS p, MWORD size,MWORD flags);
	MEMPTR	vmmAllocateMemoryForThread(TH_THREAD th,MWORD size);
	MEMPTR	vmmAllocateMemoryForProcess(TH_PROCESS p, MWORD size);
    BOOL    vmmFreeMemoryForProcess(TH_PROCESS p,MEMPTR mem);
	MEMPTR	vmmReserveAddressSpace(TH_PROCESS p, MWORD commitSize, MWORD reserveSize, MWORD flags);
	MEMPTR	vmmFindAddressSpace(TH_PROCESS p,MWORD size, MWORD flags);
EXPORTEND

extern PAGE_HEADERS vmPH;
extern MEMPTR  vmmGlobalPages;
extern UINT64	KernelMaxAddress;