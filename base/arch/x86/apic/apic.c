#define _MTOX_THREADS
#include <mtox.h>
#include "apic.hxx"

UINT64	ReadMSR(MWORD reg) {
	X86REGS xr;
	xr.rCX = reg;
    xRDMSR(&xr);
	return (xr.rAX & 0xFFFFFFFF) | ((UINT64) (xr.rDX & 0xFFFFFFFF) << 32);
}

void    WriteMSR(MWORD reg, UINT64 val) {
	X86REGS xr;
	xr.rAX = val & 0xFFFFFFFF;
	xr.rDX = (val >> 32) & 0xFFFFFFFF;
	xr.rCX = reg;
	xWRMSR(&xr);
}

UINT64  ApicReadMSR() {
	return ReadMSR(0x1B);
}

void ApicWriteMSR(UINT64 val) {
	WriteMSR(0x1B, val);
}

MWORD ApicReadRegister(MWORD addr) {
	return *((MWORD *)(APIC_BASE[GetCurrentEXU()] + addr));
}

void ApicWriteRegister(MWORD addr, MWORD value) {
	*((MWORD *)(APIC_BASE[GetCurrentEXU()] + addr)) = value;
}

MWORD   ApicGetBase() {
	return APIC_BASE[GetCurrentEXU()];
}

void ApicEOI() {
    *((MWORD *)(APIC_BASE[GetCurrentEXU()] + APIC_EOI)) = 0;
}

MWORD   ApicGetID() {
    return ( ApicReadRegister(APIC_ID) >> 24 ) & 0xFF;
} 

BOOL	IsAPICPreset() {
	X86REGS xr;
	xr.rAX = 1;  
	xr.rCX = 0;
	xCPUID(&xr);
	return (xr.rDX & CPUF_APIC)?TRUE:FALSE;
} 

BOOL    ApicEnable(BOOL flag) {  
	MWORD val = ApicReadRegister(APIC_SPURIOUS_INTR_VECTOR);

	if (flag)
		val |= APIC_ENABLE;
	else 
		val = val & ~APIC_ENABLE;

	ApicWriteRegister(APIC_SPURIOUS_INTR_VECTOR,val);
	return val & APIC_ENABLE; 
}