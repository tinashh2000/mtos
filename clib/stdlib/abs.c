#include <mtos.h>

int __CDECL abs (int i) {
  return (i < 0) ? -i : i;
}

long int __CDECL labs (long int i) {
  return (i < 0) ? -i : i;
}

long long __CDECL llabs (long long i) {
  return (i < 0) ? -i : i;
}

/*
float __CDECL fabsf(float value) {
	return value < 0.0f ? -value:value;
}
*/