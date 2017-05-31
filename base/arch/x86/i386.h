#pragma once

#define _MTOX_MMMGR

#define		MMPTR	UINT64
#define		MMSIZE	UINT64

#include <mtox.h>
#define InPortB     inportb
#define OutPortB    outportb
#define InPortW     inportw
#define OutPortW    outportw
#define InPortD     inportd
#define OutPortD    outportd

#define		X86_CF		0x0001
#define		X86_PF		0x0004
#define		X86_AF		0x0010
#define		X86_ZF		0x0040
#define		X86_SF		0x0080
#define		X86_TF		0x0100
#define		X86_IF		0x0200
#define		X86_DF		0x0400
#define		X86_OF		0x0800

#define X86SSE	1
#define _MTOX_PSE32 1
typedef struct {

    MWORD dxAX;
    MWORD dxCX;
    MWORD dxDX;
    MWORD dxBX;
    MWORD dxSI;
    MWORD dxDI;
    MWORD dxSP;
    MWORD dxBP;
    MWORD dxCS;
    MWORD dxDS;
    MWORD dxSS;
    MWORD dxES;
    MWORD dxFS;
    MWORD dxGS;
    MWORD dxFlags  ;
    MWORD dxIP;
    MWORD dxCR0;
    MWORD dxCR1;
    MWORD dxCR2;
    MWORD dxCR3;
    MWORD dxCR4;

    MWORD dxXMM0;
    MWORD dxXMM1;
    MWORD dxXMM2;
    MWORD dxXMM3;
    MWORD dxXMM4;
    MWORD dxXMM5;
    MWORD dxXMM6;
    MWORD dxXMM7;

} DEBUGCONTEXT;

typedef struct {
    MWORD   rAX;
    MWORD   rBX;
    MWORD   rCX;
    MWORD   rDX;
    MWORD   rSI;
    MWORD   rDI;
    MWORD   rSP;
    MWORD   rBP;
} X86REGS;

typedef struct {
	MWORD	rAX;
	MWORD	rCX;
	MWORD	rDX;
	MWORD	rBX;
	MWORD	rSI;
	MWORD	rDI;
	MWORD	rSP;
	MWORD	rBP;
	MWORD	rCS;
	MWORD	rDS;
	MWORD	rSS;
	MWORD	rES;
	MWORD	rFS;
	MWORD	rGS;
	MWORD	rFlags;
	MWORD	rIP;

#ifdef BITS64
	MWORD	rR8;
	MWORD	rR9;
	MWORD	rR10;
	MWORD	rR11;
	MWORD	rR12;
	MWORD	rR13;
	MWORD	rR14;
	MWORD	rR15;
#endif

	MWORD	rCR0;
	MWORD	rCR1;
	MWORD	rCR2;
	MWORD	rCR3;
    MWORD   rCR4;
    MWORD   bNew;

#ifdef X86FPU
	BYTE FPUState[108]; // DUP(?)
#elif defined(X86SSE)
	BYTE FPUState[512];
#elif defined(X86SSE5)
	BYTE FPUState[1024];
#endif

	MEMPTR	stack;
} EXUCONTEXT;

typedef struct {
    MEMPTR  PTBase;
	MWORD	VMMLock;
} VMMDATA;

EXPORTSTART

	void    APEntryPoint(void);
	BOOL    GetEXUInfo(void);
	BOOL	InitProcessContext(TH_PROCESS p);
	BOOL	InitThreadContext(TH_THREAD t, MWORD ePoint, MWORD dStackSize, MWORD dMAllocSize, MWORD tWord1, MWORD tWord2);
	MWORD   GetEXUVendor(void);
    void    GetEXUVendorString(CHARPTR str);



	BYTE __STDCALL inportb(MWORD portNum);
	BYTE __STDCALL outportb(MWORD portNum, MWORD data);

	WORD __STDCALL inportw(MWORD portNum);
	WORD __STDCALL outportw(MWORD portNum, MWORD data);

	DWORD __STDCALL inportd(MWORD portNum);
	DWORD __STDCALL outportd(MWORD portNum, MWORD data);

	DWORD __STDCALL inportstringb(MWORD portNum, void* data, MWORD size);
	DWORD __STDCALL inportstringw(MWORD portNum, void* data, MWORD size);
	DWORD __STDCALL inportstringd(MWORD portNum, void* data, MWORD size);

	DWORD __STDCALL outportstringb(MWORD portNum, void* data, MWORD size);
	DWORD __STDCALL  outportstringw(MWORD portNum, void* data, MWORD size);
	DWORD __STDCALL outportstringd(MWORD portNum, void* data, MWORD size);

	void    __STDCALL SwitchPAE(MWORD flag);
	void    __STDCALL SwitchPSE(MWORD flag);
	void    __STDCALL SetPagesBase(MEMPTR pb);
	void    __STDCALL SwitchGlobal(MWORD flag);
	void    __STDCALL SwitchPaging(MWORD flag);

	void    __STDCALL Enable8259(void);
	void    __STDCALL Disable8259(void);

	void    __STDCALL Init386(void);
	void    __STDCALL InitAP(void);
	void    __STDCALL InitContext86(EXUCONTEXT*ctx, MWORD ePoint, MEMPTR stackTop, VMMDATA* vmmData, MWORD privilegeLevel);

	void    __STDCALL xCPUID(X86REGS *xr);
	UINT64  __STDCALL xRDMSR(X86REGS *xr);
	void    __STDCALL xWRMSR(X86REGS *xr);
	void __STDCALL SetInterruptVector(MWORD vector,INTHANDLER Handler);
	void __STDCALL DisableInterrupts(void);
	void __STDCALL EnableInterrupts(void);
	void __STDCALL _Scheduler(void);
	UINT32  __STDCALL GetCurrentEXUID(void);
	UINT64  __STDCALL GetFeatures(void);
	UINT64	__STDCALL GetEXUTicks(void);
	UINT64	__STDCALL GetEXUSpeed(void);

	void	ArchReboot(void);
	void	ArchInit(VOIDPROC InitOS_Proc);
	void*	ArchGetReservedMemoryAddresses(void);
	int		DebugArchUnassemble(MEMPTR addr);
	BOOL	DebugArchStepInto(DEBUGCONTEXT *dc);
	BOOL	DebugArchStepOver(DEBUGCONTEXT *dc);
	BOOL	DebugArchPrintRegs(DEBUGCONTEXT *dc);
	BOOL	DebugArchRun(DEBUGCONTEXT *dc);
	BOOL	DebugArchSkip(DEBUGCONTEXT *dc);
	
EXPORTEND

enum    CPU_VENDOR {
    INTEL_X86 = 1,
    AMD_X86,
    VIA_X86,
    GENERIC_X86
};

typedef struct {
    UINT32  LastCPUIDFunc;
    UINT32  LastCPUIDExtFunc;
    UINT32  NumLogicalCPUs;
    UINT32  ApicIDCoreIDSize;
    INT16   NumCores;
    INT16   MaxCores;
    INT16   NumThreadsPerCore;
    BOOL    bHTT;
    BOOL    bCmpLegacy;
} AMDCPU;

typedef struct {
    UINT32  LastCPUIDFunc;
    UINT32  LastCPUIDExtFunc;
    UINT32  NumLogicalCPUs;
    INT16   NumCores;
    INT16   NumThreadsPerCore;
    BOOL    bHTT;
    BOOL    bCmpLegacy;
} IntelCPU;

#ifdef BITS64
#else
#define	SPINLOOP	__asm PAUSE;
#endif

#include "initap.h"
#include "vmm86/vmm.h"
#include "cpuid.h"
#include "apic/apic.h"
