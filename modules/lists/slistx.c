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
Add item to the end of the queue

Arguments:
IN
SLIST slist - the master link of the list
SLIST *item - the list to append
*/
MWORD	sListAppendLinkX(XLIST *xlist, SLIST *item) {

	SLIST *slistx;
	UINT32	nTimes = 0;
	if (xlist->listHead == 0) {	//If the head has nothing, this is the first item
		xlist->listHead = xlist->listTail = item;
		return 0;
	}

	if (xlist->listTail == 0)	//If the tail has nothing, (something wrong but..) find new tail
		slistx = (SLIST*)xlist->listHead;
	else
		slistx = (SLIST*)xlist->listTail;

	while (slistx->forwardLink != 0) {	//Look for tail

		if (slistx == slistx->forwardLink) { //if link points to itself
			slistx->forwardLink = 0;
			break;
		}

		slistx = (SLIST *)slistx->forwardLink;
		nTimes++;
		if (nTimes > xlist->numItems + 10)	//we recurse more than the numItems, this list is circular
			return 0;

	}

	slistx->forwardLink = item;
	item->forwardLink = 0;
	xlist->listTail = (void*)item;
	return 0;
}

MWORD	sListAppendItemX(XLIST *xlist, void *item) {

	void *slistx;
	UINT32	nTimes = 0;
	int itemSListOffset = xlist->listOffset;

	if (xlist->listHead == 0) {	//If the head has nothing, this is the first item
		xlist->listHead = xlist->listTail = item;
		return 0;
	}

	if (xlist->listTail == 0)	//If the tail has nothing, (something wrong but..) find new tail
		slistx = xlist->listHead;
	else
		slistx = xlist->listTail;

	while (SL_GETITEMFWDLINK(slistx,itemSListOffset) != 0) {	//Look for tail

		if (slistx == SL_GETITEMFWDLINK(slistx, itemSListOffset)) { //if link points to itself
			SL_GETITEMFWDLINK(slistx, itemSListOffset) = 0;
			break;
		}

		slistx = SL_GETITEMFWDLINK(slistx, itemSListOffset);
		nTimes++;
		if (nTimes > xlist->numItems + 10)	//we recurse more than the numItems, this list is circular
			return 0;

	}

	SL_GETITEMFWDLINK(slistx, itemSListOffset) = item;
	SL_GETITEMFWDLINK(item, itemSListOffset) = 0;
	xlist->listTail = item;
	return 0;
}

MWORD	sListDeleteItemX(XLIST *xlist, void *item) {

	void *slistx;
	UINT32	nTimes = 0;
	int itemSListOffset = xlist->listOffset;
	if (xlist->listHead == 0) return 0;	//If the head has nothing, this is the first item


	if (xlist->listHead == item) {
		if (xlist->listHead == SL_GETITEMFWDLINK(xlist->listHead, itemSListOffset))
			SL_GETITEMFWDLINK(xlist->listHead, itemSListOffset) = 0;

		xlist->listHead = SL_GETITEMFWDLINK(xlist->listHead, itemSListOffset);
		SL_GETITEMFWDLINK(xlist->listHead, itemSListOffset) = 0;
		xlist->numItems--;
		return 1;
	}

	slistx = xlist->listHead;

	while (SL_GETITEMFWDLINK(slistx, itemSListOffset) != 0) {	//Look for tail

		if (SL_GETITEMFWDLINK(slistx, itemSListOffset) == item) {
			if (item == SL_GETITEMFWDLINK(item, itemSListOffset)) SL_GETITEMFWDLINK(item, itemSListOffset) = 0;

			SL_GETITEMFWDLINK(slistx, itemSListOffset) = SL_GETITEMFWDLINK(item, itemSListOffset);
			SL_GETITEMFWDLINK(item, itemSListOffset) = 0;
			return 1;
		}

		if (slistx == SL_GETITEMFWDLINK(slistx, itemSListOffset)) { //if link points to itself
			SL_GETITEMFWDLINK(slistx, itemSListOffset) = 0;
			break;
		}

		slistx = SL_GETITEMFWDLINK(slistx, itemSListOffset);
		nTimes++;
		if (nTimes > xlist->numItems + 10)	//we recurse more than the numItems, this list is circular
			return 0;

	}
	return 0;
}

void *sListFindBackItemX(XLIST *xlist, void *item) {

	void *slistx;
	UINT32	nTimes = 0;
	int itemSListOffset = xlist->listOffset;
	if (xlist->listHead == 0) return 0;	//If the head has nothing, this is the first item


	if (xlist->listHead == item) {
		return 0;
	}

	slistx = xlist->listHead;

	while (SL_GETITEMFWDLINK(slistx, itemSListOffset) != 0) {	//Look for tail

		if (SL_GETITEMFWDLINK(slistx, itemSListOffset) == item) return slistx;

		if (slistx == SL_GETITEMFWDLINK(slistx, itemSListOffset)) { //if link points to itself
			SL_GETITEMFWDLINK(slistx, itemSListOffset) = 0;
			return 0;
		}

		slistx = SL_GETITEMFWDLINK(slistx, itemSListOffset);
		nTimes++;
		if (nTimes > xlist->numItems + 10)	//we recurse more than the numItems, this list is circular
			return 0;

	}
	return 0;
}