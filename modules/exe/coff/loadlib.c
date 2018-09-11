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


/* COFFLoadLibrary
 * Detects if the file is a valid COFF executable or DLL.
 * fc is already open to allow other modules to examine the file without re-opening it.
 * if it returns TRUE, the file has been recognised and iinfo is filled with information about the image
 * filebuf is memory allocated by the system, to prevent modules from allocating memory to recognise the file
 * bufSize is the size of filebuf. Depending on the type of system, it can be 512bytes to 8KB
 */ 

BOOL	COFFLoadLibrary(FILE_CONTEXT fc, MT_EXEIMAGEINFO *iinfo,void *filebuf, int bufSize) {

	return FALSE;
}

BOOL	COFFResolveDependencies(FILE_CONTEXT fc, MT_EXEIMAGEINFO *iinfo, IMAGE_FILE_HEADER *ih) {

	IMAGE_OPTIONAL_HEADER32 *ioh = BYTEPTR(ih) + sizeof(IMAGE_FILE_HEADER);
	IMAGE_OPTIONAL_HEADER64 *ioh6 = BYTEPTR(ih) + sizeof(IMAGE_FILE_HEADER);
	IMAGE_DATA_DIRECTORY *importTableEntry = iinfo->word2 == 4 ? &ioh->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT] : &ioh6->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

	int importSize = importTableEntry->Size;
	DWORD *importTable = importTableEntry->VirtualAddress;
	DWORD *iTable =  AllocateMemoryH(importSize);
	IMAGE_SECTION_HEADER *section = IMAGE_FIRST_SECTION(ih);
	int remainingSections = ih->NumberOfSections;
	MEMPTR	rawImportPTR = 0;

	while (remainingSections > 0) {
		if (section->VirtualAddress == importTable) {
			rawImportPTR = section->PointerToRawData;
			break;
		}
		section++;
		remainingSections--;
	}

	if (rawImportPTR == 0) return FALSE;

	if (!FsSetFilePosition(fc, rawImportPTR, SEEK_SET) || FsReadFile(fc, iTable, importSize) < importSize)
		return FALSE;

	eprintf("{RES5x:%x, %x, %x, %x, %x, %x}", importTable, iTable[0], iTable[1], iTable[2], iTable[3], iTable[4]);


	void *library, *proc;
	BOOL	bError;
	DWORD *importData = iTable;
	while (IMAGE_IMPORT_DESCRIPTOR_PTR(importData)->Name != 0) {
		bError = TRUE;
		char *name = BYTEPTR(importData) + (BYTEPTR(IMAGE_IMPORT_DESCRIPTOR_PTR(importData)->Name) - BYTEPTR(importTable));
		DWORD *modules = BYTEPTR(importData) + (BYTEPTR(IMAGE_IMPORT_DESCRIPTOR_PTR(importData)->FirstThunk) - BYTEPTR(importTable));

		if ((library = DlOpen(name, 0)) == 0)	//DlOpen will increase the reference count of the library. The DlClose will be called when an executable or library also terminates
			break;

		while (modules[0] != 0) {
			UINT16 *module = BYTEPTR(importData) + modules[0] - BYTEPTR(importTable);
			char *funcname = BYTEPTR(module) + 2;
			void *addr = DlSym(library, funcname);
			uprintf("%s", funcname);
			modules++;
		}
		importData = BYTEPTR(importData) + sizeof(IMAGE_IMPORT_DESCRIPTOR);
		bError = FALSE;	//If the name will be null we wont have an error, it will help know if we should close libraries in case of an error
	}

	if (bError) {
		while (importData >= iTable) {
			//@@Unload partial libraries
			eprintf("\r\n!!!!!<Unload partial libraries:%s,%i>", __FILE__, __LINE__);
			break;
		}
	}
//	if (library != 0)
//		DlClose(library);

}

int COFFDlClose(void *library) {
	return 0;
}

void *COFFDlOpen(char *libName, int openMode) {
	char *libPath = AllocateMemoryH(MAX_FILELENGTH);
	return 0;
}

void *COFFDlSym(void *library, char*symbolName) {
	return 1;
}