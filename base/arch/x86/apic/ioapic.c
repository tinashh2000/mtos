#include <mtox.h>
#include "ioapic.hxx"
 
void IoApicWrite(UINT32* IoApicBase, UINT32 offset, UINT32 val)
 {
	IoApicBase[0] = offset;
    IoApicBase[4] = val;    //4*4=0x10
 }
 
 UINT32 IoApicRead(UINT32* IoApicBase, UINT32 offset)
 {
	IoApicBase[0] = offset;
    return IoApicBase[4];
 }
 
UINT32	IoApicGetId(IOAPIC *IoApic) {
	return IoApicRead(IoApic->IoApicBase,0);
}

UINT32	IoApicGetVersion(IOAPIC *IoApic) {
	return IoApicRead(IoApic->IoApicBase,1);
}

UINT32	IoApicGetArb(IOAPIC *IoApic) {
	return IoApicRead(IoApic->IoApicBase,2);
}

/*Reads an IoApicRedir entry. Offset from 0 where 0 is first entry, 1 is second entry*/

UINT64	IoApicReadRedir(IOAPIC *IoApic, UINT32 offset) {
    UINT64  res = IoApicRead(IoApic->IoApicBase,IOAPIC_REDTBL + (offset * 2));
    res = res | ((UINT64)IoApicRead(IoApic->IoApicBase,IOAPIC_REDTBL + (offset * 2) + 1)) << 32;
	return res;
}

void	IoApicWriteRedir(IOAPIC *IoApic, UINT32 offset,UINT64 val) {
	IoApicWrite(IoApic->IoApicBase,IOAPIC_REDTBL + (offset*2) + 1,(val >> 32) & 0xFFFFFFFF);
	IoApicWrite(IoApic->IoApicBase,IOAPIC_REDTBL + (offset*2),val & 0xFFFFFFFF);
}

void	IoApicWriteRedirEntry(IOAPIC *IoApic, UINT32 offset, UINT32 IntVector, UINT32 DeliveryMode, UINT32 Flags, UINT32 DestField ) {
        IoApicWriteRedir(IoApic, offset, ((UINT64)(DestField & 0xFF) << 56) | (UINT64)(IntVector & 0xff) | ((DeliveryMode & 7) << 8) | (Flags &  IOAPIC_FLAG_MASK));
}

UINT64	IoApicReadRedirEntry(IOAPIC *IoApic, UINT32 offset) {
    return IoApicReadRedir(IoApic,offset);
}

void	IoApicInit() {
	memset(&ioapic,0,sizeof(IOAPIC));
    ioapic.IoApicBase = (UINT32*)0xFEC00000;
    bIoApicInit = TRUE;	
}

void	ApicSetLegacyInterruptVector(UINT32 vector,INTHANDLER handler) {
//    DisableInterrupts();
	SetInterruptVector(APIC_IRQBASE + vector,handler);
    IoApicWriteRedirEntry( &ioapic, vector, vector + APIC_IRQBASE, IOAPIC_DELIVERY_FIXED,  IOAPIC_FLAG_HIGHACTIVE, ApicGetID() );
//    EnableInterrupts();
}

void	ApicSetInterruptVector(UINT32 vector,INTHANDLER handler) {
//    DisableInterrupts();
	SetInterruptVector(APIC_IRQBASE + vector,handler);
    IoApicWriteRedirEntry( &ioapic, vector, vector + APIC_IRQBASE, IOAPIC_DELIVERY_FIXED, IOAPIC_FLAG_LEVELSENSE | IOAPIC_FLAG_HIGHACTIVE, ApicGetID() );
//    EnableInterrupts();
}

