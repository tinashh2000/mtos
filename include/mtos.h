 #pragma once

//#pragma pack(push,1)
//#pragma pack(1)

#define _NOSTDIO
#define _NOSTDLIB

#define MTOS
#define __MTOS__
#define I386
#define BITS32

#include "_mtx_.h"

//ENDIAN(low,high);
//ENDIAN(low0,low1,high0,high1);
#ifndef BIGENDIAN

#define ENDIANX(a,b,c) (b << c | a);
#define ENDIAN16(a,b)				( b << 8 | a )
#define ENDIAN32(a,b,c,d)			( d << 24 | c << 16 | b << 8 | a )
#define ENDIAN64(a,b,c,d,e,f,g,h)	( h << 56 | g << 48 | f << 40 | e << 32 | d << 24 | c << 16 | b << 8 | a )

#define HIGH8(a,b) (a)
#define LOW8(a,b) (b)

#else

#define ENDIANX(a,b,c) (a << c | b);
#define ENDIAN16(a,b)				( a << 8 | b )
#define ENDIAN32(a,b,c,d)			( a << 24 | b << 16 | c << 8 | d )
#define ENDIAN64(a,b,c,d,e,f,g,h)	( a << 56 | b << 48 | c << 40 | d << 32 | e << 24 | f << 16 | g << 8 | h )

#define HIGH8(a,b) (b)
#define LOW8(a,b) (a)

#endif

#define ALIGN_X(addr,size) ((addr + size - 1) & ~(size-1))

// #define NULL    0

typedef struct {
    MEMPTR  StartAddress;
    MEMPTR  EndAddress;
} ADDRESS_RANGE;

typedef struct {
    MWORD   StartAddress;
    MWORD   EndAddress;
} IOPORT_RANGE;

typedef unsigned int		CHAR32;

typedef void    (*VOIDPROC)(void);
typedef void    (*INTHANDLER)(void);
typedef MWORD   (*MWORDPROC)(void);
typedef MEMPTR	CONTEXT;

//typedef int  (*QSORTPROC)(const void *, const void *);

int __CDECL 	_vsnwprintf (int);

#include <clib.h>
#include "x86/i386.h"
#include "thread/thread.h"
#include "mm/memory.h"
#include "events/events.h"
#include "time/time.h"
#include "ui/ui.h"
#include "devices/devices.h"
#include "stream/stream.h"

typedef void(*ATEXITPROC)(void);

#define DebugPrintStr //ugyu

//#pragma options align=reset
//#pragma pack(pop)

#define cprintf(str, ...) ;//

IMPORT int myvar;
