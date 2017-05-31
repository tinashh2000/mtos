#include <mtos.h>
#include <stdlib.h>
#include "hextable.h"

int __CDECL puts(const char *s) {
	return PrintStr((CHARPTR) s);
}

void  *rawmemchr(void *block, int c) {
	return memchr(block, c, -1);
}

void *mempcpy(void *dest,void *src,size_t size) {
	memcpy(dest, src, size);
	return (void*)((CHARPTR)src + size);
}

char * __CDECL strlwr(char *str)
{
	char  *stx = str;

	while (*stx) {
		*stx = tolower(*stx);
		stx++;
	}
	return str;
}


char * __CDECL strupr(char *str)
{
	char  *stx = str;

	while (*stx) {
		*stx = toupper(*stx);
		stx++;
	}
	return str;
}


BOOL	IsNumber(char *str) {

	while (*str != 0) {
		if (*str < 48 || *str > 57)
			return FALSE;

		str++;
	}
	return TRUE;

}

UINT32 CopyStr(CHARPTR dest,CHARPTR src,UINT32*limit) {
	UINT32 sLen;
	if (limit != NULL) {
		sLen = strnlen(src, *limit);
		memcpy(dest, src,sLen);
		*limit -= sLen;
//		*((CHARPTR )dest + sLen) = 0;
		return sLen;
	}
	sLen = strlen(src);
	memcpy(dest, src,sLen);
	return sLen;
}

UINT32 Int64ToStr(CHARPTR st, UINT64 val,UINT32* limit,UINT32 paddNum) {
	UINT64 vl = val;
	CHAR buf[21];
	CHARPTR dst = &buf[20];
	UINT32 olen;	//Length of output
	UINT32 xlimit = (limit != NULL) ? *limit : 100;

	if (xlimit == 0) return 0;

	*dst = 0; //last char
	olen = 0;
	do {
		UINT8 rem = vl % 10;
		dst--;
		vl /= 10;
		*dst = (rem + 0x30);
		olen++;
	} while (vl > 0);

	while (olen < paddNum) {
		*dst = 0x30;
		dst--;
		olen++;
	}

	olen = (olen > xlimit ? xlimit : olen);
	memcpy(st, dst, olen);
	if (limit != NULL) *limit -= olen;
	return olen;
}

UINT32 Hex64ToStr(CHARPTR str, UINT64 val,UINT32 *limit,UINT32 paddNum) {
	UINT8 c;
	CHAR chx;
	UINT32 olen = 0;
	CHARPTR desx = str;
	UINT32	xlimit = (limit == NULL) ? 20 : *limit;
	if (xlimit == 0) return 0;

	for (c = 0;(c < 16 && (xlimit > 0));c++) { //If limit is one, dont! spare that 1 for null term
		chx = (val >> (15 - c) * 4) & 0x0f;
		if (olen == 0 && chx == 0 && (paddNum < (15 - c))) continue;
		*desx = HexTable[chx];
		desx++;
		xlimit--;
		olen++;
	}
	if (limit != NULL) *limit = xlimit;
	return olen;
}

UINT32 Hex32ToStr(CHARPTR str, UINT32 val,UINT32 *limit,UINT32 paddNum) {
	UINT8 c;
	CHAR chx;
	UINT32 olen = 0;
	CHARPTR desx = str;
	UINT32	xlimit = (limit == NULL) ? 20 : *limit;
	UINT32 pad = paddNum > 8 ? 8 : paddNum;
	if (xlimit == 0) return 0;

	for (c = 0;(c < 8 && (xlimit>0));c++) {
		chx = (val >> (7 - c) * 4) & 0x0f;
		if (olen == 0 && chx == 0 && (paddNum < (7 - c))) continue;
		*desx = HexTable[chx];
		desx++;
		xlimit--;
		olen++;
	}
	if (limit != NULL) *limit = xlimit;
	return olen;
}

