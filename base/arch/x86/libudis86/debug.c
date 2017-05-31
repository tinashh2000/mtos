#define __UD_STANDALONE__
#define _MTOX_ARCH
#include <mtox.h>

#include "udint.h"
#include "extern.h"
#include "decode.h"
#include "itab.h"
#include "syn.h"

#include "udis.cxx"

int DebugArchUnassembleX(MEMPTR addr,BOOL bPrint) {

 ud_t ud_obj;

    ud_init(&ud_obj);
    ud_set_input_buffer(&ud_obj,(const uint8_t*) addr,100000);
    ud_set_mode(&ud_obj,32);
    ud_set_syntax(&ud_obj,UD_SYN_INTEL);
    ud_set_pc(&ud_obj,(uint64_t) addr);

    UINT32 size = ud_disassemble(&ud_obj);
	if (bPrint) {
		const char *instrDis = ud_insn_asm(&ud_obj);
		UINT16	instrLen = strlen(instrDis);
		UINT16	instrPad = instrLen > 24 ? 0 : (24 - instrLen);

		printf("%08x ",((UINT32)(ud_insn_off(&ud_obj) & 0xFFFFFFFF)));
		printf(instrDis);

		for (int cc= 0;cc<instrPad;cc++)
			printf(" ");

		printf("\t;");
		for (int cc=0;cc<size;cc++)
			printf("%02x", ((char*) addr)[cc] & 0xff );
//		printf("\r\n");
	}
	return size;
}

int DebugArchUnassemble(MEMPTR addr) {
	return DebugArchUnassembleX(addr,1);
}

int DebugArchGetInstrLength(MEMPTR addr) {
	return DebugArchUnassembleX(addr,0);
}

BOOL	DebugArchStepInto(DEBUGCONTEXT *dc) {
	dc->dxFlags |= X86_TF;
	return TRUE;
}

BOOL	DebugArchStepOver(DEBUGCONTEXT *dc) {
	unsigned char *instr = (unsigned char*) dc->dxIP;
	
	if (instr[0] == 0xe8 || instr[0] == 0xff || instr[0] == 0x9a) {
		dc->dxFlags &= ~X86_TF;	//Disable single step
		MEMPTR bpAddr = (MEMPTR) (dc->dxIP + DebugArchGetInstrLength((MEMPTR) dc->dxIP));
		MWORD xdr0,xdr7;
		__asm {
			mov eax,bpAddr
			mov dr0,eax
			
			mov eax,2
			mov dr7,eax
			
			mov eax,dr0
			mov dword ptr xdr0,eax
			
			mov eax,dr7
			mov dword ptr xdr7,eax
		}
//		printf("DebugRegs: dr0: %08x,dr7: %08x",xdr0,xdr7);
		
	}
	else {
//		printf("NoCall: %02x",instr[0] & 0xff);
		dc->dxFlags |= X86_TF;
	}
	return TRUE;
}


BOOL	DebugArchSkip(DEBUGCONTEXT *dc) {
	dc->dxIP = (dc->dxIP + DebugArchGetInstrLength((MEMPTR)dc->dxIP));
	dc->dxFlags |= X86_TF;
	return FALSE;
}


BOOL	DebugArchRun(DEBUGCONTEXT *dc) {

	dc->dxFlags &= ~X86_TF;
	
	return TRUE;
}

BOOL	DebugArchPrintRegs(DEBUGCONTEXT *dc) {
	printf("\r\neax:%08x ebx:%08x ecx:%08x edx:%08x\r\n", dc->dxAX, dc->dxBX,dc->dxCX,dc->dxDX);
	printf("esi:%08x edi:%08x esp:%08x ebp:%08x\r\n", dc->dxSI, dc->dxDI,dc->dxSP,dc->dxBP);
	printf("cs :%08x ds: %08x es :%08x ss :%08x\r\n", dc->dxCS, dc->dxDS,dc->dxES,dc->dxSS);
	printf("cr0 :%08x  cr2 :%08x cr3 :%08x cr4 :%08x \r\n", dc->dxCR0, dc->dxCR2, dc->dxCR3, dc->dxCR4);
	printf(":::%x,%x\r\n", dc->dxIP, (dc->dxIP + DebugArchGetInstrLength((MEMPTR)dc->dxIP)));
	DebugArchUnassemble((MEMPTR)dc->dxIP);
	return TRUE;
}

void	DebugChangeRegister(char *regname, MWORD value,DEBUGCONTEXT *dc) {
	
}