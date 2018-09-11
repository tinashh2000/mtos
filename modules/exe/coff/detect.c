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

#define __MTOS_DEBUG__
#include "../exe.h"
#include <filesys.h>

#include <mm/vmm.h>


/* COFFDetectFormat
 * Detects if the file is a valid COFF executable or DLL.
 * fc is already open to allow other modules to examine the file without re-opening it.
 * if it returns TRUE, the file has been recognised and iinfo is filled with information about the image
 * filebuf is memory allocated by the system, to prevent modules from allocating memory to recognise the file
 * bufSize is the size of filebuf. Depending on the type of system, it can be 512bytes to 8KB
 */ 

BOOL	COFFDetectFormat(FILE_CONTEXT fc, MT_EXEIMAGEINFO *iinfo) {
	char *peHeader;
	int bufSize;
	void *buf;

	if (iinfo->buf == 0 || iinfo->bufSize < 8192) {
		buf = AllocateMemoryH(8192);
		bufSize = 8192;
	}
	else {
		buf = iinfo->buf;
		bufSize = iinfo->bufSize;
	}

	FsSetFilePosition(fc, 0, SEEK_SET);
	UINT32 bytesRead = FsReadFile(fc, buf, sizeof(IMAGE_DOS_HEADER));	//Read the COFF header separately bcz some programs might embed a very large DOS program before the COFF header

	//This will not repeat, but it will help us break out when an error occurs. We want to avoid calling the memory-free function many times.

	while ((MZ_CAST(buf)->e_magic == IMAGE_DOS_SIGNATURE || MZ_CAST(buf)->e_magic == IMAGE_DOS_SIGNATURE2) && (MZ_CAST(buf)->e_lfarlc >= 0x40)) {
		dprintf("{%i}", __LINE__);
		if (!FsSetFilePosition(fc, MZ_CAST(buf)->e_lfanew, SEEK_SET)) {
			break;
		}
		dprintf("{%i}", __LINE__);
		iinfo->word1 = MZ_CAST(buf)->e_lfanew; //Save pointer to PE header
		if ((bytesRead = FsReadFile(fc, buf, sizeof(IMAGE_FILE_HEADER) + 4)) != sizeof(IMAGE_FILE_HEADER) + 4)
			break;
		dprintf("{%i}", __LINE__);
		peHeader = BYTEPTR(buf); // +MZ_CAST(buf)->e_lfanew;
		if (memcmp(peHeader, &peSignature[0], 4) != 0) {
			break;
		}
		dprintf("{%i}", __LINE__);
		IMAGE_FILE_HEADER *ih = BYTEPTR(peHeader) + 4;
		IMAGE_OPTIONAL_HEADER32 *ioh = BYTEPTR(ih) + sizeof(IMAGE_FILE_HEADER);
		IMAGE_OPTIONAL_HEADER64 *ioh6 = BYTEPTR(ih) + sizeof(IMAGE_FILE_HEADER);
		dprintf("{%i}", __LINE__);
		if (ih->Machine == IMAGE_FILE_MACHINE_I386)
			iinfo->word2 = 4;
		else if (ih->Machine == IMAGE_FILE_MACHINE_AMD64)
			iinfo->word2 = 8;
		else
			break;

		dprintf("{%i}", __LINE__);

		if (ih->SizeOfOptionalHeader > 512) break;
		int nBytes = FsReadFile(fc, BYTEPTR(buf) + bytesRead, ih->SizeOfOptionalHeader);
		if (nBytes != ih->SizeOfOptionalHeader) break;
		iinfo->word4 = nBytes + bytesRead;
		int numSections = ih->NumberOfSections;
		if (numSections == 0 || numSections > 96) break;
		if (iinfo->word2 == 8) {
			if (ioh6->FileAlignment < 512 || ioh6->FileAlignment > ioh6->SectionAlignment) break;
			iinfo->stackReserve = ioh6->SizeOfStackReserve;
			iinfo->memReserve = ioh6->SizeOfHeapReserve;
			iinfo->memCommit = ioh6->SizeOfHeapCommit;
			iinfo->stackCommit = ioh6->SizeOfStackCommit;
			iinfo->imageSize = ioh6->SizeOfImage;
		}
		else if (iinfo->word2 == 4) {
			if (ioh->FileAlignment < 512 || ioh->FileAlignment > ioh->SectionAlignment) break;
			iinfo->stackReserve = ioh->SizeOfStackReserve;
			iinfo->memReserve = ioh->SizeOfHeapReserve;
			iinfo->memCommit = ioh->SizeOfHeapCommit;
			iinfo->stackCommit = ioh->SizeOfStackCommit;
			iinfo->imageSize = ioh->SizeOfImage;
		}
//		iinfo->word3 = (numSections << 16) | ih->SizeOfOptionalHeader;
		IMAGE_SECTION_HEADER *section = IMAGE_FIRST_SECTION(ih);

		dprintf("{%i}", __LINE__);

/* 
 * The buffer must be able to contain all the headers.
 * The buffer must only run-out while scanning the sections - not before
 */	
		uprintf("[\0330Aimgsz:%x,%x,%x\03307]", fc, iinfo->imageSize, iinfo->word4);
		iinfo->flags |= EII_CREATEKERNELPROCESS | EII_CREATEPROCESS;	//If this library resides in kernel space, we can do this.
		iinfo->buf = buf;
		iinfo->bufSize = bufSize;
		return TRUE;
	}

	dprintf("{%i}", __LINE__);

	if (iinfo->buf != buf)
		FreeMemory(buf);

	return FALSE;
}