UINT32 Int32ToStr(CHARPTR st,UINT32 val, UINT32* limit,UINT32 paddNum) {
	UINT32 vl = val;
	CHAR buf[12];
	CHARPTR dst = &buf[11];
	UINT32 olen;	//Length of output
	UINT32 xlimit = (limit != NULL) ? *limit : 100;

	if (xlimit == 0) return 0;

	*dst = 0; //last char
	olen = 0;
	do {
		UINT8 rem = vl % 10;
		dst--;
		vl /= 10;
		*dst = (rem + 0x30);
		olen++;
	} while (vl > 0);

	while (olen < paddNum) {
		*dst = 0x30;
		dst--;
		olen++;
	}

	olen = (olen > xlimit ? xlimit : olen);
	memcpy(st, dst, olen);
	if (limit != NULL) *limit -= olen;

	return olen;
}


UINT32 Int16ToStr(CHARPTR st,UINT32 val, UINT32* limit,UINT32 paddNum) {
    UINT16	vl = val;
	CHAR	buf[12];
	CHARPTR	dst = &buf[11];
	UINT32	olen;	//Length of output
	UINT32	xlimit = (limit != NULL) ? *limit : 100;

	if (xlimit == 0) return 0;

	*dst = 0; //last char
	olen = 0;
	do {
		UINT8 rem = vl % 10;
		dst--;
		vl /= 10;
		*dst = (rem + 0x30);
		olen++;
	} while (vl > 0);

	while (olen < paddNum) {
		*dst = 0x30;
		dst--;
		olen++;
	}

	olen = (olen > xlimit ? xlimit : olen);
	memcpy(st, dst, olen);
	if (limit != NULL) *limit -= olen;

	return olen;
}

UINT32 Hex16ToStr(CHARPTR str, UINT32 val,UINT32 *limit,UINT32 paddNum) {
	UINT8 c;
	CHAR chx;
	UINT32 olen = 0;
	CHARPTR desx = str;
	UINT32	xlimit = (limit == NULL) ? 20 : *limit;
    UINT32 pad = paddNum > 4 ? 4 : paddNum;
	if (xlimit == 0) return 0;

    for (c = 0;(c < 4 && (xlimit>0));c++) {
        chx = (val >> (3 - c) * 4) & 0x0f;
        if (olen == 0 && chx == 0 && (paddNum < (3 - c))) continue;
		*desx = HexTable[chx];
		desx++;
		xlimit--;
		olen++;
	}
	if (limit != NULL) *limit = xlimit;
	return olen;
}


void PrintInt32(UINT32 val,UINT32 paddNum) {
	CHAR output[11];

    output[Int32ToStr((CHARPTR )&output, val, NONE,paddNum)]=0;
	PrintStr((CHARPTR ) &output);

}

void PrintInt64(UINT32 val,UINT32 paddNum) {
	CHAR output[21];

    output[Int64ToStr((CHARPTR )&output, val, NONE,paddNum)] = 0;
	PrintStr((CHARPTR ) &output);
}

void PrintHexW(UINT16 num) {
    INT32 c;
//    BeginPrint();

    for (c=0;c<4;c++)
        PrintChar( HexTable[(num >> (3-c)*4) & 0x0f] );

//    EndPrint();
}

void PrintHexB(BYTE num) {
    INT32 c;

//    BeginPrint();

    for (c=0;c<2;c++)
        PrintChar( HexTable[(num >> (1-c)*4) & 0x0f] );

//    EndPrint();
}

void PrintHex32(UINT32 val,UINT32 paddNum) {
	CHAR output[9];

    output[Hex32ToStr((CHARPTR )&output, val, NONE, paddNum)] = 0;
	PrintStr((CHARPTR )&output);

}

void PrintHex64(UINT32 val,UINT32 paddNum) {
	CHAR output[17];

    output[Hex64ToStr((CHARPTR )&output, val, NONE, paddNum)] = 0;
	PrintStr((CHARPTR )&output);
}

//wchar_t * wmemrchr()
void PrintLF() {
	PrintStr("\r\n");
}

void PrintLFStr(CHARPTR strx) {
	PrintStr("\r\n");
	PrintStr(strx);
}

void PrintStrLF(CHARPTR strx) {
	PrintStr(strx);
	PrintStr("\r\n");
}

void PrintLFStrLF(CHARPTR strx) {
	PrintStr("\r\n");
	PrintStr(strx);
	PrintStr("\r\n");
}

void PrintHexD(UINT32 num) {
    INT32 c;
//    BeginPrint();

    for (c=0;c<8;c++)
        PrintChar( HexTable[(num >> (7-c)*4) & 0x0f] );

//    EndPrint();
}
