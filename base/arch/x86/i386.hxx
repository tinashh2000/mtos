#include "i386.h"

union _CPUsInfo {
    AMDCPU  AMDInfo;
    IntelCPU    IntelInfo;
} CPUsInfo;

VOIDPROC	InitOS_ProcX;

//AMDCPU *amd; // =  (AMDCPU*) &CPUsInfo;


//TH_THREAD LastFPUThread[MAX_CPUS];

//DWORD   GlobalPages[1024 + 8]; //1024 dwords = 4096 bytes,
                                //8 dwords to accomodate PAE 4 (64-bit) PDPTEs

//Architectural reserved addresses. {Start Address}, {End Address}
const UINT64  preReservedAddress[] = {0,0x100000,0,0};

//#include "vmm/vmm.hxx"
//#include "apic/apic.hxx"

