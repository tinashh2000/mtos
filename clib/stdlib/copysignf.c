/* copysignf function */
#include "math.h"

float __cdecl copysignf(float x, float y)
{	/* copy sign from y to x */
	union  intfloat {
		unsigned int	intVal;
		float			floatVal;
	};
	
	union intfloat* xv = &x;
	union intfloat* yv = &y;

	xv->intVal = (xv->intVal & 0x7fffffff) | (yv->intVal & 0x80000000);
	return (xv->floatVal);
}

