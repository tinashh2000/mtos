#include <mtos.h>

int __CDECL atexit (void (*func)(void)) {
		return 0;
}

void	__CDECL exit(int status) {
	//DestroyProcess(status);
	return;
}
