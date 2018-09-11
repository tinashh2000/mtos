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
*/
MWORD sListAppendLink(SLIST *slist, SLIST *item) {	//Append item to the queue
	SLIST *slistx = slist;
	if (slistx == item) return 0;
	while (slistx->forwardLink != 0) {
		if (slistx->forwardLink == (void*)item) { //if item already exists
			return 0;
		}

		if (slistx == slistx->forwardLink) { //if slist points to itself
			slistx->forwardLink = 0;	//make it point to nothing
			break;
		}

		slistx = slistx->forwardLink;
	}

	slistx->forwardLink = item;

	return 0;
}

/*

*/
MWORD sListDeleteLink(SLIST *slist, SLIST *item) {	//Delete item from the queue
	SLIST *slistx = slist;
	while (slistx->forwardLink != 0) {
		if (slistx->forwardLink == (void*)item) {
			if (item == (SLIST*)item->forwardLink)
				item->forwardLink = 0;

			slistx->forwardLink = item->forwardLink;
			item->forwardLink = 0;
			return 0;
		}
		if (slistx == slistx->forwardLink) {
			slistx->forwardLink = 0;
			return 0;
		}
		slistx = (SLIST*)slistx->forwardLink;
	}
	return 0;
}

SLIST *sListFindBackLink(SLIST *slist, SLIST *item) {
	SLIST *slistx = slist;
	while (slistx->forwardLink != 0) {
		if (slistx->forwardLink == (void*)item) {
			return slistx;
		}

		if (slistx == slistx->forwardLink) {
			slistx->forwardLink = 0;
			return 0;
		}

		slistx = (SLIST*)slistx->forwardLink;
	}
	return 0;
}
