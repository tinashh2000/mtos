/***************************************************************************************
* Copyright (C) 2018 Tinashe Mutandagayi                                               *
*                                                                                      *
* This file is part of the MT-Operating System source code. The author(s) of this file *
* is/are not liable for any damages, loss or loss of information, deaths, sicknesses   *
* or other bad things resulting from use of this file or software, either direct or    *
* indirect.                                                                            *
* Terms and conditions for use and distribution can be found in the license file named *
* LICENSE.TXT. If you distribute this file or continue using it,                       *
* it means you understand and agree with the terms and conditions in the license file. *
* binding this file.                                                                   *
*                                                                                      *
* Happy Coding :)                                                                      *
****************************************************************************************/

#include <mtos.h>

#define DLL_PROCESS_ATTACH 1
#define DLL_THREAD_ATTACH 2
#define DLL_THREAD_DETACH 3
#define DLL_PROCESS_DETACH 0
#define DLL_PROCESS_VERIFIER 4

__declspec(dllexport) int DllMain(int hinstDLL, int fdwReason, void* lpvReserved)
{
	switch (fdwReason) 
	{ 
	/*
	 * The DLL is loading due to process 
	 * initialization or a call to LoadLibrary. 
	 */
	case DLL_PROCESS_ATTACH: 
		break; 
 
	/* The attached process creates a new thread.  */
	case DLL_THREAD_ATTACH: 
		break; 
 
	/* The thread of the attached process terminates. */
	case DLL_THREAD_DETACH: 
		break; 
 
	/*
	 * The DLL is unloading from a process due to 
	 * process termination or a call to FreeLibrary. 
	 */
	case DLL_PROCESS_DETACH: 
		break; 

	default: 
		break; 
	} 
	return 1;
}


int _terminate() {
	return 100;
}