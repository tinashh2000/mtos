/*
* Copyright (C) 2017 Tinashe Mutandagayi
*
* This file is part of the MT-Operating System. The author(s) of this file is/are not 
* liable for any damages, loss or loss of information, deaths, sicknesses or other 
* bad things resulting from use of this file or software, either direct or indirect.
* Terms and conditions for use and distribution can be found in the license file named
* LICENSE.TXT. If you distribute this file or continue using it, 
* it means you understand and agree with the terms and conditions in the license file.
* binding this file.
*
* Happy Coding :)
*/

#include <stdio.h>
IMPORT const char HexTable[17];
wchar_t *utowc(unsigned int value, wchar_t *str, int radix) {
	int i, j;
	wchar_t c;

	if ((radix < 2) || (radix > 16))
	{
		str[0] = 0;
		return 0;
	}

	wchar_t *sx = &str[11];
	*sx = 0;

	do
	{
		*(--sx) = HexTable[value % radix];
		value = value / radix;
	} while (value != 0);

	wcscpy(str, sx);

	return str;
}

wchar_t *itowc(int i, wchar_t *dest, int radix)
{
   wchar_t *b = &dest[10];

   if ((radix < 2) || (radix > 16))
   {
	   dest[0] = 0;
	   return 0;
   }

   int   sign = (i < 0);

   if (sign) i = -i;

   *b = 0;

   do
   {
      *--b = '0' + (i % radix);
      i /= radix;
   }
   while (i);

   if (sign) *--b = '-';
   wcscpy(dest, b);
   return dest;
}
