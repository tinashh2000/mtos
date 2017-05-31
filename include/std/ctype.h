#pragma once

#define _UPPER          0x1     /* upper case letter */
#define _LOWER          0x2     /* lower case letter */
#define _DIGIT          0x4     /* digit[0-9] */
#define _SPACE          0x8     /* space, tab, carriage return, newline, */
                                /* vertical tab or form feed */
#define _PUNCT          0x10    /* punctuation character */
#define _CONTROL        0x20    /* control character */
#define _BLANK          0x40    /* space char (tab handled separately) */
#define _HEX            0x80    /* hexadecimal digit */

#define _LEADBYTE       0x8000                  /* multibyte leadbyte */
#define _ALPHA          (0x0100|_UPPER|_LOWER)  /* alphabetic character */
#define _ALNUM			_ALPHA | _DIGIT
#define _XDIGIT			_HEX | _DIGIT

EXPORTSTART
	int __CDECL isalnum(int);
	int __CDECL isalpha(int);
	int __CDECL iscntrl(int);
	int __CDECL isdigit(int);
	int __CDECL isgraph(int);
	int __CDECL islower(int);
	int __CDECL isprint(int);
	int __CDECL ispunct(int);
	int __CDECL isspace(int);
	int __CDECL isblank(int);
	int __CDECL isupper(int);
	int __CDECL isxdigit(int);
	int __CDECL isascii(int);
	int __CDECL tolower(int);
	int __CDECL toupper(int);
	int __CDECL _toascii(int);
	int __CDECL iswascii(int c);
//	int __CDECL towupper(int c) ;
//	int __CDECL towlower(int c);
EXPORTEND