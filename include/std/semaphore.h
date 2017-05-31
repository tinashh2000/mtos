/* Linuxthreads - a simple clone()-based implementation of Posix        */
/* threads for Linux.                                                   */
/* Copyright (C) 1996 Xavier Leroy (Xavier.Leroy@inria.fr)              */
/*                                                                      */
/* This program is free software; you can redistribute it and/or        */
/* modify it under the terms of the GNU Library General Public License  */
/* as published by the Free Software Foundation; either version 2       */
/* of the License, or (at your option) any later version.               */
/*                                                                      */
/* This program is distributed in the hope that it will be useful,      */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/* GNU Library General Public License for more details.                 */

#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H    1

#include <sys/types.h>
/* Thread descriptors.  Needed for `sem_t' definition.  */
typedef struct _pthread_descr_struct *_pthread_descr;
# define _PTHREAD_DESCR_DEFINED

/* System specific semaphore definition.  */
typedef struct
{
  int __sem_value;
} sem_t;



/* Value returned if `sem_open' failed.  */
#define SEM_FAILED	((sem_t *) 0)

/* Maximum value the semaphore can have.  */
#define SEM_VALUE_MAX 	((int) ((~0u) >> 1))

EXPORTSTART
/* Initialize semaphore object SEM to VALUE.  If PSHARED then share it
   with other processes.  */
int __CDECL sem_init (sem_t *__sem, int __pshared, unsigned int __value);

/* Free resources associated with semaphore object SEM.  */
int __CDECL sem_destroy (sem_t *__sem);

/* Open a named semaphore NAME with open flaot OFLAG.  */
sem_t *__CDECL sem_open (__const char *__name, int __oflag, ...);

/* Close descriptor for named semaphore SEM.  */
int __CDECL sem_close (sem_t *__sem);

/* Remove named semaphore NAME.  */
int __CDECL sem_unlink (__const char *__name);

/* Wait for SEM being posted.  */
int __CDECL sem_wait (sem_t *__sem);

/* Similar to `sem_wait' but wait only until ABSTIME.  */
int __CDECL sem_timedwait (sem_t * __sem, __const struct timespec * __abstime);


/* Test whether SEM is posted.  */
int __CDECL sem_trywait (sem_t *__sem);

/* Post SEM.  */
int __CDECL sem_post (sem_t *__sem);

/* Get current value of SEM and store it in *SVAL.  */
int __CDECL sem_getvalue (sem_t * __sem, int * __sval);

EXPORTEND
#endif  /* semaphore.h */
