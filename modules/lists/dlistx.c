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
DLIST dlist - the master link of the list
DLIST *item - the list to append
*/

#define dprintf //
MWORD	dListAppendLinkX(XLIST *xlist, DLIST *item) {

	DLIST *dlistx;
	UINT32	nTimes = 0;

	if (xlist->listHead == 0) {	//If the head has nothing, this is the first item
		xlist->listHead = xlist->listTail = (void*) item;
		item->backLink = item->forwardLink = 0;
		return 0;
	}

	if (xlist->listTail == 0)	//If the tail has nothing, (something wrong but..) find new tail
		dlistx = (DLIST*)xlist->listHead;
	else
		dlistx = (DLIST*)xlist->listTail;

	while (dlistx->forwardLink != 0) {	//Look for tail

		if (dlistx == dlistx->forwardLink) { //if link points to itself
			dlistx->forwardLink = 0;
			break;
		}

		dlistx = (DLIST *)dlistx->forwardLink;
		nTimes++;
		if (nTimes > xlist->numItems + 10) {	//we recurse more than the numItems, this list is circular
			return 0;
		}

	}

	dlistx->forwardLink = (void*)item;
	item->backLink = (void*)dlistx;
	item->forwardLink = 0;
	xlist->listTail = (void*)item;

	return 0;
}

MWORD	dListAppendItemAscX(XLIST *xlist, void *item) {

	void *dlistx;
	UINT32	nTimes = 0;
	int itemSListOffset = xlist->listOffset;

	if (xlist->listHead == 0) {	//If the head has nothing, this is the first item
		xlist->listHead = xlist->listTail = item;
		DL_GETITEMBACKLINK(item, itemSListOffset) = 0;
		DL_GETITEMFWDLINK(item, itemSListOffset) = 0;
		return 0;
	}

	if (xlist->listTail == 0)	//If the tail has nothing, (something wrong but..) find new tail
		dlistx = xlist->listHead;
	else
		dlistx = xlist->listTail;

	while (DL_GETITEMFWDLINK(dlistx, itemSListOffset) != 0) {	//Look for tail

		if (dlistx == DL_GETITEMFWDLINK(dlistx, itemSListOffset)) { //if link points to itself
			DL_GETITEMFWDLINK(dlistx, itemSListOffset) = 0;
			break;
		}

		dlistx = DL_GETITEMFWDLINK(dlistx, itemSListOffset);
		nTimes++;
		if (nTimes > xlist->numItems + 10)	//we recurse more than the numItems, this list is circular
			return 0;

	}

	DL_GETITEMFWDLINK(dlistx, itemSListOffset) = item;
	DL_GETITEMBACKLINK(item, itemSListOffset) = dlistx;
	DL_GETITEMFWDLINK(item, itemSListOffset) = 0;
	xlist->listTail = item;
	return 0;
}

MWORD	dListAppendItemX(XLIST *xlist, void *item) {

	if (item == 0 || xlist == 0) return 0;

	void *dlistx;
	UINT32	nTimes = 0;
	int itemSListOffset = xlist->listOffset;

	if (xlist->listHead == 0) {	//If the head has nothing, this is the first item
		xlist->listHead = xlist->listTail = item;
		DL_GETITEMBACKLINK(item, itemSListOffset) = 0;
		DL_GETITEMFWDLINK(item, itemSListOffset) = 0;
		xlist->numItems++;
		return 0;
	}

	if (xlist->listTail == 0)	//If the tail has nothing, (something wrong but..) find new tail
		dlistx = xlist->listHead;
	else
		dlistx = xlist->listTail;

	if (item == dlistx) { dprintf("\r\n<dup>"); return 0; };

	while (DL_GETITEMFWDLINK(dlistx, itemSListOffset) != 0) {	//Look for tail

		if (dlistx == DL_GETITEMFWDLINK(dlistx, itemSListOffset)) { //if link points to itself
			DL_GETITEMFWDLINK(dlistx, itemSListOffset) = 0;
			dprintf("<err@@>");
			break;
		}

		dlistx = DL_GETITEMFWDLINK(dlistx, itemSListOffset);

		if (item == dlistx) { dprintf("\r\n<dup>"); return 0; };

		nTimes++;
		if (nTimes > xlist->numItems + 10)	//we recurse more than the numItems, this list is circular
			return 0;

	}

	DL_GETITEMFWDLINK(dlistx, itemSListOffset) = item;
	DL_GETITEMBACKLINK(item , itemSListOffset) = dlistx;
	DL_GETITEMFWDLINK(item, itemSListOffset) = 0;
	xlist->listTail = item;
	xlist->numItems++;
	return 0;
}

