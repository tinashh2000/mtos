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
#include "stream.hxx"

#define HEXTOINT(ch) 	\
		if (ch >='0' && ch <= '9')\
			ch -= '0';\
		else if (ch >='a' && ch <= 'f')\
			ch -= ('a' - 10);\
		else if (ch >='A' && ch <='F')\
			ch -= ('A' - 10);\
		else\
			ch=0xFF;\


WORD64	GetHex64(char **str) {
	WORD64	w = 0;
	char c = 16;
	unsigned char d;
	while (**str != 0 && c-- > 0) {
		d = **str;

		HEXTOINT(d);

		if (d == 0xff)
			break;

		w = (w << 4) | (d & 15);
		*(str) += 1;
	}
	return w;
}
			
WORD16	GetHex16(char **str) {
	WORD16	w = 0;
	char c = 4;
	unsigned char d;
	while (**str != 0 && c-- > 0) {
		d = **str;
		HEXTOINT(d);

		if (d == 0xff)
			break;

		w = (w << 4) | (d & 15);
		*(str) += 1;
	}
	return w;
}

WORD32	GetHex32(char **str) {
	WORD32	w = 0;
	char c = 8;
	unsigned char d;
	while (**str != 0 && c-- > 0) {
		d = **str;

		HEXTOINT(d);
		
		
		if (d == 0xff)
			break;

		w = (w << 4) | (d & 15);
		*(str) += 1;
	}
	return w;
}

BYTE	GetByte(void **str) {
	BYTE w = **((BYTE**) str);
	*((char **) str) += 2;
	return w;
}

WORD16	GetWord16(void **str) {
	WORD16 w = **((WORD16**) str);
	*((char **) str) += 2;
	return w;
}

WORD32	GetWord32(void **str) {
	WORD32 w = **((WORD32**) str);
	*((char **) str) += 4;
	return w;
}

WORD64	GetWord64(void **str) {
	WORD64 w = **((WORD64**) str);
	*((char **) str) += 8;
	return w;
}

BOOL InitDataStream(_STREAMPTR s, CHARPTR Buffer, MWORD BufferSize, SD_PUTDATA pd, SD_GETDATA gd ) {

	s->Lock = 0;
	s->Buffer = Buffer;
	s->BufferPosition = 0;
	s->BufferSize = BufferSize;

	s->PutData = pd;
	s->GetData = gd;
	return TRUE;

}

BOOL InitCharStream(_STREAMPTR s, CHARPTR Buffer, MWORD BufferSize, SD_PUTSTR ps, SD_PUTCHAR pc, SD_GETSTR gs, SD_GETCHAR gc) {

	s->Lock = 0;
	s->Buffer = Buffer;
	s->BufferPosition = 0;
	s->BufferSize = BufferSize;
	s->PutStr = ps;
	s->GetStr = gs;
	s->PutChar = pc;
	s->GetChar = gc;
	return TRUE;

}

BOOL	StreamSetHandle(_STREAMPTR s, MWORD handle) {
	s->Handle = handle;
	return TRUE;
}

extern MWORD KernelBaseAddress;

void phexx(UINT32 h);
void pstrr(char *str);


BOOL InitWCharStream(_STREAMPTR s, WCHARPTR BufferW, MWORD BufferSize, SD_PUTWSTR ps, SD_PUTWCHAR pc, SD_GETWSTR gs, SD_GETWCHAR gc ) {

	s->Lock = 0;
	s->BufferW = BufferW;
	s->BufferPosition = 0;
	s->BufferSize = BufferSize;
	s->PutWStr = ps;
	s->GetWStr = gs;
	s->PutWChar = pc;
	s->GetWChar = gc;
	return TRUE;

}

BOOL StreamClear(_STREAMPTR s) {

	if (s->Clear)
		return s->Clear(s);
	else {
		s->BufferPosition = 0;
		s->Buffer[0] = 0;
	}
    return TRUE;

	}

MWORD StreamPutWString(_STREAMPTR s, WCHARPTR str) {

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

MWORD StreamPutString(_STREAMPTR s,CHARPTR str) {

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

MWORD StreamPutWChar(_STREAMPTR s, WCHAR ch) {

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

MWORD StreamPutChar(_STREAMPTR s, CHAR ch) {

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

MWORD StreamGetData(_STREAMPTR s, void *buf, MWORD size) {
	return s->GetData(s,buf, size);
}

MWORD StreamPutData(_STREAMPTR s, void *data, MWORD size) {
	return s->PutData(s,data, size);
}

INT64	StreamGetBufferSize(_STREAMPTR s) {
	return s->BufferSize;
}

INT64	StreamGetPosition(_STREAMPTR s) {

	if (s->GetPosition != NULL)
		return s->GetPosition(s);
	else
		return s->BufferPosition;

}

INT64 StreamSetPosition(_STREAMPTR s, INT64 pos) {

	if (s->SetPosition != NULL)
		return s->SetPosition(s,pos);
	else {
		return s->BufferPosition = pos;
	}
}

BOOL	StreamAsyncLock(_STREAMPTR s) {
	return AcquireVariableLock(&s->Lock);
}

BOOL	StreamSyncLock(_STREAMPTR s) {
//	return TRUE;
	return LockVariable(&s->Lock);
}

BOOL	StreamUnlock(_STREAMPTR s) {
//	return TRUE;
	return UnlockVariable(&s->Lock);
}