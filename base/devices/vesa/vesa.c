#include "vesa.hxx"

	void VesaDrawPixelDummy(G_COR x, G_COR y, G_COLOR col) {
	}

	void VesaDrawPixel8(G_COR x, G_COR y, G_COLOR col)
	{
		VesaLinearBuffer8[y * VesaBytesPerScanLine + x] = (G_RGB8)col & 0xff;
	}

	void VesaDrawPixel16(G_COR x, G_COR y, G_COLOR col)
	{
		VesaLinearBuffer16[y*VesaBytesPerScanLine + x] = (G_RGB16)col & 0xffff;
	}

	void VesaDrawPixel24(G_COR x, G_COR y, G_COLOR col)
	{
		G_RGB24 *vl = &VesaLinearBuffer24[y*VesaBytesPerScanLine + x];
        *((UINT16*) vl) = ((UINT16) col);
        vl->b = *((BYTE*)(&col)+1);
	}

	void VesaDrawPixel32(G_COR x, G_COR y, G_COLOR col)
	{
        *((G_RGB32 *) (y*VesaBytesPerScanLine + BYTEPTR(VesaLinearBuffer) + x * sizeof(G_RGB32))) = (G_RGB32) col;
	}

    void VesaDrawBox8(G_COR dx, G_COR dy,G_COR bx, G_COR by,G_COR bwidth,G_COR bheight, PIXEL_DATA *pd){
    }

    void VesaDrawBox16(G_COR dx, G_COR dy,G_COR bx, G_COR by,G_COR bwidth,G_COR bheight, PIXEL_DATA *pd){
    }

	void VesaDrawBox24(G_COR dx, G_COR dy, G_COR bx, G_COR by, G_COR bwidth, G_COR bheight, PIXEL_DATA *pd) {
		INT32 y;
		UINT32 sw = pd->width * sizeof(G_COLOR);
		UINT32 bytespercopy = bwidth * sizeof(G_RGB24);

		if (LockX(&DrawLock,LockConC)) {
			char *dest  = BYTEPTR(VesaLinearBuffer) + ( dy * VesaBytesPerScanLine + (dx * sizeof(G_RGB24)) );
			char *src   = BYTEPTR(&pd->PData[by * pd->width + bx]);
			for (y = by; y < by + bheight; y++) {
				memcpy(dest,src,bytespercopy);
				dest = (dest + VesaBytesPerScanLine);
				src += sw;
			}
			Unlock(&DrawLock);
		}
	}

	void __CDECL memcpy_sse(MEMPTR dest, MEMPTR src, UINT32 numBytes);

    void VesaDrawBox32(G_COR dx, G_COR dy,G_COR bx, G_COR by,G_COR bwidth,G_COR bheight, PIXEL_DATA *pd)
	{
        INT32 y;
        UINT32 sw = pd->width * sizeof(G_COLOR);
        UINT32 bytespercopy = bwidth * sizeof(G_RGB32);

//		return;

		if (dx < 0 || dy < 0 || bx < 0 || by < 0 || bwidth < 0 || bheight < 0) {
			printf("Nuh");
			return;
		}

		if (bytespercopy > 0x1000000) {
			__asm int 3;
			printf("[[debug:bpc:%i,%i,%i,%i,%i,%i]]", dx,dy,bx,by,bwidth,bheight);
			while (1);
		}

		bytespercopy &= 0xfffff;
//		if (LockX(&DrawLock,LockConC)) {
		DisableInterrupts();
			char *dest  = BYTEPTR(VesaLinearBuffer) + ( dy * VesaBytesPerScanLine + (dx * sizeof(G_RGB32)) );
			char *src   = BYTEPTR(&pd->PData[by * pd->width + bx]);
			for (y = by; y < by + bheight; y++) {
				memcpy_opt(dest,src,bytespercopy);
				dest = (dest + VesaBytesPerScanLine);
				src += sw;
			}
		EnableInterrupts();
//			Unlock(&DrawLock);
//		}

	}

	void	VesaClearScreen() {
		char *dest = BYTEPTR(VesaLinearBuffer);
		memset_opt(dest, 0, VesaBytesPerScanLine * VesaHeight); 
	}

    void VesaInit() {
        VIDEO_PARAMS vp;

		InitLock(&DrawLock,"DrawLock");
        vbeM = &LoaderParams.vbeMode;

        VesaWidth = VesaGetVideoWidth();
        VesaHeight = VesaGetVideoHeight();
        VesaBPP = VesaGetVideoBitDepth();
        VesaBytesPerScanLine = VesaGetVideoBytesPerScanLine();
		VesaLinearBuffer = VesaGetLinearBufferAddress();

        VesaLinearBuffer8 =  (G_RGB8*) VesaLinearBuffer;
        VesaLinearBuffer16 = (G_RGB16*) VesaLinearBuffer;
        VesaLinearBuffer24 = (G_RGB24*) VesaLinearBuffer;
        VesaLinearBuffer32 = (G_RGB32*) VesaLinearBuffer;


		VesaLinearBufferSize = VesaGetLinearBufferSize();

        vp.width = VesaWidth;
        vp.height = VesaHeight;
        vp.BitsPerPixel = VesaBPP;
        vp.BytesPerScanLine = VesaBytesPerScanLine;

//		printf("<VesaLin:%x>",VesaLinearBuffer);
		switch (VesaBPP) {

			case 8:
				vp.SetPixel = (SETPIXELPROC)VesaDrawPixel8;
                vp.DrawBox = VesaDrawBox8;
				break;

			case 16:
				vp.SetPixel = (SETPIXELPROC)VesaDrawPixel16;
                vp.DrawBox = VesaDrawBox16;
				break;

			case 24:
				vp.SetPixel = (SETPIXELPROC)VesaDrawPixel24;
                vp.DrawBox = VesaDrawBox24;
				break;

			case 32:
				vp.SetPixel = (SETPIXELPROC)VesaDrawPixel32;
                vp.DrawBox = VesaDrawBox32;
				break;

			default:
				break;
		}
		
		SetVideoParams(&vp);
		bVesaInit = TRUE;

		return;

	}

G_COR  VesaGetVideoWidth() {
    return ((UINT32) vbeM->XResolution);
}

G_COR  VesaGetVideoHeight() {
    return ((UINT32) vbeM->YResolution);
}

UINT32  VesaGetVideoBitDepth() {
    return ((UINT32) vbeM->BitsPerPixel);
}

UINT32  VesaGetVideoBytesPerScanLine() {
    return ((UINT32) vbeM->BytesPerScanLine);
}

MEMPTR  VesaGetLinearBufferAddress() {
    return (MEMPTR) LoaderParams.vbeMode.PhysBasePtr;
}

UINT32  VesaGetLinearBufferSize() {
    return ((UINT32) vbeM->XResolution * (UINT32) vbeM->BytesPerScanLine * (UINT32) vbeM->YResolution) ;
}

