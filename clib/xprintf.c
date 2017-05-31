#include <mtos.h>
#include <stdlib.h>

#include <clib.h>
#include "xprintf.hxx"
#include "xwprintf.cxx"

MWORD _xpGetData(STREAM *s,char *str, MWORD size) {
	return 0;
}

MWORD _xpGetStr(STREAM *s,char *str) {
	return 0;
}

MWORD _xpGetChar(STREAM *s,char c) {
    char ch[2];

   return 1;
}

MWORD _xpPutStr(STREAM *s,char *str) {
	PrintStr(str);
	return strlen(str);
}

MWORD _xpPutChar(STREAM *s,char c) {
    char ch[2];
	PrintChar(c);
   return 1;
}

int	PrintCharRepeat(STREAM *str, int ch, int numTimes) {
	
	int c;
	for (c=0;c<numTimes;c++) {
		StreamPutChar(str,ch);
	}
	return numTimes;
}

UINT32	GetUINT(char**strx,UINT8 nbase) {
	char *str = *strx;
	UINT32	number=0;
	if (nbase >16)
		return 0;

	while (isxdigit(*str))
	{
		int ch = *str;
		if (islower(ch)) ch = toupper(ch);
		ch -= (ch<='9' ? '0' : 'A'-10);
		if (ch>nbase)
			break;

		number= (number*nbase)+ch;
		str++;
	}
	*strx = str;
	return number;
}

int __CDECL  _xprintf(STREAM *s, char * dest, INT32 numChars, const char * format, va_list arg) {
	char boutput[32];
	UINT32 paddNum = 0;
	UINT64 val6;
    UINT32 val3;
	UINT16 val1;
    INT32 nChars = numChars == 0 ?0x10000000 : numChars;
    INT32 nnChars=0,opsize=0;
    INT32 pChars=0;
	BOOL	bZeroPad,bPrePad;
    char ch;
    char *str = (char*)format;
	char *st;
    BOOL    bFlags;

	StreamSyncLock(s);

	if (numChars == 0x12345) {
		PrintHex32(dest, 0);
		PrintChar('>');
		PrintHex32(format, 0);
		PrintChar('>');
		PrintStr(format);
		PrintChar(']');
	}

	while (*str != 0 && nChars > 0) {
        bFlags=FALSE;
		paddNum = 0;
		bZeroPad = 0;
		bPrePad = TRUE;
		if (*str == '%') {
			str++;

            do {
                switch(*str) {
                    case '-':
						bPrePad = FALSE;
                        break;
                    case '+':
						break;
                    default:
						if (isdigit(*str)) {
							if (*str == '0') {
								bZeroPad = TRUE;
								str++;
								if (!isdigit(*str))
									break;
									
								paddNum = GetUINT(&str,10);

							}
						}
                    break;
                }
            } while (bFlags);

            switch (*str) {
                case 'I':
                    if ( *(str+1) == '3' && *(str+2) == '2') {
                        opsize=32;
                        str+=3;
                    }
                    else if ( *(str+1) == '6' && *(str+2) == '4') {
                        opsize=64;
                        str+=3;
                    }
                    break;
                case 'h':
                    str++;
                    opsize=16;
                    break;
                case 'L':
                    opsize=2;
                    break;
                case 'l':
                    str++;
                    if (*str=='l') {    //ll
                        opsize = 64;
                        str++;
                        break;
                    }
                    else {
                        opsize = 32;
                    }
                    break;
                case 'w':
                    break;
            }

			switch (*str) {
			case 'd':
			case 'i':
                if (opsize==64) {
                    val6 = va_arg(arg, INT64);
                    nnChars = Int64ToStr((char*)&boutput, val6, NONE, 0);
                }
                else if (opsize==16) {
                    val3 = va_arg(arg, INT32);
                    nnChars = Int16ToStr((char*)&boutput, val3, NONE, 0);
                }
                else {
                    val3 = va_arg(arg, INT32);
                    nnChars = Int32ToStr((char*)&boutput, val3, NONE, 0);
                }

				if (bPrePad && paddNum > 0 && paddNum > nnChars)
					PrintCharRepeat(s,(bZeroPad) ? '0':' ',paddNum - nnChars);
					
				boutput[nnChars] = 0;
                nnChars = StreamPutString(s,(char *)&boutput);

				if (!bPrePad && paddNum > 0 && paddNum > nnChars)
					PrintCharRepeat(s,(bZeroPad) ? '0':' ',paddNum - nnChars);

                nChars -= nnChars;
				break;
            case 'u':

                if (opsize==64) {
                    val6 = va_arg(arg, INT64);
                    nnChars = Int64ToStr((char*)&boutput, val6, NONE, 0);
				}
                else if (opsize==16) {
                    val3 = va_arg(arg, INT16);
                    nnChars = Int16ToStr((char*)&boutput, val3, NONE, 0);
				}
                else {
                    val3 = va_arg(arg, INT32);
                    nnChars = Int32ToStr((char*)&boutput, val3, NONE, 0);
				}
			
				if (bPrePad && paddNum > 0 && paddNum > nnChars)
					PrintCharRepeat(s,(bZeroPad) ? '0':' ',paddNum - nnChars);

				boutput[nnChars] = 0;
                nnChars = StreamPutString(s,(char *)&boutput);

				if (!bPrePad && paddNum > 0 && paddNum > nnChars )
					PrintCharRepeat(s,(bZeroPad) ? '0':' ',paddNum - nnChars);

                nChars -= nnChars;
				break;
			case 'x':

                if (opsize==64) {
					val6 = va_arg(arg, UINT64);
                    nnChars = Hex64ToStr((char*)&boutput, val6, NONE, 0);
				}
                else if (opsize==16) {
					val3 = va_arg(arg, UINT16);
                    nnChars = Hex16ToStr((char*)&boutput, val3, NONE, 0);
				}
                else {
					val3 = va_arg(arg, UINT32);
                    nnChars = Hex32ToStr((char*)&boutput, val3, NONE, 0);
				}
				if (bPrePad && paddNum > 0 && paddNum > nnChars)
					PrintCharRepeat(s,(bZeroPad) ? '0':' ',paddNum - nnChars);

				boutput[nnChars] = 0;
                nnChars = StreamPutString(s,(char *)&boutput);

				if (!bPrePad && paddNum > 0 && paddNum > nnChars)
					PrintCharRepeat(s,(bZeroPad) ? '0':' ',paddNum - nnChars);

                nChars -= nnChars;
				break;
			case 'c':
                ch = va_arg(arg, char);
                nnChars = StreamPutChar(s,ch);
                nChars -= nnChars;
                break;
			case 's':
				st = va_arg(arg, char*);
                nnChars = StreamPutString(s,st);
                nChars -= nnChars;
				break;
			default:
                nnChars = StreamPutChar(s,'%');
                nChars -= nnChars;
				str--;	//it will be advanced foward below.
				break;
			}
		}
        else {
            nnChars = StreamPutChar(s,*str);
            nChars -= nnChars;
        }
		str++;
        pChars += nnChars;

	}
    if (nChars > 0) StreamPutChar(s,0);
	
	StreamUnlock(s);

	return pChars;
}

