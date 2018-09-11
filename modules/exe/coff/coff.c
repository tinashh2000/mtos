/***************************************************************************************
* Copyright (C) 2018 Tinashe Mutandagayi                                               *
*                                                                                      *
* This file is part of the MT-Operating System source code. The author(s) of this file *
* is/are not liable for any damages, loss or loss of information, deaths, sicknesses   *
* or other bad things resulting from use of this file or software, either direct or    *
* indirect.                                                                            *
*                                                                                      *
* Terms and conditions for use and distribution can be found in the license file named *
* LICENSE.TXT. If you distribute this file or continue using it,                       *
* it means you understand and agree with the terms and conditions in the license file. *
* binding this file.                                                                   *
*                                                                                      *
* Happy Coding :)                                                                      *
*                                                                                      *
****************************************************************************************/

#include "../exe.h"
#include <filesys.h>

#include <mm/vmm.h>
#include <exe/coff/coff.h>
#include "coff.hxx"

int myvar = 1234;;
void PrintHex3(UINT32 val);

MWORD	COFFCreateImageThread(TH_THREAD thread, MEMPTR mAllocPTR, UINT32 mAllocSize, MWORD tWord1, MWORD tWord2);

BOOL	COFFValidateImage(MEMPTR peImage) {
	UINT16 sig = ((IMAGE_DOS_HEADER*) peImage)->e_magic;
	if (  sig == IMAGE_DOS_SIGNATURE || sig == IMAGE_DOS_SIGNATURE2) {
        if (((IMAGE_DOS_HEADER *)peImage)->e_lfarlc >= 0x40) {
            if ( *((DWORD *)((BYTEPTR)peImage + ((IMAGE_DOS_HEADER *)peImage)->e_lfanew)) == IMAGE_NT_SIGNATURE) {
				return TRUE;
			}			
		}
	}
	return FALSE;
}

UINT32	COFFGetImageSize(MEMPTR peImage) {
	if (!COFFValidateImage(peImage))
		return 1;
	
    if ( *((DWORD *)((BYTEPTR)peImage + ((IMAGE_DOS_HEADER *)peImage)->e_lfanew)) == IMAGE_NT_SIGNATURE) {
		PIMAGE_FILE_HEADER pe = (PIMAGE_FILE_HEADER)((BYTEPTR)peImage + ((IMAGE_DOS_HEADER *)peImage)->e_lfanew + 4);
		if (pe->Machine == IMAGE_FILE_MACHINE_I386) {
			PIMAGE_OPTIONAL_HEADER32 oh = (PIMAGE_OPTIONAL_HEADER32)((BYTEPTR) pe + sizeof(IMAGE_FILE_HEADER));
			return oh->SizeOfImage;
		}
	}
    return 1;
}

/*
 *	Creates a library in the context of the current process
 */

