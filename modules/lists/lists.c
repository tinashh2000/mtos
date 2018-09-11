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

#include <lists/lists.h>

/*

Append item to tail of sList
itemSListOffset is the offset from the beginning of the void *slist to where the SLIST structure actually resides.
The void*slist is not an SLIST* itself but within the void* must reside the SLIST*

*/
MWORD	sListAppendItem(void *slist, void *item, int itemSListOffset) {
	void *slistx = slist;
	if (slist == item) return 0;

	while (SL_GETITEMFWDLINK(slistx, itemSListOffset) != 0) {	//if slist has forward link
		if (slistx == SL_GETITEMFWDLINK(slistx, itemSListOffset)) {//if slist points to itself
			SL_GETITEMFWDLINK(slistx, itemSListOffset) = 0;	//remove forward link
			return 0;
		}
		slistx = SL_GETITEMFWDLINK(slistx, itemSListOffset);
	}

	SL_GETITEMFWDLINK(slistx, itemSListOffset) = item;
	SL_GETITEMFWDLINK(item, itemSListOffset) = 0;
	return 0;
}

/*
We transverse because its a single list, we dont know the predecessor of an item, we must remove the item's forward link from the predecessor's SLIST
*/
BOOL	sListDeleteItem(void *slist, void *item, int itemSListOffset) {	//Delete item from the queue
	void*slistx = slist;
	while (SL_GETITEMFWDLINK(slistx, itemSListOffset) != 0) {

		if (SL_GETITEMFWDLINK(slistx, itemSListOffset) == item) {
			if (SL_GETITEMFWDLINK(item, itemSListOffset) == item) //if item points toself. it must point to 0
				SL_GETITEMFWDLINK(item, itemSListOffset) = 0;

			SL_GETITEMFWDLINK(slistx, itemSListOffset) = SL_GETITEMFWDLINK(item, itemSListOffset); //slistx->forwardLink = item->forwardLink
			SL_GETITEMFWDLINK(item, itemSListOffset) = 0;
			return TRUE;
		}

		if (slistx == SL_GETITEMFWDLINK(slistx, itemSListOffset)) return 0;

		slistx = SL_GETITEMLIST(slistx, itemSListOffset);
	}
	return FALSE;
}

void *sListFindBackItem(void *slist, void *item, int itemSListOffset) {
	void *slistx = slist;
	while (SL_GETITEMFWDLINK(slistx, itemSListOffset) != 0) {
		if (SL_GETITEMFWDLINK(slistx, itemSListOffset) == item) {
			return slistx;
		}

		if (slistx == SL_GETITEMFWDLINK(slistx, itemSListOffset)) {
			SL_GETITEMFWDLINK(slistx, itemSListOffset) = 0;
			return 0;
		}

		slistx = SL_GETITEMFWDLINK(slistx, itemSListOffset);
	}
	return 0;
}
