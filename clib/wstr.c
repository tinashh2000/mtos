#include <mtos.h>
#include <stdlib.h>
#include <stream/stream.h>
#include <wctype.h>

//#include "hextable.h"

IMPORT char* HexTable;

int __CDECL _putws(const wchar_t *s) {
	return PrintWStr((WCHARPTR)s);
}

wchar_t * __CDECL wcsrchr(const wchar_t *wstring, wchar_t c) {
	return wmemrchr(wstring, c, wcslen(wstring));
}

size_t __CDECL wcsnlen(const wchar_t* s, size_t n)
{
	wchar_t * z = (wchar_t*) wmemchr((void*)s, 0, n);
	if (z) n = z-s;
	return n;
}

wchar_t * __CDECL wmempcpy(wchar_t * dest, wchar_t * src,size_t size) {
	wmemcpy(dest, src, size);
	return src + size;
}

wchar_t * __CDECL wmemmove(wchar_t *_S1, const wchar_t *_S2, size_t _N)
{
	return (wchar_t *)memmove(_S1, _S2, _N*sizeof(wchar_t));
}

int __CDECL wmemcmp(const wchar_t* ptr1, const wchar_t* ptr2, size_t sz) {
	return memcmp(ptr1,ptr2,sz * sizeof(wchar_t)) > 0 ? 1 : -1;
}

wchar_t * __CDECL wcslwr(wchar_t *str)
{
	wchar_t  *stx = str;

	while (*stx) {
		*stx = towlower(*stx);
		stx++;
	}
	return str;
}

wchar_t * __CDECL wcsupr(wchar_t *str)
{
	wchar_t  *stx = str;

	while (*stx != 0) {
		*stx = towupper(*stx);
		stx++;
	}
	return str;
}

/*
wchar_t * __CDECL wmemcpy(wchar_t * wto, const wchar_t * wfrom,size_t size)
{
	return (wchar_t *)memcpy(wto, wfrom, size * sizeof(wchar_t));
}
*/

//wcschr	__CDECL



BOOL	IsNumberW(WCHAR *str) {

	CHAR32 ch;
	while ((ch = GetWideChar(&str)) != 0) {
		if (*str < 48 || *str > 57) {
			return FALSE;
		}
	}
	return TRUE;

}

UINT32 CopyWStr(wchar_t * dest,wchar_t * src,UINT32*limit) {
	UINT32 sLen;
	if (limit != NULL) {
		sLen = wcsnlen(src, *limit);
		wmemcpy(dest, src,sLen);
		*limit -= sLen;
//		*((CHARPTR )dest + sLen) = 0;
		return sLen;
	}
	sLen = wcslen(src);
	wmemcpy(dest, src,sLen);
	return sLen;
}

UINT32 Int64ToWStr(WCHARPTR st, UINT64 val,UINT32* limit,UINT32 paddNum) {
	UINT64 vl = val;
	WCHAR buf[21];
	WCHARPTR dst = &buf[20];
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
	wmemcpy(st, dst, olen);
	if (limit != NULL) *limit -= olen;
	return olen;
}

UINT32 Hex64ToWStr(WCHARPTR str, UINT64 val,UINT32 *limit,UINT32 paddNum) {
	UINT8 c;
	WCHAR chx;
	UINT32 olen = 0;
	WCHARPTR desx = str;
	UINT32	xlimit = (limit == NULL) ? 20 : *limit;
	if (xlimit == 0) return 0;

	for (c = 0;(c < 16 && (xlimit > 0));c++) { //If limit is one, dont! spare that 1 for null term
		chx = (val >> (15 - c) * 4) & 0x0f;
		if (olen == 0 && chx == 0 && (paddNum < (16 - c))) continue;
		*desx = (WCHAR)(HexTable[chx]);
		desx++;
		xlimit--;
		olen++;
	}
	if (limit != NULL) *limit = xlimit;
	return olen;
}

UINT32 Hex32ToWStr(WCHARPTR str, UINT32 val,UINT32 *limit,UINT32 paddNum) {
	UINT8 c;
	WCHAR chx;
	UINT32 olen = 0;
	WCHARPTR desx = str;
	UINT32	xlimit = (limit == NULL) ? 20 : *limit;
	UINT32 pad = paddNum > 8 ? 8 : paddNum;
	if (xlimit == 0) return 0;

	for (c = 0;(c < 8 && (xlimit>0));c++) {
		chx = (val >> (7 - c) * 4) & 0x0f;
		if (olen == 0 && chx == 0 && (paddNum < (8 - c))) continue;
		*desx = (WCHAR)(HexTable[chx]);
		desx++;
		xlimit--;
		olen++;
	}
	if (limit != NULL) *limit = xlimit;
	return olen;
}

UINT32 Int32ToWStr(WCHARPTR st,UINT32 val, UINT32* limit,UINT32 paddNum) {
	UINT32 vl = val;
	WCHAR buf[12];
	WCHARPTR dst = &buf[11];
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
	wmemcpy(st, dst, olen);
	if (limit != NULL) *limit -= olen;

	return olen;
}

UINT32 Int16ToWStr(WCHARPTR st,UINT32 val, UINT32* limit,UINT32 paddNum) {
    UINT16	vl = val;
	WCHAR	buf[12];
	WCHARPTR	dst = &buf[11];
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
	wmemcpy(st, dst, olen);
	if (limit != NULL) *limit -= olen;

	return olen;
}

UINT32 Hex16ToWStr(WCHARPTR str, UINT32 val,UINT32 *limit,UINT32 paddNum) {
	UINT8 c;
	WCHAR chx;
	UINT32 olen = 0;
	WCHARPTR desx = str;
	UINT32	xlimit = (limit == NULL) ? 20 : *limit;
    UINT32 pad = paddNum > 4 ? 4 : paddNum;
	if (xlimit == 0) return 0;

    for (c = 0;(c < 4 && (xlimit>0));c++) {
        chx = (val >> (3 - c) * 4) & 0x0f;
        if (olen == 0 && chx == 0 && (paddNum < (4 - c))) continue;
		*desx = (WCHAR)(HexTable[chx]);
		desx++;
		xlimit--;
		olen++;
	}
	if (limit != NULL) *limit = xlimit;
	return olen;
}

size_t __CDECL mtos_wcmemdiff(WCHARPTR s1, WCHARPTR s2, size_t len) {
	return (((size_t)mtos_memdiff((CHARPTR)s1, (CHARPTR)s2, len*2)) >> 1);
}
