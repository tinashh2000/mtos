#pragma once

EXPORTSTART

	void VesaInit(void);
	G_COR   VesaGetVideoWidth(void);
	G_COR   VesaGetVideoHeight(void);
	UINT32  VesaGetVideoBitDepth(void);
	UINT32  VesaGetVideoBytesPerScanLine(void);
	MEMPTR  VesaGetLinearBufferAddress(void);
	UINT32  VesaGetLinearBufferSize(void);

	void VesaDrawPixelDummy(G_COR x, G_COR y, G_COLOR col);

	void VesaDrawPixel8(G_COR x, G_COR y, G_COLOR col);
	void VesaDrawPixel16(G_COR x, G_COR y, G_COLOR col);
	void VesaDrawPixel24(G_COR x, G_COR y, G_COLOR col);
	void VesaDrawPixel32(G_COR x, G_COR y, G_COLOR col);

	void VesaDrawBox8(G_COR dx, G_COR dy,G_COR bx, G_COR by,G_COR bwidth,G_COR bheight, PIXEL_DATA *pd);
	void VesaDrawBox16(G_COR dx, G_COR dy,G_COR bx, G_COR by,G_COR bwidth,G_COR bheight, PIXEL_DATA *pd);
	void VesaDrawBox24(G_COR dx, G_COR dy,G_COR bx, G_COR by,G_COR bwidth,G_COR bheight, PIXEL_DATA *pd);
	void VesaDrawBox32(G_COR dx, G_COR dy,G_COR bx, G_COR by,G_COR bwidth,G_COR bheight, PIXEL_DATA *pd);

EXPORTEND

extern struct _LOADER_PARAMS LoaderParams;