int __CDECL sprintf2(char *str, const char *format, ...) {

	STREAM stream;
	va_list args;
	va_start(args, format);
	int nChars = 0;


	if (InitCharStream(&stream, str, 0x10000000, NULL, NULL, NULL, NULL)) {

		PrintChar('@');
		PrintHex32(format, 0);
		PrintChar('@');

		nChars = _xprintf(&stream, str, 0x12345, format, args);
		str[nChars] = 0;
	}
	return 0;

}

int __CDECL sprintf(char *str,const char *format, ...) {

	STREAM stream;
	va_list args;
	va_start(args, format);
	int nChars=0;
    if (InitCharStream(&stream,str, 0x10000000, NULL, NULL, NULL, NULL)) {
		nChars = _xprintf(&stream, str, 0x12345, format, args);
		str[nChars] = 0;
	}
	return 0;

}

int __CDECL snprintf2(char *str, size_t sz, const char *format, ...) {

	STREAM stream;
	va_list args;
	va_start(args, format);
	int nChars = 0;
	if (InitCharStream(&stream, str, sz, NULL, NULL, NULL, NULL)) {
		nChars = _xprintf(&stream, str, 0x12345, format, args);
		str[nChars] = 0;
	}
	return nChars;

}

int __CDECL snprintf(char *str,size_t sz, const char *format, ...) {

	STREAM stream;
	va_list args;
	va_start(args, format);
	int nChars=0;
    if (InitCharStream(&stream,str, sz, NULL, NULL, NULL, NULL)) {
		nChars = _xprintf(&stream, str, sz, format, args);
		str[nChars] = 0;
	}
	return nChars;

}

char * __CDECL xsprintf(char *str,const char *format, ...) {

	STREAM stream;
	va_list args;
	va_start(args, format);

	if (InitCharStream(&stream, str, 0x100000, NULL, NULL, NULL, NULL)) {
		int nChars = _xprintf(&stream, str, 0, format, args);
		str[nChars] = 0;
	}

	return str;
}

char * __CDECL ysprintf(char *str, const char *format, ...) {

	STREAM stream;
	va_list args;
	va_start(args, format);

	if (InitCharStream(&stream, str, 256, NULL, NULL, NULL, NULL)) {
		int nChars = _xprintf(&stream, str, 0, format, args);
		str[nChars] = 0;
	}

	return str;
}

int __CDECL printf(const char *format, ...) {
    STREAM stream;
	__builtin_va_list args;
	__builtin_va_start(args, format);

	_xprintf(StdOut_Stream,NULL,0, format, args);

	return 0;
}

int __CDECL vsnprintf(char* _Buffer, const size_t _BufferCount, const char * _Format, va_list _ArgList) {
	STREAM stream;
    UINT32 nb;
    MWORD *p=((MWORD*) _ArgList);

	if (InitCharStream((STREAM*)&stream, _Buffer, _BufferCount, NULL, NULL, NULL, NULL)) {
        return _xprintf(&stream, NULL, 0, _Format, _ArgList);
	}
    return 0;
}

int	__CDECL vfprintf(FILE *f, const char *format,va_list args) {
    STREAM stream;

	if (f == stderr) {
		return _xprintf(StdError_Stream,NULL,0, format, args);
	}
	else if (f == stdout) {
		return _xprintf(StdOut_Stream,NULL,0, format, args);
	}

	return 0;
}

int __CDECL fprintf ( FILE *f, const char *format, ...) {
	
	STREAM stream;
	__builtin_va_list args;
	__builtin_va_start(args, format);


	if (f == stderr) {
		return _xprintf(StdError_Stream,NULL,0, format, args);
	}
	else if (f == stdout) {
		return _xprintf(StdOut_Stream,NULL,0, format, args);
	}

	return 0;
}

void InitStd() {


	InitWCharStream(&Console_Stream, NULL, 0, _xpPutWStr, _xpPutWChar, _xpGetWStr, _xpGetWChar);
	InitCharStream(&Console_Stream, NULL, 0, _xpPutStr, _xpPutChar, _xpGetStr, _xpGetChar);

	StdIn_Stream = &Console_Stream;
	StdOut_Stream = &Console_Stream;
	StdError_Stream = &Console_Stream;

}
