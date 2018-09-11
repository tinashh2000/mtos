#pragma once

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


#define _MTOX_STREAMBUILD

#include <mtos.h>


#pragma pack(push,1)

typedef struct _STREAM {
	union {
		CHARPTR		Buffer;
		WCHARPTR	BufferW;
	};
	UINT64		BufferPosition;
	UINT64		BufferSize;

	MWORD		Handle;

	SD_GETPOSITION	GetPosition;	//This function gets the position of the stream.
	SD_SETPOSITION	SetPosition;

	SD_PUTSTR	PutStr;
	SD_GETSTR	GetStr;

	SD_PUTCHAR	PutChar;
	SD_GETCHAR	GetChar;

	SD_PUTWSTR	PutWStr;
	SD_GETWSTR	GetWStr;

	SD_PUTWCHAR	PutWChar;
	SD_GETWCHAR	GetWChar;

	SD_GETDATA	GetData;
	SD_PUTDATA	PutData;
	SD_CLEAR	Clear;
	
	MWORD		Lock;
} STREAM;

typedef struct _INSTREAM {
	union {
		CHARPTR		Buffer;
		WCHARPTR	BufferW;
	};
	UINT64		BufferPosition;
	UINT64		BufferSize;
	MWORD		Handle;
	SD_GETPOSITION	GetPosition;	//This function gets the position of the stream.
	SD_SETPOSITION	SetPosition;
	SD_GETSTR	GetStr;
	SD_GETCHAR	GetChar;
	SD_GETWSTR	GetWStr;
	SD_GETWCHAR	GetWChar;
	SD_GETDATA	GetData;
	SD_CLEAR	Clear;
	MWORD		Lock;
} INSTREAM;

typedef struct _OUTSTREAM {
	union {
		CHARPTR		Buffer;
		WCHARPTR	BufferW;
	};
	UINT64		BufferPosition;
	UINT64		BufferSize;
	MWORD		Handle;
	SD_GETPOSITION	GetPosition;	//This function gets the position of the stream.
	SD_SETPOSITION	SetPosition;
	SD_PUTSTR	PutStr;
	SD_PUTCHAR	PutChar;
	SD_PUTWSTR	PutWStr;
	SD_PUTWCHAR	PutWChar;
	SD_PUTDATA	PutData;
	SD_CLEAR	Clear;
	MWORD		Lock;
} OUTSTREAM;

typedef struct _MINSTREAM {
	MWORD		Handle;
	MWORD		Type;
	SD_GETDATA	GetData;
	MWORD		Lock;
} MINSTREAM;

typedef struct _MOUTSTREAM {
	MWORD		Handle;
	MWORD		Type;
	SD_PUTDATA	PutData;
	MWORD		Lock;
} MOUTSTREAM;

#pragma options align=reset
#pragma pack(pop)