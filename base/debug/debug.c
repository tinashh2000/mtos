#define _MTOX_ARCH
#define _MTOX_THREADS

#include <mtox.h>
#include "debug.h"

TH_PROCESS	curProcess;
TH_THREAD	curThread;
MWORD		dbgInstr;

BYTE		DebugDumpSize	= 4;
MWORD		DebugDumpBytes	= 32;
MEMPTR		DebugDumpAddress	=	0;
MEMPTR		DebugUnassembleAddress = 0x100000;
MWORD		DebugUnassembleBytes = 10;

IMPORT UINT32 winColActive;
IMPORT UINT32 winColInactive;

TH_THREAD DebugThread = 0;

void	SetDebugThreadX(TH_THREAD th) {
	DebugThread = th;
}

TH_THREAD GetDebugThreadX() {
	return DebugThread;
}

void	DebugSetCurrentProcess(TH_PROCESS p) {
	if (VerifyProcess(p))
		curProcess = p;
}

void DebugSetCurrentThread(TH_THREAD th) {
	if (VerifyThread(th)) 
		curThread = th;
}

void DebugStepInto() {
	dbgInstr = DBG_STEPINTO;
}

void DebugStepOver() {
	dbgInstr = DBG_STEPOVER;
}

void DebugRun() {
	dbgInstr = DBG_RUN;
}

void DebugSkip() {
	dbgInstr = DBG_SKIP;
}

void byteDumps(char*dumpad, int nbytes) {
	for (int c = 0; c < nbytes; c++) {
		printf(" %02x", dumpad[c] & 0xff);
	}
}

void	DebugDump() {
	int c;
	char *dumpptr = (char*)DebugDumpAddress;
	char *dumplinestart = dumpptr;
	UINT32	value64;
	UINT32	nItems=0;
	UINT32 	nItemsPerCol = (DebugDumpSize < 16) ? 32 / DebugDumpSize : 20;
	printf("\r\nDump Address: 0x%08x\r\n",dumpptr);
	for (c=0;c<DebugDumpBytes;c++) {
		if (DebugDumpSize == 1) {
			printf("%02x ",*dumpptr & 0xff);
			dumpptr++;
		}
		else if (DebugDumpSize == 2) {
			printf("%04x ",GetWord16((void**) &dumpptr) & 0xffff);
		}
		else if (DebugDumpSize == 4) {
			printf("%08x ",GetWord32((void**) &dumpptr) & 0xffffffff);
		}
		else if (DebugDumpSize == 8) {
			value64 = GetWord64((void**) &dumpptr);
			printf("%016x ",value64);
		}
		else {
			printf("%c", *dumpptr > 31 && *dumpptr < 128 ? *dumpptr:'.');
			dumpptr++;
		}

		if (nItems++ >= nItemsPerCol) {
			if (DebugDumpSize == 255)
				byteDumps(dumplinestart,nItems);

			dumplinestart = dumpptr;
			nItems = 0;
			printf("\r\n");
		}

	}

	if (DebugDumpSize == 255) {
		while (nItems++ <= nItemsPerCol)
			printf(" ");
		byteDumps(dumplinestart, nItems-1);
	}

	DebugDumpAddress = (MEMPTR) dumpptr;
}

char *FindNextChar(char *st) {
	char *stx = st;
	while (*stx != 0) {
		if (*stx > 32)
			return stx;

		stx++;
	}
	return stx;
}

void DebugUnassemble() {
	UINT32 c, size;

	for (c = 0;c<DebugUnassembleBytes;c++) {
		size = DebugArchUnassemble((void*)DebugUnassembleAddress);
		DebugUnassembleAddress += size;
		printf("\r\n");
	}

}
char *membuffer=0;

