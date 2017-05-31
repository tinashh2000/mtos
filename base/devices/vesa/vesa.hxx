#define _MTOX_SYS
#define _MTOX_UI

#include <mtox.h>
#include "vbe3.h"
#include "vesa.h"

MEMPTR	VesaLinearBuffer;
G_RGB8*		VesaLinearBuffer8;
G_RGB16*	VesaLinearBuffer16;
G_RGB24*	VesaLinearBuffer24;
G_RGB32*	VesaLinearBuffer32;

PVBEINFOBLOCK vbe;
PVBEMODEINFOBLOCK vbeMode;

UINT32  VesaWidth, VesaHeight, VesaBPP, VesaBytesPerScanLine, VesaLinearBufferSize;
BOOL bVesaInit;

LOCK	DrawLock;

//LoaderParams.vbeMode.PhysBasePtr
VBEMODEINFOBLOCK*   vbeM;

