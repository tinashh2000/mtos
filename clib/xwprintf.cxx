#include <mtos.h>
#include <stdlib.h>

MWORD _xpGetWStr(STREAM *s, WCHARPTR str) {
	return 0;
}

MWORD _xpGetWChar(STREAM *s, WCHAR c) {
	char ch[2];

	return 1;
}

MWORD _xpPutWStr(STREAM *s, WCHARPTR str) {
	PrintWStr(str);
	return wcslen(str);
}

MWORD _xpPutWChar(STREAM *s, WCHAR c) {
	char ch[2];
	PrintChar(c);
	return 1;
}

int _xwprintf(STREAM *s, WCHARPTR dest, INT32 numChars, WCHARPTR format, va_list arg) {
	WCHAR boutput[32];
	UINT32 paddNum = 0;
	UINT64 val6;
    UINT32 val3;
    INT32 nChars = numChars == 0 ? MAX_SIGNED : numChars;
    INT32 nnChars=0,opsize=0;
    INT32 pChars=0;
    WCHAR ch,chx;
    WCHARPTR str = (WCHARPTR)format;
	WCHARPTR st;
    BOOL    bFlags;
    while ((chx=GetWideChar(&str)) != 0 && nChars > 0) {
        bFlags=FALSE;

		if (chx == L'%') {

			chx = GetWideChar(&str);
//			PrintChar(chx);
            do {
                switch(chx) {
                    case L'-':
                        break;
                    case L'+':
                    case L'0':
						break;
                }
            } while (bFlags);

            switch (chx) {
                case L'I':
                    if ( str[0] == L'3' && str[1] == L'2') {
						GetWideChar(&str); //Get the 3
						GetWideChar(&str); //Get the 2
                        opsize=32;
                    }
                    if ( str[0] == L'6' && str[1] == L'4') {
						GetWideChar(&str); //Get 6
						GetWideChar(&str); //Get 4
                        opsize=64;
                    }
                    break;
                case L'h':
                    opsize=16;
                    break;
                case L'L':
                    opsize=2;
                    break;
                case L'l':
                    if (str[0]==L'l') {    //ll
                        opsize = 64;
                        GetWideChar(&str);
                        break;
                    }
					else {
                        opsize = 32;
                    }
                    break;
                case L'w':
                    break;

			case L'd':
			case L'i':
                if (opsize==64) {
                    val6 = va_arg(arg, INT64);
                    boutput[Int64ToWStr((WCHARPTR)&boutput, val3, NONE, paddNum)] = 0;
                }
                else if (opsize==16) {
                    val3 = va_arg(arg, INT32);
                    boutput[Int16ToWStr((WCHARPTR)&boutput, val3, NONE, paddNum)] = 0;
                }
                else {
                    val3 = va_arg(arg, INT32);
                    boutput[Int32ToWStr((WCHARPTR)&boutput, val3, NONE, paddNum)] = 0;
                }

                nnChars = StreamPutWString(s,(WCHARPTR)&boutput);
                nChars -= nnChars;
				break;
            case L'u':
				val3 = va_arg(arg, INT32);
                if (opsize==64)
                    boutput[Int64ToWStr((WCHARPTR)&boutput, val3, NONE, paddNum)] = 0;
                else if (opsize==16)
                    boutput[Int16ToWStr((WCHARPTR)&boutput, val3, NONE, paddNum)] = 0;
                else
                    boutput[Int32ToWStr((WCHARPTR)&boutput, val3, NONE, paddNum)] = 0;
                nnChars = StreamPutWString(s,(WCHARPTR)&boutput);
                nChars -= nnChars;
				break;
			case L'x':
                val3 = va_arg(arg, UINT32);
                if (opsize==64)
                    boutput[Hex64ToWStr((WCHARPTR)&boutput, val3, NONE, paddNum)] = 0;
                else if (opsize==16)
                    boutput[Hex16ToWStr((WCHARPTR)&boutput, val3, NONE, paddNum)] = 0;
                else
                    boutput[Hex32ToWStr((WCHARPTR)&boutput, val3, NONE, paddNum)] = 0;
                nnChars = StreamPutWString(s,(WCHARPTR)&boutput);
                nChars -= nnChars;
				break;
			case L'c':
                ch = va_arg(arg, wchar_t);
                nnChars = StreamPutWChar(s,ch);
                nChars -= nnChars;
                break;
			case L's':
				st = va_arg(arg, wchar_t*);
                nnChars = StreamPutWString(s,st);
                nChars -= nnChars;

				break;
			default:
                nnChars = StreamPutWChar(s,L'%');
                nChars -= nnChars;
//				str--;	//it will be advanced foward below.
				break;
			}
		}
        else {

//			printf(",");

			nnChars = StreamPutWChar(s, chx );
            nChars -= nnChars;
//			str--;
        }

//		str++;
        pChars += nnChars;

	}
    if (nChars >0) StreamPutWChar(s,0);
    return pChars;
}

int __CDECL wprintf(const wchar_t* format, ...) {
//    STREAM stream;
	__builtin_va_list args;
	__builtin_va_start(args, format);

	_xwprintf(StdOut_Stream,NULL,0, (WCHARPTR) format, args);

	return 0;
}
