#pragma once

#include <mtos.h>
#define CONSOLE_WIDTH   80
#define CONSOLE_HEIGHT  50

CHAR_DEVICE  Console;
CHAR_DEVICE* con;

EXPORTSTART
    void ConsoleInit();
    void ConsolePrintStrXY(UINT32 x,UINT32 y,char *str);
EXPORTEND

