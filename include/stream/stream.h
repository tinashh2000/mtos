#pragma once

#define SD_TYPE_CHARBUFFER	0x01
#define SD_TYPE_UCHARBUFFER	0x02

#if !defined(_MTOX_STREAMBUILD)

typedef struct _STREAM {
	MWORD StreamData[19];
} STREAM;

#define _STREAMPTR STREAM*

#else

	struct _STREAM;
#define _STREAMPTR struct _STREAM*

#endif

typedef MWORD(*SD_SETPOSITION)(struct _STREAM* s,INT64 pos);   //sends data to stream from *data
typedef MWORD(*SD_GETPOSITION)(_STREAMPTR s);   //gets data from stream to *buf
typedef MWORD(*SD_PUTDATA)(_STREAMPTR s, void *data, MWORD size);   //sends data to stream from *data
typedef MWORD(*SD_GETDATA)(_STREAMPTR s, void *buf, MWORD size);    //gets data from stream to *buf
typedef MWORD(*SD_PUTSTR)(_STREAMPTR s,CHARPTR str);
typedef MWORD(*SD_GETSTR)(_STREAMPTR s, CHARPTR str);
typedef MWORD(*SD_PUTCHAR)(_STREAMPTR s, CHAR c);
typedef MWORD(*SD_GETCHAR)(_STREAMPTR s, CHAR c);
typedef MWORD(*SD_PUTWSTR)(_STREAMPTR s,WCHARPTR str);
typedef MWORD(*SD_GETWSTR)(_STREAMPTR s, WCHARPTR str);
typedef MWORD(*SD_PUTWCHAR)(_STREAMPTR s, WCHAR c);
typedef MWORD(*SD_GETWCHAR)(_STREAMPTR s, WCHAR c);
typedef BOOL(*SD_CLEAR)(_STREAMPTR s);

EXPORTSTART

WORD16	GetHex16(char **str);
WORD32	GetHex32(char **str);
WORD64	GetHex64(char **str);

BYTE	GetByte(void **str);
WORD16	GetWord16(void **str);
WORD32	GetWord32(void **str);
WORD64	GetWord64(void **str);

CHAR32	PeekWideChar(WCHARPTR str);
CHAR32	GetWideChar(WCHARPTR *str);
CHAR32	GetUTF16Char(CHAR32 ch);

BOOL InitDataStream(_STREAMPTR s, CHARPTR Buffer, MWORD BufferSize, SD_PUTDATA pd, SD_GETDATA gd );
BOOL InitCharStream(_STREAMPTR s, CHARPTR Buffer, MWORD BufferSize, SD_PUTSTR ps, SD_PUTCHAR pc, SD_GETSTR gs, SD_GETCHAR gc);
BOOL InitWCharStream(_STREAMPTR s, WCHARPTR BufferW, MWORD BufferSize, SD_PUTWSTR ps, SD_PUTWCHAR pc, SD_GETWSTR gs, SD_GETWCHAR gc );
MWORD StreamPutWString(_STREAMPTR s, WCHARPTR str);
MWORD StreamPutString(_STREAMPTR s,CHARPTR str);
BOOL StreamClear(_STREAMPTR s);
MWORD StreamPutWChar(_STREAMPTR s, CHAR32 ch);
MWORD StreamPutChar(_STREAMPTR s, CHAR ch);
MWORD StreamGetData(_STREAMPTR s, void *buf, MWORD size);
MWORD StreamPutData(_STREAMPTR s, void *data, MWORD size);
INT64 StreamGetPosition(_STREAMPTR s);
INT64 StreamSetPosition(_STREAMPTR s, INT64 pos);
BOOL	StreamAsyncLock(_STREAMPTR s);
BOOL	StreamSyncLock(_STREAMPTR s);
BOOL	StreamUnlock(_STREAMPTR s);

EXPORTEND