BOOL	COFFCreateModule(FILE_CONTEXT fc, MT_EXEIMAGEINFO *iinfo) {
	int bufSize = 4096;
	FS_FINDFILECONTEXT fcxt;
	TH_PROCESS  p = iinfo->p;
	FILE_CONTEXT fc;
	//	FS_PATH fileName = AllocateMemoryH(MAX_FILELENGTH);
	MEMPTR buf = iinfo->buf;
	memset(&fcxt, 0, sizeof(FS_FINDFILECONTEXT));

	int c = 0;
	uprintf("{Loading library...%s}", iinfo->fileName, iinfo->processName);
	if (memcmp(buf, peSignature, 4) != 0) return 0;

	IMAGE_FILE_HEADER *ih = BYTEPTR(buf) + 4;
	IMAGE_OPTIONAL_HEADER32 *ioh = BYTEPTR(ih) + sizeof(IMAGE_FILE_HEADER);
	IMAGE_OPTIONAL_HEADER64 *ioh6 = BYTEPTR(ih) + sizeof(IMAGE_FILE_HEADER);

	int numSections = ih->NumberOfSections;
	int sizeOfOptional = ih->SizeOfOptionalHeader;

	eprintf("{%s}", iinfo->fileName);
	fc = FsOpenFile(&fcxt, iinfo->fileName, FS_FILE_OPEN_READ);
	if (fc == 0) return 0;

	int nBytes = numSections * sizeof(IMAGE_SECTION_HEADER);
	uprintf("{2}");

	FsSetFilePosition(fc, iinfo->word1 + iinfo->word4, SEEK_SET);
	uprintf("{3}");

	int bytesRead = FsReadFile(fc, BYTEPTR(buf) + iinfo->word4, nBytes);
	if (bytesRead != nBytes) return 0;

	if (!COFFResolveDependencies(fc, iinfo, ih)) return 0;

	IMAGE_SECTION_HEADER *section = IMAGE_FIRST_SECTION(ih);
	int paddBytes;
	int sectSize;
	int remainingSections = ih->NumberOfSections;
	//	MEMPTR	sectionBuffer = AllocateMemory( remainingSections * sizeof(IMAGE_SECTION_HEADER) );
	uprintf("{4}");

	if (iinfo->imageAddr == 0) {
		uprintf("{5::%x}", VerifyProcess(p));

		if ((iinfo->imageAddr = VMMReserve(p, 0, 0, iinfo->imageSize, 0, 0)) == 0) {
			return 0;
		}

		uprintf("{6}");

		uprintf("!@#%%");
	}

	uprintf("[img:%x]", iinfo->imageAddr);

	if (COFFLoadSections(fc, iinfo, section, numSections)) {
		int numRVAs;
		IMAGE_DATA_DIRECTORY *relocPTR;
		MEMPTR prefImageBase;

		if (iinfo->word2 == 4) {	//32-Bit
			numRVAs = ioh->NumberOfRvaAndSizes;
			relocPTR = &ioh->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
			prefImageBase = ioh->ImageBase;
		}
		else if (iinfo->word2 == 8) {	//64-bit
			numRVAs = ioh6->NumberOfRvaAndSizes;
			relocPTR = &ioh6->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
			prefImageBase = ioh6->ImageBase;
		}

		if (!(ih->Characteristics & IMAGE_FILE_RELOCS_STRIPPED) && (iinfo->imageAddr != prefImageBase)) { //If we have relocs and image was not loaded at prefered address

			if (numRVAs <= IMAGE_DIRECTORY_ENTRY_BASERELOC) return 0;	//No base reloc

			if (!COFFDoRelocations(iinfo, relocPTR, prefImageBase)) {
				return 0;
			}
		}
		else if (iinfo->imageAddr != prefImageBase) {
			uprintf("Cannot load image at preferred address!! Recompile with dynamic base");
			return 0;
		}

		uprintf("{%x}", iinfo->imageAddr);
		/*		if (!COFFResolveImports(iinfo, )) {

		}
		*/
		if (!COFFProtectImage(iinfo, section, numSections))
			return 0;
	}
	else {
		return 0;
	}
	uprintf("[[Done:%x, %x]]", AllocateMemory(4096), BYTEPTR(iinfo->imageAddr) + ioh->AddressOfEntryPoint);
	while (1);
	return 0;

}
/*
 *	COFFCreateImage is supposed to create an image from file, but it dispatches a thread which runs within the context of the process being created.
 *	This makes it easy load the executable without too many context switches or memory flushes.
 *	The thread created is a kernel thread which terminates after successfully loading the COFF image
 */
 
