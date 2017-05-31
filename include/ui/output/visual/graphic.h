#pragma once

typedef INT32	G_COR;
typedef INT32	G_CORSHORT;
typedef UINT32	G_COLOR;


enum {
	FONT_BOLD		= 1,
	FONT_UNDERLINE	= 2,
	FONT_ITALIC		= 4
};

typedef BYTE G_RGB8;
typedef INT16 G_RGB16;
typedef struct {
    BYTE    r;
    BYTE    g;
    BYTE    b;
} G_RGB24;
typedef UINT32 G_RGB32;

typedef struct {
    union {
        G_RGB8  c8;
        G_RGB16 c16;
        G_RGB24 c24;
        G_RGB32 c32;
    };
} G_COLX;


typedef union {
    UINT32	rgba;
    struct {
		BYTE r;
		BYTE g;
		BYTE b;
        BYTE alpha;
    } _RGBA;
} G_COLOREX;

typedef struct {
	DWORD	type;
	DWORD	bits;
	MEMPTR	adapterString;
	MEMPTR	deviceString;
} G_DEVICE;

typedef struct {
	UINT32	fontFlags;
	G_COLOR	fontColor;
	G_COLOR	fontOutlineColor;
	MEMPTR	fontName;
} G_FONT;

typedef struct {
	G_COR		x;
	G_COR		y;
	UINT32		width;
	UINT32		height;
	G_DEVICE	device;
	G_COLOR		outline;
	G_COLOR		backColor;
	G_COLOR		foreColor;
	G_FONT		font;
	UINT32		flags;
} G_DRAW;

typedef struct {
	G_COR	x;
	G_COR	y;
	UINT32	width;
	UINT32	height;
} G_RECT;

typedef struct {
	G_COR	x;
	G_COR	y;
} G_POINTS;

#define GetRValue(rgb)  ((rgb >> 16) & 0xff)
#define GetGValue(rgb)  ((rgb >> 8) & 0xff)
#define GetBValue(rgb)  ((rgb) & 0xff)
#define RGB(r,g,b)  (r << 16 | g < 8 | b)
#define RGBA(r,g,b,a)  (a << 24 | r << 16 | g < 8 | b)
#define PUTALPHA(a,rgb) ((a <<24) | (rgb &0xFFFFFF))

#define WHITE	RGBA(255,255,255,0)
#define RED		RGBA(255,0,0,0)
#define GREEN	RGBA(0,255,0,0)
#define BLUE	RGBA(0,0,255,0)

typedef struct {

    G_COR  width;
    G_COR  height;
    G_COLOR mask;
	G_COLOR PData[];

} PIXEL_DATA;


//typedef	MWORD	G_DRAW;
//typedef	MWORD	G_DEVICE;

#define G_DRAWFILL	=	1
#define G_OUTLINE	=	2

#define MASK_COLOR 0xff000000

