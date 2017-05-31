#include <mtos.h>

int __CDECL  putchar(int character) {
	return PrintChar(character);
}

int __CDECL puts(const char*str) {
    return PrintStr((CHARPTR)str);
}