BOOL	COFFCreateImage(FILE_CONTEXT fc, MT_EXEIMAGEINFO *iinfo) {

	int sLen = strlen(iinfo->fileName);
	int sLen2 = strlen(iinfo->processName);
	int reqSize = PAGE_ALIGN_SIZE(N_4KB + sizeof(MT_EXEIMAGEINFO) + sLen + sLen2 + iinfo->word4 + 2);	//4KBs is for the sections, iinfo.word4 is for the headers we have read.
	MEMPTR thInfo = VMMAllocateMemory(GetCurrentProcess(), reqSize, MM_FLAG_WRITEABLE | MM_FLAG_MOVABLE); // AllocateMemory(reqSize); //2 is for the null terminators
	if (thInfo) {
		int ofs = (((offsetof(COFF_BOOTSTAP_STRUCT, fileAndProcessName) + sLen + sLen2 + 2) + 7) & ~7);	//8-byte align , assuming allocated memory is already aligned

		memcpy(&I_COFF_BOOTSTRAP(thInfo)->iinfo, iinfo, sizeof(MT_EXEIMAGEINFO));
		memcpy(&I_COFF_BOOTSTRAP(thInfo)->fileAndProcessName[0], iinfo->fileName, sLen + 1);	//Copy filename
		memcpy(&I_COFF_BOOTSTRAP(thInfo)->fileAndProcessName[sLen + 1], iinfo->processName, sLen2 + 1); //copy process name
		memcpy(BYTEPTR(thInfo) + ofs, iinfo->buf, iinfo->bufSize > 4096 ? 4096 : iinfo->bufSize);	//Copy file buffer, which contains the COFF header
		MEMPTR thInfoDest = VMMReserve(iinfo->p, 0, 0, reqSize, MM_FLAG_WRITEABLE | MM_FLAG_MOVABLE, MM_IFLAG_HIGHESTADDRESS);		//Allocate a shared memory on new process
		if (thInfoDest) {

			I_COFF_BOOTSTRAP(thInfo)->iinfo.fileName = BYTEPTR(thInfoDest) + offsetof(COFF_BOOTSTAP_STRUCT, fileAndProcessName);
			I_COFF_BOOTSTRAP(thInfo)->iinfo.processName = BYTEPTR(thInfoDest) + (offsetof(COFF_BOOTSTAP_STRUCT, fileAndProcessName) + sLen + 1);
			I_COFF_BOOTSTRAP(thInfo)->fileBuf = BYTEPTR(thInfoDest) + ofs;

			VMMShareMemory(iinfo->p, thInfoDest, GetCurrentProcess(), thInfo, reqSize | VMM_SHARE_MOVE, MM_FLAG_WRITEABLE); //After moving this, we wont have access to it!

		//	CREATETHREADPARAM ctp = (CREATETHREADPARAM) { "COFFLoader", iinfo->p, COFFCreateImageThread, THREAD_PRIORITY_NORMAL, 0, 8192, TF_READY | TF_KERNELTHREAD, thInfoDest, reqSize};

			CREATETHREADPARAM ctp = (CREATETHREADPARAM) {
				.ThreadName = "COFFLoader",
					.process = iinfo->p,
					.thProc = COFFCreateImageThread,
					.cPriority = THREAD_PRIORITY_NORMAL,
					.stackReserve = 0,
					.stackAlloc = 8192,
					.flags = TF_READY | TF_KERNELTHREAD,
					.tWord1 = thInfoDest,
					.tWord2 = reqSize
			};

			TH_THREAD newThread = CreateThread(&ctp);

			if (newThread) {
				return TRUE;
			}
		}
	}
	UiPrintStr("\r\n<cofffail>");
	return FALSE;
}

BOOL	COFFLoadSections(FILE_CONTEXT fc, MT_EXEIMAGEINFO *iinfo, IMAGE_SECTION_HEADER *section, int numSections)  { //MEMPTR *imageAddr, IMAGE_SECTION_HEADER *section, int numSections
	MEMPTR imageAddr = iinfo->imageAddr;
	MEMPTR imageEnd = BYTEPTR(imageAddr) + iinfo->imageSize;
	UINT32 sectSize, paddBytes, nBytes, bytesRead, remainingSections = numSections;
	MEMPTR	sectionPTR;
	while (remainingSections > 0) {
		if (section->Characteristics & IMAGE_SCN_CNT_CODE || section->Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA || section->Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA) {

			if (section->VirtualSize >= section->SizeOfRawData) {
				sectSize = section->VirtualSize;
				paddBytes = section->VirtualSize - section->SizeOfRawData;
			}
			else {
				sectSize = section->SizeOfRawData;
				paddBytes = section->SizeOfRawData - section->VirtualSize;
			}
			if (memcmp(section->Name, ".rsrc", 5) == 0) {	//Skip for now

			}
			/*			else if (strcmp(section->Name, ".reloc")) {	//Skip for now

			}*/
			else {
				imageAddr = BYTEPTR(iinfo->imageAddr) + section->VirtualAddress;
				sectionPTR = VMMCommit(GetCurrentProcess(), imageAddr, sectSize, MM_FLAG_WRITEABLE, 0);
				if (section->SizeOfRawData > 0) {
					if (!FsSetFilePosition(fc, section->PointerToRawData, SEEK_SET)) return 0;
					nBytes = MIN(section->SizeOfRawData, section->VirtualSize);
					if ((bytesRead = FsReadFile(fc, sectionPTR, nBytes)) == 0) { uprintf("[\03308@@@@@ %x, %x\03307]", bytesRead, nBytes); return 0; };
					//					memset(BYTEPTR(sectionPTR) + (sectSize - paddBytes), 0, paddBytes);
				}
			}
		}
		remainingSections--;
		section++;
	}
}

