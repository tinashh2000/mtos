#include <mtos.h>

typedef struct _KONTEXT {
	MWORD	type;
	MWORD	state;

} KONTEXT;

CONTEXT* CreateContext(MWORD type) {
	return 0;
}