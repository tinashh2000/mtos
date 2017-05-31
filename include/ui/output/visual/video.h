#pragma once

typedef void(*SETPIXELPROC) (G_COR, G_COR, G_COLOR);
typedef G_COLOR(*GETPIXELPROC) (G_COR, G_COR);
typedef void(*DRAWBOXPROC)(G_COR dx, G_COR dy,G_COR bx, G_COR by,G_COR bwidth,G_COR bheight, PIXEL_DATA *pd);

typedef struct {
    UINT32  width;
    UINT32  height;
    UINT32  BitsPerPixel;
    UINT32  BytesPerScanLine;
    SETPIXELPROC  SetPixel;
    GETPIXELPROC  GetPixel;
	DRAWBOXPROC		DrawBox;
} VIDEO_PARAMS;


typedef void(*SETVIDEOPARAMS)(VIDEO_PARAMS *vp);


EXPORTSTART
G_COR  GetVideoWidth(void);
G_COR  GetVideoHeight(void);
void DrawPixel(G_COR x,G_COR y,G_COLOR col);
EXPORTEND
