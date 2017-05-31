#ifndef _SYS_STAT_H
#define _SYS_STAT_H

/* sys/stat.h - private header for file status definitions */

#pragma once
#include <mtos.h>
#include <sys/types.h>

/* type definitions */
#ifndef _TIME_T_DEFINED
#define _TIME_T_DEFINED
typedef unsigned long time_t;
#endif

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#endif

#ifndef _STAT_DEFINED
#define _STAT_DEFINED
struct _stat {
    _dev_t st_dev;
    _ino_t st_ino;
    unsigned short st_mode;
    short st_nlink;
    short st_uid;
    short st_gid;
    _dev_t st_rdev;
    _off_t st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
};

struct stat {
    dev_t st_dev;
    ino_t st_ino;
    unsigned short st_mode;
    short st_nlink;
    short st_uid;
    short st_gid;
    dev_t st_rdev;
    off_t st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
};
#endif /* _STAT_DEFINED */

#define _S_ISDIR(m)  ((m) & _S_IFDIR)
#define _S_ISCHR(m)  ((m) & _S_IFCHR)
#define _S_ISFIFO(m)  ((m) & _S_IFIFO)
#define _S_ISREG(m)  ((m) & _S_IFREG)
#define _S_ISBLK(m)  ((m) & 0)
#define _S_ISLNK(m)  ((m) & 0)
#define _S_ISSOCK(m)  ((m) & 0)

#define _S_IFMT    0xF000
#define _S_IFDIR   0x4000
#define _S_IFCHR   0x2000
#define _S_IFIFO   0x1000
#define _S_IFREG   0x8000
#define _S_IREAD   0x100
#define _S_IWRITE  0x80
#define _S_IEXEC   0x40

/* declarations */
int __CDECL _fstat(int, struct _stat *);
int __CDECL _stat(const char *, struct _stat *);
int __CDECL _wstat(const wchar_t *, struct _stat *);

/* compatibility names */
#define S_ISDIR(m)  _S_ISDIR(m)
#define S_ISCHR(m)  _S_ISCHR(m)
#define S_ISFIFO(m)  _S_ISFIFO(m)
#define S_ISREG(m)  _S_ISREG(m)
#define S_ISBLK(m)  _S_ISBLK(m)
#define S_ISLNK(m)  _S_ISLNK(m)
#define S_ISSOCK(m)  _S_ISSOCK(m)

#define S_IFMT  _S_IFMT
#define S_IFDIR  _S_IFDIR
#define S_IFCHR  _S_IFCHR
#define S_IFIFO  _S_IFIFO
#define S_IFREG  _S_IFREG
#define S_IREAD  _S_IREAD
#define S_IWRITE  _S_IWRITE
#define S_IEXEC  _S_IEXEC

EXPORTSTART
int __CDECL fstat(int, struct stat *);
int __CDECL stat(const char *, struct stat *);
EXPORTEND
#endif /* _SYS_STAT_H */