BOOL	COFFProtectImage(MT_EXEIMAGEINFO *iinfo, IMAGE_SECTION_HEADER *section, int numSections) { //MEMPTR *imageAddr, IMAGE_SECTION_HEADER *section, int numSections
	MEMPTR imageAddr = iinfo->imageAddr;
//	MEMPTR imageEnd = BYTEPTR(imageAddr) + iinfo->imageSize;
	UINT32 sectSize, paddBytes, bytesRead, remainingSections = numSections;

//	MEMPTR	sectionPTR;
	while (remainingSections > 0) {
		if (section->Characteristics & IMAGE_SCN_CNT_CODE || section->Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA || section->Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA) {

			if (section->VirtualSize >= section->SizeOfRawData) {
				sectSize = section->VirtualSize;
				paddBytes = section->VirtualSize - section->SizeOfRawData;
			}
			else {
				sectSize = section->SizeOfRawData;
				paddBytes = section->SizeOfRawData - section->VirtualSize;
			}
			if (memcmp(section->Name, ".rsrc", 5) == 0) {	//Skip for now

			}
			else {
				UINT32 flags = 0;
				UINT32 characteristics = section->Characteristics;
				if (characteristics & IMAGE_SCN_MEM_EXECUTE | characteristics & IMAGE_SCN_CNT_CODE) flags |= MM_FLAG_EXECUTABLE;
				if (characteristics & IMAGE_SCN_MEM_NOT_CACHED == 0) flags |= MM_FLAG_CACHEABLE;
//@@				if (characteristics & IMAGE_SCN_MEM_NOT_PAGED == 0) flags |= MM_FLAG_GLOBAL;
//@@				if (characteristics & IMAGE_SCN_MEM_SHARED) flags |= MM_FLAG_GLOBAL;
				if (characteristics & IMAGE_SCN_MEM_WRITE) flags |= MM_FLAG_WRITEABLE;

				imageAddr = BYTEPTR(iinfo->imageAddr) + section->VirtualAddress;
				VMMProtect(GetCurrentProcess(), imageAddr, sectSize, flags);
			}
		}
		remainingSections--;
		section++;
	}

}

BOOL COFFDoRelocations(MT_EXEIMAGEINFO *iinfo, IMAGE_DATA_DIRECTORY *relocPTR, MEMPTR prefImageBase) {
	if (relocPTR->Size == 0 || relocPTR->VirtualAddress == 0) return TRUE;

	MEMPTR pRel = BYTEPTR(iinfo->imageAddr) + relocPTR->VirtualAddress;
	MEMPTR pRelEnd = BYTEPTR(pRel) + relocPTR->Size;

	MWORD relocDiff = BYTEPTR(iinfo->imageAddr) - BYTEPTR(prefImageBase);

	while (pRel < pRelEnd) {
		MEMPTR relVA = BYTEPTR(iinfo->imageAddr) + UINT32PTR(pRel)[0];
		UINT32 numRelocs = UINT32PTR(pRel)[1];
		if (numRelocs < 8) return 0;
		numRelocs = (numRelocs - 8) / 2;
		pRel = BYTEPTR(pRel) + 8;
		for (int c = 0; c < numRelocs && pRel < pRelEnd; c++) {
			WORD16 val = WORD16PTR(pRel)[0];

			BYTE relType = (val >> 12) & 0xf;
			MEMPTR dest = BYTEPTR(relVA) + (val & 0xfff);


			switch (relType) {

				case IMAGE_REL_BASED_HIGHLOW:
					*UINT32PTR(dest) += relocDiff;
					break;

				case IMAGE_REL_BASED_DIR64:
					*UINT64PTR(dest) += relocDiff;
					break;

				case IMAGE_REL_BASED_HIGH:
					*UINT16PTR(dest) += ((relocDiff >> 16) & 0xffff);
					break;

				case IMAGE_REL_BASED_LOW:
					*UINT16PTR(dest) += (relocDiff & 0xffff);
					break;

				case IMAGE_REL_BASED_ABSOLUTE:	//Skip
					break;

				case IMAGE_REL_BASED_HIGH3ADJ:	//Not supported
				case IMAGE_REL_BASED_HIGHADJ:
				default:
					uprintf("{Not supported relocation type:%x}", relType);
					return FALSE;
			}

			pRel = BYTEPTR(pRel) + 2;
		}
	}

	if (pRel >= pRelEnd) {
		return TRUE;
	}
}

