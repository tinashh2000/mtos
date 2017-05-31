#include "vga.hxx"
void VGASetWritingMode(MWORD mode) {
    if (mode != VGAWritingMode) {
        OutPortW(0x3CE,0x1803);
    }
}

void VGAWaitRetrace() {
    while (inportb(0x3DA) & 8);
    while (inportb(0x3DA & 8) == 0);
}
