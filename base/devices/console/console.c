#include "console.h"
void ConsolePostPrint() {
    UINT32 pos = CD_GetNumRows(con) * CD_GetPosY(con) + CD_GetPosX(con);

    OutPortB(0x3D4,0x0F);
    OutPortB(0x3D5,pos & 0xFF);
    OutPortB(0x3D4,0x0E);
    OutPortB(0x3D5,(pos >> 8) & 0xFF);
}

void ConsoleInit() {
    con=&Console;
    CD_Init(con,CONSOLE_WIDTH,CONSOLE_HEIGHT,(CHRPTR) 0xB8000,CD_44FB,1);
    CD_SetColor(con, 7,  0);
    CD_ClearOutput(con);
    Console.PostPrint = ConsolePostPrint;
}

void ConsolePrintStrXY(UINT32 x,UINT32 y,char *str) {
    CHRPTR dest = (CHRPTR) 0xB8000 + (y * CONSOLE_WIDTH * 2) + (x * 2);
    while (*str != 0) {
        *dest = *str   ;
        str++;
        dest+=2;
    }
}

