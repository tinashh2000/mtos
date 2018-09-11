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


char spacechars[] = { 0x20,0x09,0x0a,0x0b,0x0c,0x0d };

int __CDECL isalpha(int c) {
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int __CDECL iswalpha(wint_t c) {
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int __CDECL iswupper(wint_t c) {
	return (c >= 65 && c <= 90);
}

int __CDECL iswlower(wint_t c) {
	return (c >= 97 && c <= 122);
}

int __CDECL isdigit(int c) {
	return ((c >= 48 && c <= 57));
}

int __CDECL iswdigit(wint_t c) {
	return ((c >= 48 && c <= 57));
}

int __CDECL isxdigit(int c) {
	return (isdigit(c) || (c >= 65 && c <= 70) || (c >= 97 && c <= 102));
}

int __CDECL iswxdigit(wint_t c) {
	isxdigit(c);
}

int __CDECL isalnum(int c) {
	return (isalpha(c) || isdigit(c));
}

int __CDECL iswalnum(wint_t c) {
	return (isalpha(c) || iswdigit(c));
}

int __CDECL isspace(int c) {
	short int cx;
	for (cx = 0;cx < 6;cx++)
		if (c == (int)spacechars[cx]) return 1;
	return 0;
}

int __CDECL iswspace(wint_t c) {
	return isspace(c);
}

int __CDECL tolower(int c) {
	if (c >= 65 && c <= 90) return c + 32;
	return c;
}

int __CDECL towlower(wint_t  c) {
	if (c >= 65 && c <= 90) return c + 32;
	return c;
}

int __CDECL toupper(int c) {
	if (c >= 97 && c <= 122) return c - 32;
	return c;
}

int __CDECL towupper(wint_t  c) {
	if (c >= 97 && c <= 122) return c - 32;
	return c;
}

int __CDECL isascii(int c) {
	return (c < 0x7F);
}

int __CDECL iswascii(int c) {
	return (c < 0x7F);
}

int __CDECL islower(int c) {
	return ((c >= 97 && c <= 122));
}

int __CDECL isupper(int c) {
	return ((c >= 65 && c <= 90));
}

int __CDECL iswctype(wint_t ch, wctype_t type) {
	switch (type) {
		case _DIGIT:
			return iswdigit(ch);
/*		case _ALPHA:
			return isalpha(ch);
		case _ALNUM:
			return iswalnum (ch);
		case _SPACE:
			return iswspace (ch);
		case _UPPER:
			return iswupper (ch);
		case _XDIGIT:
			return iswxdigit (ch);
		case _LOWER:
			return iswlower (ch);

    case _BLANK:
      return iswblank (c);
    case WC_CNTRL:
      return iswcntrl (c);

    case WC_GRAPH:
      return iswgraph (c);

    case WC_PRINT:
      return iswprint (c);
    case WC_PUNCT:
      return iswpunct (c);

*/	  
    default:
      return 0; /* eliminate warning */
	}
	return 0;
}
