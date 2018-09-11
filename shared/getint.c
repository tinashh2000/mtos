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