int hasDup = 0;
MWORD	dListAppendItemCompareX(XLIST *xlist, void *item) {
	
	if (item == 0 || xlist == 0) return 0;
	void *dlistx, *nextx=0;
	UINT32	nTimes = 0;
	UINT16	compareOffset = xlist->compareOffset;
	UINT32	compareValue = DL_GETITEMCMPVALUE(item, compareOffset);
	int itemSListOffset = xlist->listOffset;

//	BOOL	isThread = I_THREAD(item)->Signature == THREAD_SIGNATURE  ? TRUE: FALSE;

#ifdef _DLIST_DEB
	dprintf("\r\n    ad:{%x,%x}",item, xlist);
#endif

	if (xlist->listHead == 0) {	//If the head has nothing, this is the first item
		xlist->listHead = xlist->listTail = item;
		DL_GETITEMBACKLINK(item, itemSListOffset) = 0;
		DL_GETITEMFWDLINK(item, itemSListOffset) = 0;
		xlist->numItems++;
		return TRUE;
	}

	dlistx = xlist->listHead;

	if (item == dlistx) {
/*
		dprintf("\r\n     adup!:%s,%x,%x", xlist->listName, item, xlist);

		hasDup = 1;
		__asm cli;
		while (1);*/
		return FALSE;
	};

	while (compareValue >= DL_GETITEMCMPVALUE(dlistx, compareOffset) && DL_GETITEMFWDLINK(dlistx, itemSListOffset) != 0) {	//Look for tail

		if (dlistx == DL_GETITEMFWDLINK(dlistx, itemSListOffset)) { //if link points to itself
			DL_GETITEMFWDLINK(dlistx, itemSListOffset) = 0;
			dprintf("<<err!!:%x>>", dlistx);

			break;
		}

		dlistx = DL_GETITEMFWDLINK(dlistx, itemSListOffset);

		if (item == dlistx) {
/*			dprintf("\r\n     adup@:%s:%x,%x", xlist->listName, item, xlist);
			hasDup = 1;
			__asm cli;
			while (1);
			*/return FALSE;
		};

		nTimes++;
		if (nTimes > xlist->numItems + 10) {	//we recurse more than the numItems, this list is circular
			dprintf("~<%i>", xlist->numItems);
			nTimes = 0;
		}
	}

	if (compareValue >= DL_GETITEMCMPVALUE(dlistx, compareOffset)) {	//if compare value >= dlist value, insert after
		DL_GETITEMFWDLINK(item, itemSListOffset) = DL_GETITEMFWDLINK(dlistx, itemSListOffset);	//item->fwd = dlist->fwd
		DL_GETITEMBACKLINK(item, itemSListOffset) = dlistx;	//item->back = dlistx
		DL_GETITEMFWDLINK(dlistx, itemSListOffset) = item;	//dlist->fwd = item

		if (dlistx == xlist->listTail) 	//check if dlistx was tail and update tail 
			xlist->listTail = item;
	}
	else {	//otherwise insert before

		if (dlistx == xlist->listHead)
			xlist->listHead = item;

		void *backLink = DL_GETITEMBACKLINK(dlistx, itemSListOffset);
		if (backLink != 0)
			DL_GETITEMFWDLINK(backLink, itemSListOffset) = item;

		DL_GETITEMFWDLINK(item, itemSListOffset) = dlistx;	//item->fwd = dlist
		DL_GETITEMBACKLINK(item, itemSListOffset) = DL_GETITEMBACKLINK(dlistx, itemSListOffset);	//item->back = dlistx->back
		DL_GETITEMBACKLINK(dlistx, itemSListOffset) = item;	//dlist->back = item
	}

	xlist->numItems++;
	return TRUE;
}

MWORD	dListAppendItemAfterX(XLIST *xlist, void *item, void *afterItem) {

	if (item == 0 || xlist == 0 || afterItem == 0) return 0;

	void *dlistx;
	UINT32	nTimes = 0;
	int itemSListOffset = xlist->listOffset;

	if (xlist->listHead == 0) {	//If the head has nothing, this is the first item
		xlist->listHead = xlist->listTail = item;
		DL_GETITEMBACKLINK(item, itemSListOffset) = 0;
		DL_GETITEMFWDLINK(item, itemSListOffset) = 0;
		xlist->numItems++;
		return 0;
	}

	dlistx = xlist->listHead;

	while (dlistx != afterItem && DL_GETITEMFWDLINK(dlistx, itemSListOffset) != 0) {	//Look for tail

		if (dlistx == DL_GETITEMFWDLINK(dlistx, itemSListOffset)) { //if link points to itself
			DL_GETITEMFWDLINK(dlistx, itemSListOffset) = 0;
			break;
		}

		dlistx = DL_GETITEMFWDLINK(dlistx, itemSListOffset);
		nTimes++;
		if (nTimes > xlist->numItems + 10)	//we recurse more than the numItems, this list is circular
			return 0;

	}

	DL_GETITEMFWDLINK(item, itemSListOffset) = DL_GETITEMFWDLINK(dlistx, itemSListOffset);	//item->fwd = dlist->fwd
	DL_GETITEMBACKLINK(item, itemSListOffset) = dlistx;	//item->back = dlistx
	DL_GETITEMFWDLINK(dlistx, itemSListOffset) = item;	//dlist->fwd = item
	xlist->listTail = item;
	xlist->numItems++;

	return 0;
}

