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

BOOL OutStreamInitChar(_OUTSTREAMPTR s, CHARPTR Buffer, MWORD BufferSize, SD_PUTSTR ps, SD_PUTCHAR pc) {

	s->Lock = 0;
	s->Buffer = Buffer;
	s->BufferPosition = 0;
	s->BufferSize = BufferSize;
	s->PutStr = ps;

	s->PutChar = pc;

	return TRUE;

}

BOOL	OutStreamSetHandle(_OUTSTREAMPTR s, MWORD handle) {
	s->Handle = handle;
	return TRUE;
}

BOOL OutStreamInitWChar(_OUTSTREAMPTR s, WCHARPTR BufferW, MWORD BufferSize, SD_PUTWSTR ps, SD_PUTWCHAR pc) {

	s->Lock = 0;
	s->BufferW = BufferW;
	s->BufferPosition = 0;
	s->BufferSize = BufferSize;
	s->PutWStr = ps;
	s->PutWChar = pc; 
	return TRUE;

}

BOOL OutStreamClear(_OUTSTREAMPTR s) {

	if (s->Clear)
		return s->Clear(s);
	else {
		s->BufferPosition = 0;
		s->Buffer[0] = 0;
	}
    return TRUE;

}

MWORD OutStreamPutWString(_OUTSTREAMPTR s, WCHARPTR str) {

	if (s->PutWStr != NULL)
		return s->PutWStr(s, str);
	else {
		UINT64 bytesLeft = s->BufferSize - s->BufferPosition;
		UINT32 cBytes = wcsnlen(str, (UINT32) (bytesLeft/sizeof(WCHAR))) * sizeof(WCHAR);
		memcpy((void*)&s->Buffer[s->BufferPosition], str, cBytes );
		s->BufferPosition += cBytes;
		return cBytes;
	}

}

MWORD OutStreamPutString(_OUTSTREAMPTR s,CHARPTR str) {

	if (s->PutStr != NULL)
		return s->PutStr(s,str);
	else {
		UINT64 bytesLeft = s->BufferSize - s->BufferPosition;
		UINT32 cBytes = strnlen(str, (UINT32) bytesLeft);
		memcpy((void*) &s->Buffer[s->BufferPosition], str, cBytes);
		s->BufferPosition += cBytes;
		return cBytes;
	}

}

MWORD OutStreamPutWChar(_OUTSTREAMPTR s, WCHAR ch) {

	if (s->PutWChar != NULL)
		return s->PutWChar(s, ch);
	else {
		if (s->Buffer != NULL) {
			if (s->BufferPosition + sizeof(WCHAR) < s->BufferSize) {
				s->BufferW[s->BufferPosition] = ch;
				s->BufferPosition += sizeof(WCHAR);
				return sizeof(WCHAR);
			}
		}
	}
	return 0;

}

MWORD OutStreamPutChar(_OUTSTREAMPTR s, CHAR ch) {

	if (s->PutChar != NULL)
        return s->PutChar(s,ch);
	else {
		if (s->Buffer != NULL) {
			if (s->BufferPosition < s->BufferSize) {
				s->Buffer[s->BufferPosition] = ch;
				s->BufferPosition++;
				return 1;
			}
		}
	}
	return 0;

} 


MWORD OutStreamPutData(_OUTSTREAMPTR s, void *data, MWORD size) {
	return s->PutData(s,data, size);
}

INT64	OutStreamGetBufferSize(_OUTSTREAMPTR s) {
	return s->BufferSize;
}

char *OutStreamGetBuffer(_OUTSTREAMPTR s) {
	return s->Buffer;
}

MWORD OutStreamGetHandle(_OUTSTREAMPTR s) {
	return s->Handle;
}

INT64	OutStreamGetPosition(_OUTSTREAMPTR s) {

	if (s->GetPosition != NULL)
		return s->GetPosition(s);
	else
		return s->BufferPosition;

}

INT64 OutStreamSetPosition(_OUTSTREAMPTR s, INT64 pos) {

	if (s->SetPosition != NULL)
		return s->SetPosition(s,pos);
	else {
		return s->BufferPosition = pos;
	}
}

BOOL	OutStreamAsyncLock(_OUTSTREAMPTR s) {
	return AcquireVariableLock(&s->Lock);
}

BOOL	OutStreamSyncLock(_OUTSTREAMPTR s) {
	return TRUE;
	return LockVariable(&s->Lock);
}

BOOL	OutStreamUnlock(_OUTSTREAMPTR s) {
	return TRUE;
	return UnlockVariable(&s->Lock);
}