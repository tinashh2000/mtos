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

MWORD COFFCreateImageThread(TH_THREAD thread, MEMPTR mAllocPTR, UINT32 mAllocSize, MWORD tWord1, MWORD tWord2) {

	MT_EXEIMAGEINFO *iinfo = &I_COFF_BOOTSTRAP(tWord1)->iinfo;
	int bufSize = 4096;
	FS_FINDFILECONTEXT fcxt;
	TH_PROCESS  p = iinfo->p;
	FILE_CONTEXT fc;
//	FS_PATH fileName = AllocateMemoryH(MAX_FILELENGTH);
	MEMPTR buf = I_COFF_BOOTSTRAP(tWord1)->fileBuf;
	memset(&fcxt, 0, sizeof(FS_FINDFILECONTEXT));

//	uprintf("{pe2:%x, %x, %x, %x}", tWord1, I_COFF_BOOTSTRAP(tWord1)->fileBuf, iinfo->fileName, iinfo->fileName);

	int c = 0;
/*	while (BYTEPTR(iinfo->fileName)[c] != 0) {
		((WCHAR*)fileName)[c] = BYTEPTR(iinfo->fileName)[c];
		c++;
	}
	fileName[c] = 0;
*/
	uprintf("{Starting process from :%x, %x, %s:%s}", iinfo->fileName, *UINT32PTR(I_COFF_BOOTSTRAP(tWord1)->fileBuf), I_COFF_BOOTSTRAP(tWord1)->iinfo.fileName, I_COFF_BOOTSTRAP(tWord1)->iinfo.processName);
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

	//Address of entry has the same offset for PE32 and PE32+
	CREATETHREADPARAM ctp = (CREATETHREADPARAM) {
		.ThreadName = iinfo->processName,
			.process = iinfo->p,
			.thProc = BYTEPTR(iinfo->imageAddr) + ioh->AddressOfEntryPoint,
			.cPriority = THREAD_PRIORITY_NORMAL,
			.stackReserve = 0,
			.stackAlloc = 8192,
			.flags = TF_READY,
			.tWord1 = 0,
			.tWord2 = 0
	};
	TH_THREAD newThread = CreateThread(&ctp);

	uprintf("[[Done:%x, %x]]", AllocateMemory(4096), BYTEPTR(iinfo->imageAddr) + ioh->AddressOfEntryPoint);

	while (1);
	return 0;
}