MWORD	dListDeleteItemX(XLIST *xlist, void *item) {

	if (item == 0 || xlist == 0) return 0;

	void *dlistx;
	UINT32	nTimes = 0;
	int itemSListOffset = xlist->listOffset;
	if (xlist->listHead == 0) return 0;	//If the head has nothing, this is the first item

	if (hasDup) {
#ifdef _DLIST_DEB
		dprintf("\r\n   {#:%x}", item);
#endif
	}
	hasDup = 0;

#ifdef _DLIST_DEB
	dprint("\r\n   {$del:%x,%x}", item, xlist);
#endif

	if (xlist->listHead == item) {
		if (xlist->listHead == DL_GETITEMFWDLINK(xlist->listHead, itemSListOffset)) {
			DL_GETITEMFWDLINK(xlist->listHead, itemSListOffset) = 0;
			xlist->listHead = 0;
			xlist->numItems = 0;

#ifdef _DLIST_DEB

			dlistx = xlist->listHead;
			do {
				dprint("{dl:%x, %x, %x}", dlistx, DL_GETITEMFWDLINK(dlistx, itemSListOffset), DL_GETITEMBACKLINK(dlistx, itemSListOffset));
			} while (DL_GETITEMFWDLINK(dlistx, itemSListOffset) != 0);	//Look for tail
#endif

			return 1;
		}
		xlist->listHead = DL_GETITEMFWDLINK(xlist->listHead, itemSListOffset);
//		DL_GETITEMFWDLINK(xlist->listHead, itemSListOffset) = 0;
		DL_GETITEMBACKLINK(xlist->listHead, itemSListOffset) = 0;
		xlist->numItems--;

#ifdef _DLIST_DEB
		dlistx = xlist->listHead;
		do {
			dprint("{dl:%x, %x, %x}", dlistx, DL_GETITEMFWDLINK(dlistx, itemSListOffset), DL_GETITEMBACKLINK(dlistx, itemSListOffset));
		} while (DL_GETITEMFWDLINK(dlistx, itemSListOffset) != 0);	//Look for tail
#endif

		return 1;
	}

	dlistx = xlist->listHead;

	while (DL_GETITEMFWDLINK(dlistx, itemSListOffset) != 0) {	//Look for tail

		if (DL_GETITEMFWDLINK(dlistx, itemSListOffset) == item) {
			if (item == DL_GETITEMFWDLINK(item, itemSListOffset)) DL_GETITEMFWDLINK(item, itemSListOffset) = 0;

			DL_GETITEMFWDLINK(dlistx, itemSListOffset) = DL_GETITEMFWDLINK(item, itemSListOffset);
			DL_GETITEMFWDLINK(item, itemSListOffset) = 0;

			if (item == xlist->listTail)
				xlist->listTail = dlistx;

			xlist->numItems--;

#ifdef _DLIST_DEB
			dlistx = xlist->listHead;
			do {
				dprint("{dl:%x, %x, %x}", dlistx, DL_GETITEMFWDLINK(dlistx, itemSListOffset), DL_GETITEMBACKLINK(dlistx, itemSListOffset));
			} while (DL_GETITEMFWDLINK(dlistx, itemSListOffset) != 0);	//Look for tail
#endif

			return 1;
		}

		if (dlistx == DL_GETITEMFWDLINK(dlistx, itemSListOffset)) { //if link points to itself
			DL_GETITEMFWDLINK(dlistx, itemSListOffset) = 0;
			break;
		}

		dlistx = DL_GETITEMFWDLINK(dlistx, itemSListOffset);
		nTimes++;
		if (nTimes > xlist->numItems + 10) {	//we recurse more than the numItems, this list is circular
			nTimes = 0;
		}

	}

#ifdef _DLIST_DEB
	dprint("\r\n   #{del:%x, %x}",item, xlist);
	dlistx = xlist->listHead;
	do {
		dprint("{dl:%x, %x, %x}", dlistx, DL_GETITEMFWDLINK(dlistx, itemSListOffset), DL_GETITEMBACKLINK(dlistx, itemSListOffset));
	}
	while (DL_GETITEMFWDLINK(dlistx, itemSListOffset) != 0);	//Look for tail
#endif
	
	return 0;
}
