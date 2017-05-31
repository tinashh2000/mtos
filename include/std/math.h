#pragma once

#define _STRING_H_
//#define __midl
#ifndef _MTOX_COMMON_
#include "_mtx_.h"
#endif

#define FP_NAN		0x0100
#define FP_NORMAL	0x0400
#define FP_INFINITE	(FP_NAN | FP_NORMAL)
#define FP_ZERO		0x4000
#define FP_SUBNORMAL	(FP_NORMAL | FP_ZERO)

struct _exception
{
	int	type;
	char	*name;
	double	arg1;
	double	arg2;
	double	retval;
};

EXPORTSTART

float __CDECL sinf (float);
long double __CDECL sinl (long double);

float __CDECL cosf (float);
long double __CDECL cosl (long double);

float __CDECL tanf (float);
long double __CDECL tanl (long double);

float __CDECL asinf (float);
long double __CDECL asinl (long double);

float __CDECL acosf (float);
long double __CDECL acosl (long double);

float __CDECL atanf (float);
long double __CDECL atanl (long double);

float __CDECL atan2f (float, float);
long double __CDECL atan2l (long double, long double);

/* 7.12.5 Hyperbolic functions: Double in C89  */
float __CDECL sinhf (float);

long double __CDECL sinhl (long double);

float __CDECL coshf (float);
long double __CDECL coshl (long double);

float __CDECL tanhf (float);

long double __CDECL tanhl (long double);


        int     __CDECL abs(int);
        double  __CDECL acos(double);
        double  __CDECL asin(double);
        double  __CDECL atan(double);
        double  __CDECL atan2(double, double);
        double  __CDECL cos(double);
        double  __CDECL cosh(double);
        double  __CDECL exp(double);
        double  __CDECL fabs(double);
        double  __CDECL fmod(double, double);
        long    __CDECL labs(long);
        double  __CDECL log(double);
        double  __CDECL log10(double);
        double  __CDECL pow(double, double);
        double  __CDECL sin(double);
        double  __CDECL sinh(double);
        double  __CDECL tan(double);
        double  __CDECL tanh(double);
        double  __CDECL sqrt(double);


double __CDECL trunc (double);
float __CDECL truncf (float);
long double __CDECL truncl (long double);
		
double __CDECL ceil (double);
double __CDECL floor (double);
double __CDECL ldexp (double, int);
double __CDECL frexp (double, int*);

float __CDECL fabsf (float x);
long double __CDECL fabsl (long double x);

double __CDECL modf (double, double*);
float __CDECL ceilf (float);

float __CDECL floorf (float);
long double __CDECL floorl (long double);

float __CDECL sqrtf (float);
long double __CDECL sqrtl (long double);

float __CDECL powf (float, float);
long double __CDECL powl (long double, long double);

float       __CDECL nextafterf( float from, float to );
double      __CDECL nextafter( double from, double to );
long double __CDECL nextafterl( long double from, long double to );
float       __CDECL nexttowardf( float from, long double to );
double      __CDECL nexttoward( double from, long double to );
long double __CDECL nexttowardl( long double from, long double to );


float       __CDECL truncf( float arg );
double      __CDECL trunc( double arg );
long double __CDECL truncl( long double arg );

int __CDECL __fpclassify( double x );
EXPORTEND