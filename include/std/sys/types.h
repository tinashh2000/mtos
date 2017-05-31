
#pragma once

#ifndef __clockid_t_defined
#define __clockid_t_defined
typedef unsigned long clockid_t;
#endif

#ifndef _CLOCK_T_DEFINED
#define _CLOCK_T_DEFINED
typedef unsigned int clock_t;
#endif /* _CLOCK_T_DEFINED */

#ifndef _TIME_T_DEFINED
#define _TIME_T_DEFINED
typedef unsigned long time_t;
#endif /* _TIME_T_DEFINED */

#ifndef _SUSECONDS_T_DEFINED
#define _SUSECONDS_T_DEFINED
typedef signed long _suseconds_t;
#ifdef __POCC__OLDNAMES
typedef signed long suseconds_t;
#endif /* __POCC__OLDNAMES */
#endif /* _SUSECONDS_T_DEFINED */

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#if __POCC_TARGET__ == 3
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif /* __POCC_TARGET__ */
#endif /* _SIZE_T_DEFINED */

#ifndef _SSIZE_T_DEFINED
#define _SSIZE_T_DEFINED
#if __POCC_TARGET__ == 3
typedef long long _ssize_t;
#else
typedef int _ssize_t;
#endif /* __POCC_TARGET */
#ifdef __POCC__OLDNAMES
#if __POCC_TARGET__ == 3
typedef long long ssize_t;
#else
typedef long ssize_t;
#endif /* __POCC_TARGET */
#endif /* __POCC__OLDNAMES */
#endif /* SSIZE_T_DEFINED */

#ifndef _DEV_T_DEFINED
#define _DEV_T_DEFINED
typedef unsigned int _dev_t;
typedef unsigned int dev_t;
#endif /* _DEV_T_DEFINED */

#ifndef _INO_T_DEFINED
#define _INO_T_DEFINED
typedef unsigned short _ino_t;
typedef unsigned short ino_t;
#endif /* _INO_T_DEFINED */

#ifndef _OFF_T_DEFINED
#define _OFF_T_DEFINED
#if __POCC_TARGET__ == 3
typedef long long _off_t;
#else
typedef long _off_t;
#endif /* __POCC_TARGET */
#ifdef __POCC__OLDNAMES
#if __POCC_TARGET__ == 3
typedef long long off_t;
#else
typedef long off_t;
#endif /* __POCC_TARGET */
#endif /* __POCC__OLDNAMES */
#endif /* _OFF_T_DEFINED */

#ifndef _PID_T_DEFINED
#define _PID_T_DEFINED
#if __POCC_TARGET__ == 3
typedef long long _pid_t;
#else
typedef int _pid_t;
#endif /* __POCC_TARGET */
#ifdef __POCC__OLDNAMES
#if __POCC_TARGET__ == 3
typedef long long pid_t;
#else
typedef int pid_t;
#endif /* __POCC_TARGET */
#endif /* __POCC__OLDNAMES */
#endif /* _PID_T_DEFINED */

#ifndef _TIME32_T_DEFINED
typedef int32 __time32_t;
#define _TIME32_T_DEFINED
#endif

#ifndef _TIME64_T_DEFINED
typedef __int64 __time64_t;
#define _TIME64_T_DEFINED
#endif

#ifndef _TIME_T_DEFINED
/* FIXME __STRICT_ANSI__ ! */

#if defined(_USE_32BIT_TIME_T)
typedef	__time32_t time_t;
#else

typedef	__time64_t time_t;
#endif /* _USE_32BIT_TIME_T */

#define _TIME_T_DEFINED
#endif


#ifndef	_OFF_T_
#define	_OFF_T_
typedef long _off_t;
#ifndef __STRICT_ANSI__
typedef _off_t	off_t;
#endif /* __STRICT_ANSI__ */
#endif	/* Not _OFF_T_ */

#ifndef _OFF64_T_
#define _OFF64_T_
typedef __int64 _off64_t;
#ifndef __STRICT_ANSI__
typedef __int64 off64_t;
#endif /* __STRICT_ANSI__ */
#endif /* ndef _OFF64_T */

#ifndef _DEV_T_
#define	_DEV_T_
typedef unsigned int _dev_t;

#ifndef	_NO_OLDNAMES
typedef _dev_t	dev_t;
#endif
#endif	/* Not _DEV_T_ */


#ifndef _PID_T_
#define	_PID_T_
typedef int	_pid_t;
#endif

#ifndef	_NO_OLDNAMES
typedef _pid_t	pid_t;
#endif	/* Not _PID_T_ */


#ifndef _MODE_T_
#define	_MODE_T_
typedef unsigned short _mode_t;

#ifndef	_NO_OLDNAMES
typedef _mode_t	mode_t;
#endif
#endif	/* Not _MODE_T_ */


#ifndef _SIGSET_T_
#define	_SIGSET_T_
typedef int	_sigset_t;

#ifndef	_NO_OLDNAMES
typedef _sigset_t	sigset_t;
#endif
#endif	/* Not _SIGSET_T_ */

#ifndef _SSIZE_T_
#define _SSIZE_T_
typedef int _ssize_t;

#ifndef	_NO_OLDNAMES
typedef _ssize_t ssize_t;
#endif
#endif /* Not _SSIZE_T_ */

#ifndef _FPOS64_T_
#define _FPOS64_T_
typedef long long fpos64_t;
#endif

#ifndef _OFF64_T_
#define _OFF64_T_
typedef long long off64_t;
#endif

#if !defined __NO_ISOCEXT
typedef unsigned int useconds_t;
#endif  /* Not __NO_ISOCEXT */
