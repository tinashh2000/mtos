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

#include "stream.h"

BOOL InStreamInitChar(_INSTREAMPTR s, CHARPTR Buffer, MWORD BufferSize, SD_GETSTR gs, SD_GETCHAR gc) {

	s->Lock = 0;
	s->Buffer = Buffer;
	s->BufferPosition = 0;
	s->BufferSize = BufferSize;
	s->GetStr = gs;
	s->GetChar = gc;
	return TRUE;

}


BOOL	InStreamSetHandle(_INSTREAMPTR s, MWORD handle) {
	s->Handle = handle;
	return TRUE;
}

BOOL InStreamInitWChar(_INSTREAMPTR s, WCHARPTR BufferW, MWORD BufferSize, SD_GETWSTR gs, SD_GETWCHAR gc ) {

	s->Lock = 0;
	s->BufferW = BufferW;
	s->BufferPosition = 0;
	s->BufferSize = BufferSize;
	s->GetWStr = gs;
	s->GetWChar = gc;
	return TRUE;

}
 
BOOL InStreamClear(_INSTREAMPTR s) {

	if (s->Clear)
		return s->Clear(s);
	else {
		s->BufferPosition = 0;
		s->Buffer[0] = 0;
	}
    return TRUE;

}

MWORD InStreamGetData(_INSTREAMPTR s, void *buf, MWORD size) {
	return s->GetData(s,buf, size);
}

INT64	InStreamGetBufferSize(_INSTREAMPTR s) {
	return s->BufferSize;
}

INT64	InStreamGetPosition(_INSTREAMPTR s) {

	if (s->GetPosition != NULL)
		return s->GetPosition(s);
	else
		return s->BufferPosition;

}

INT64 InStreamSetPosition(_INSTREAMPTR s, INT64 pos) {

	if (s->SetPosition != NULL)
		return s->SetPosition(s,pos);
	else {
		return s->BufferPosition = pos;
	}
}

BOOL	InStreamAsyncLock(_INSTREAMPTR s) {
	return AcquireVariableLock(&s->Lock);
}

BOOL	InStreamSyncLock(_INSTREAMPTR s) {
	return TRUE;
	return LockVariable(&s->Lock);
}

BOOL	InStreamUnlock(_INSTREAMPTR s) {
	return TRUE;
	return UnlockVariable(&s->Lock);
}