void	DebugExecuteString(char *st) {
	char *ln = st;

	ln = FindNextChar(ln);

	if (memcmp("alloc",ln,5) == 0) {
		membuffer = malloc(0x123456);
		OXListMemory();
	}
	else if (memcmp("free",ln,5) == 0) {
		free(membuffer);
		OXListMemory();
	}
	else if (memcmp("list",ln,4) == 0) {
		ln += 4;
		printf("<%s>",ln);
		if (memcmp("-threads",ln,8) == 0)
			OXListThreads();
		else if (memcmp("-processes",ln,10) == 0)
			OXListProcesses();
		else if (memcmp("-memx",ln,5) == 0)
			OXListMemory();
		else if (memcmp("-mem",ln,4) == 0)
			OXListMemory();
		else if (memcmp("-usedmem",ln,8) == 0)
			OXListUsedMemory();
		else if (memcmp("-unusedmem",ln,10) == 0)
			OXListUnusedMemory();

		return;		
	}
	else if (memcmp("kill",ln,3)) {
		
	}
	
	switch(*ln) {

		case 'u':

			ln = FindNextChar(ln + 1);
			if (*ln == 0) {
				DebugUnassemble();
				return;
			}
			DebugUnassembleAddress = (void*) GetHex32((char**) &ln);
			ln = FindNextChar(ln);
			if (*ln == 0) {
				DebugUnassemble();
				return;
			}
			DebugUnassembleBytes = GetHex32((char**) &ln);
			DebugUnassemble();
			break;

		case 'b':
			ln++;
			
			MWORD *whichColor;
			char cDbl = 0;
			if (*ln == 'a')
				whichColor = &winColActive;
			else if (*ln == 'i')
				whichColor = &winColInactive;
			else if (*ln == 'x') 
				cDbl = 1;
			else
				return;
			
			ln = FindNextChar(ln + 1);
			if (*ln == 0) {
				return;
			}

			MWORD gCol = (void*) GetHex32((char**) &ln);
			if (cDbl) {
				winColActive = gCol;
				winColInactive = gCol;
			}
			else
				*whichColor = gCol;
			break;
		case 'd':
			ln++;
			switch (*ln) {

				case 'a':
					DebugDumpSize = 255;
					ln++;
					break;					

				case 'b':
					DebugDumpSize = 1;
					ln++;
					break;

				case 'w':
					DebugDumpSize = 2;
					ln++;
					break;

				case 'd':
					DebugDumpSize = 4;
					ln++;
					break;

				case 'q':
					DebugDumpSize = 8;
					ln++;
					break;

			}

			ln = FindNextChar(ln);
			if (*ln == 0) {
				DebugDump();
				return;
			}
			DebugDumpAddress =(void*) GetHex32((char**) &ln);
			ln = FindNextChar(ln);
			if (*ln == 0) {
				DebugDump();
				return;
			}
			DebugDumpBytes = GetHex32((char**) &ln);
			DebugDump();
			break;
		case 'r':  {
			ln++;
			ln = FindNextChar(ln);
			if (*ln==0)
				dbgInstr = DBG_PRINTREGS;
			else
				printf("%x", *ln);
		}
			break;
		case 'c':
			dbgInstr = DBG_RUN;
			break;	}
}

void	DebugProcess(MEMPTR addr,DEBUGCONTEXT *dc) {
	MEMPTR	instrAddr = addr;

	SetDebugThreadX(GetCurrentThread());
	printf("\r\n");
	instrAddr = ((CHARPTR) instrAddr) + DebugArchUnassemble(instrAddr);
	DebugUnassembleAddress = instrAddr;
	dbgInstr = 0;
	while(1) {
		if (dbgInstr != 0) {
			UINT32 di = dbgInstr;
			dbgInstr = 0;
			switch (di) {
				case DBG_STEPINTO:
					if (DebugArchStepInto(dc))
						return;
					break;
				case DBG_STEPOVER:
					if (DebugArchStepOver(dc))
						return;
					break;
				case DBG_PRINTREGS:
					DebugArchPrintRegs(dc); 
					break;
				case DBG_RUN:
					if (DebugArchRun(dc))
						return;
					break;
				case DBG_SKIP:
					if (DebugArchSkip(dc))
						return;
					DebugArchPrintRegs(dc);
					break;
			};
		}
		_idle();
		Delay(10);
    }
	return;
}