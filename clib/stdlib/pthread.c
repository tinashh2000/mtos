/* pthread.h: POSIX pthread interface

   Written by Marco Fuykschot <marco@ddi.nl>

   This file is part of Cygwin.

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */
#include <mtos.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/sched.h>
#include <time.h>

#include <pthread.h>

#define ___NI	"%s not implemented ", __FILE__

#define UNIMP(fx)	printf("%s is not implemented in %s, line: %i",fx,__FILE__, __LINE__);\
				return ENOTSUP;
;

#define UNIMP0(fx)	printf("%s is not implemented in %s, line: %i",fx,__FILE__, __LINE__);
				//while(1);

//extern void __CDECL (**_pthread_key_dest)(void *);

int         __CDECL pthread_key_create(pthread_key_t *key, void (* dest)(void *)) {
	return ENOTSUP;
	UNIMP("pcreate")
}

int         __CDECL pthread_key_delete(pthread_key_t key) {
	return ENOTSUP;
	UNIMP("pdelete")
}

void *      __CDECL pthread_getspecific(pthread_key_t key) {
	return 0;
	UNIMP0("pgetspecific")
}

int         __CDECL pthread_setspecific(pthread_key_t key, const void *value) {
	return ENOTSUP;
	UNIMP("psetspecific")
}


pthread_t __CDECL pthread_self(void) {
	return GetCurrentThread();
	UNIMP("pself")
}

int       __CDECL pthread_once(pthread_once_t *o, void (*func)(void)) {
	return ENOTSUP;
	UNIMP("ponce")
}

void      __CDECL pthread_testcancel(void) {
	UNIMP0("ptestcancel")
}

int       __CDECL pthread_equal(pthread_t t1, pthread_t t2) {
	return (t1 == t2);
	UNIMP("pequal")
}

void      __CDECL pthread_tls_init(void) {
	UNIMP0("unimplemented")
}

void      __CDECL _pthread_cleanup_dest(pthread_t t) {
	UNIMP0("unimplemented")
}

int       __CDECL pthread_get_concurrency(int *val) {
	UNIMP("unimplemented")
}

int       __CDECL pthread_set_concurrency(int val) {
	UNIMP("unimplemented")
}

void      __CDECL pthread_exit(void *res) {
	UNIMP0("unimplemented")
}

void      __CDECL _pthread_invoke_cancel(void) {
	UNIMP0("unimplemented")
}

int       __CDECL pthread_cancel(pthread_t t) {
	UNIMP("unimplemented")
}

int       __CDECL pthread_kill(pthread_t t, int sig) {
	UNIMP("unimplemented")
}

unsigned  __CDECL _pthread_get_state(const pthread_attr_t *attr, unsigned flag) {
	UNIMP("unimplemented")
}

int       __CDECL _pthread_set_state(pthread_attr_t *attr, unsigned flag, unsigned val) {
	UNIMP("unimplemented")
}

int       __CDECL pthread_setcancelstate(int state, int *oldstate) {
	UNIMP("unimplemented")
}

int       __CDECL pthread_setcanceltype(int type, int *oldtype) {
	UNIMP("unimplemented")
}

int       __CDECL pthread_create_wrapper(void *args) {
	UNIMP("unimplemented")
}

int       __CDECL pthread_create(pthread_t *th, const pthread_attr_t *attr, void *(* func)(void *), void *arg) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int       __CDECL pthread_join(pthread_t t, void **res) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int       __CDECL pthread_detach(pthread_t t) {
	return ENOTSUP;
	UNIMP("unimplemented")
}


int __CDECL pthread_rwlock_init(pthread_rwlock_t *rwlock_, const pthread_rwlockattr_t *attr) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_rwlock_wrlock(pthread_rwlock_t *l) {
	return ENOTSUP;
	UNIMP("unimplemented")
}
/*
int __CDECL pthread_rwlock_timedwrlock(pthread_rwlock_t *rwlock, const struct timespec *ts) {
	UNIMP("unimplemented")
}
*/
int __CDECL pthread_rwlock_rdlock(pthread_rwlock_t *l) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_rwlock_timedrdlock(pthread_rwlock_t *l, const struct timespec *ts) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_rwlock_unlock(pthread_rwlock_t *l) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_rwlock_tryrdlock(pthread_rwlock_t *l) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_rwlock_trywrlock(pthread_rwlock_t *l) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_rwlock_destroy (pthread_rwlock_t *l) {
	return ENOTSUP;
	UNIMP("unimplemented")
}


int __CDECL pthread_cond_init(pthread_cond_t *cv, const pthread_condattr_t *a) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_cond_destroy(pthread_cond_t *cv) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_cond_signal (pthread_cond_t *cv) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_cond_broadcast (pthread_cond_t *cv) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_cond_wait (pthread_cond_t *cv, pthread_mutex_t *external_mutex) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_cond_timedwait(pthread_cond_t *cv, pthread_mutex_t *external_mutex, const struct timespec *t) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_cond_timedwait_relative_np(pthread_cond_t *cv, pthread_mutex_t *external_mutex, const struct timespec *t) {
	return ENOTSUP;
	UNIMP("unimplemented")
}


int __CDECL pthread_mutex_lock(pthread_mutex_t *m) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_mutex_timedlock(pthread_mutex_t *m, const struct timespec *ts) {
	return ENOTSUP;
	UNIMP("unimplemented")
}

int __CDECL pthread_mutex_unlock(pthread_mutex_t *m) {
	UNIMP("unimplemented")
}

int __CDECL pthread_mutex_trylock(pthread_mutex_t *m) {
	UNIMP("unimplemented")
}

int __CDECL pthread_mutex_init(pthread_mutex_t *m, const pthread_mutexattr_t *a) {
	UNIMP("unimplemented")
}

int __CDECL pthread_mutex_destroy(pthread_mutex_t *m) {
	UNIMP("unimplemented")
}


int __CDECL pthread_barrier_destroy(pthread_barrier_t *b) {
	UNIMP("unimplemented")
}

int __CDECL pthread_barrier_init(pthread_barrier_t *b, const void *attr, unsigned int count) {
	UNIMP("unimplemented")
}

int __CDECL pthread_barrier_wait(pthread_barrier_t *b) {
	UNIMP("unimplemented")
}


int __CDECL pthread_spin_init(pthread_spinlock_t *l, int pshared) {
	UNIMP("unimplemented")
}

int __CDECL pthread_spin_destroy(pthread_spinlock_t *l) {
	UNIMP("unimplemented")
}

/* No-fair spinlock due to lack of knowledge of thread number.  */
int __CDECL pthread_spin_lock(pthread_spinlock_t *l) {
	UNIMP("unimplemented")
}

int __CDECL pthread_spin_trylock(pthread_spinlock_t *l) {
	UNIMP("unimplemented")
}

int __CDECL pthread_spin_unlock(pthread_spinlock_t *l) {
	UNIMP("unimplemented")
}


int __CDECL pthread_attr_init(pthread_attr_t *attr) {
	UNIMP("unimplemented")
}

int __CDECL pthread_attr_destroy(pthread_attr_t *attr) {
	UNIMP("unimplemented")
}

int __CDECL pthread_attr_setdetachstate(pthread_attr_t *a, int flag) {
	UNIMP("unimplemented")
}

int __CDECL pthread_attr_getdetachstate(const pthread_attr_t *a, int *flag) {
	UNIMP("unimplemented")
}

int __CDECL pthread_attr_setinheritsched(pthread_attr_t *a, int flag) {
	UNIMP("unimplemented")
}

int __CDECL pthread_attr_getinheritsched(const pthread_attr_t *a, int *flag) {
	UNIMP("unimplemented")
}

int __CDECL pthread_attr_setscope(pthread_attr_t *a, int flag) {
	UNIMP("unimplemented")
}

int __CDECL pthread_attr_getscope(const pthread_attr_t *a, int *flag) {
	UNIMP("unimplemented")
}

int __CDECL pthread_attr_getstackaddr(pthread_attr_t *attr, void **stack) {
	UNIMP("unimplemented")
}

int __CDECL pthread_attr_setstackaddr(pthread_attr_t *attr, void *stack) {
	UNIMP("unimplemented")
}

int __CDECL pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *size) {
	UNIMP("unimplemented")
}

int __CDECL pthread_attr_setstacksize(pthread_attr_t *attr, size_t size) {
	UNIMP("unimplemented")
}


int __CDECL pthread_mutexattr_init(pthread_mutexattr_t *a) {
	UNIMP("unimplemented")
}

int __CDECL pthread_mutexattr_destroy(pthread_mutexattr_t *a) {
	UNIMP("unimplemented")
}

int __CDECL pthread_mutexattr_gettype(const pthread_mutexattr_t *a, int *type) {
	UNIMP("unimplemented")
}

int __CDECL pthread_mutexattr_settype(pthread_mutexattr_t *a, int type) {
	UNIMP("unimplemented")
}

int __CDECL pthread_mutexattr_getpshared(const pthread_mutexattr_t *a, int *type) {
	UNIMP("unimplemented")
}

int __CDECL pthread_mutexattr_setpshared(pthread_mutexattr_t * a, int type) {
	UNIMP("unimplemented")
}

int __CDECL pthread_mutexattr_getprotocol(const pthread_mutexattr_t *a, int *type) {
	UNIMP("unimplemented")
}

int __CDECL pthread_mutexattr_setprotocol(pthread_mutexattr_t *a, int type) {
	UNIMP("unimplemented")
}

int __CDECL pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *a, int * prio) {
	UNIMP("unimplemented")
}

int __CDECL pthread_mutexattr_setprioceiling(pthread_mutexattr_t *a, int prio) {
	UNIMP("unimplemented")
}

int __CDECL pthread_getconcurrency(void) {
	UNIMP("unimplemented")
}

int __CDECL pthread_setconcurrency(int new_level) {
	UNIMP("unimplemented")
}


int __CDECL pthread_condattr_destroy(pthread_condattr_t *a) {
	UNIMP("unimplemented")
}

int __CDECL pthread_condattr_init(pthread_condattr_t *a) {
	UNIMP("unimplemented")
}

int __CDECL pthread_condattr_getpshared(const pthread_condattr_t *a, int *s) {
	UNIMP("unimplemented")
}

int __CDECL pthread_condattr_setpshared(pthread_condattr_t *a, int s) {
	UNIMP("unimplemented")
}


int __CDECL pthread_condattr_getclock (const pthread_condattr_t *attr,
       clockid_t *clock_id) {
	UNIMP("unimplemented")
}

int __CDECL pthread_condattr_setclock(pthread_condattr_t *attr,
       clockid_t clock_id) {
	UNIMP("unimplemented")
}

int __CDECL __pthread_clock_nanosleep(clockid_t clock_id, int flags, const struct timespec *rqtp, struct timespec *rmtp) {
	UNIMP("unimplemented")
}


int __CDECL pthread_barrierattr_init(void **attr) {
	UNIMP("unimplemented")
}

int __CDECL pthread_barrierattr_destroy(void **attr) {
	UNIMP("unimplemented")
}

int __CDECL pthread_barrierattr_setpshared(void **attr, int s) {
	UNIMP("unimplemented")
}

int __CDECL pthread_barrierattr_getpshared(void **attr, int *s) {
	UNIMP("unimplemented")
}


/* Private extensions for analysis and internal use.  */
struct _pthread_cleanup ** __CDECL pthread_getclean (void) {
	UNIMP("unimplemented")
}

void *                     __CDECL pthread_gethandle (pthread_t t) {
	return 0;
	UNIMP("unimplemented")
}

void *                     __CDECL pthread_getevent () {
	return 0;
	UNIMP("unimplemented")
}

/*
unsigned long long         __CDECL _pthread_rel_time_in_ms(const struct timespec *ts) {
	UNIMP("unimplemented")
}
*/

unsigned long long         __CDECL _pthread_time_in_ms(void) {
	UNIMP("unimplemented")
}

/*
unsigned long long         __CDECL _pthread_time_in_ms_from_timespec(const struct timespec *ts) {
	UNIMP("unimplemented")
}
*/
int                        __CDECL _pthread_tryjoin (pthread_t t, void **res) {
	UNIMP("unimplemented")
}

int                        __CDECL pthread_rwlockattr_destroy(pthread_rwlockattr_t *a) {
	UNIMP("unimplemented")
}

int                        __CDECL pthread_rwlockattr_getpshared(pthread_rwlockattr_t *a, int *s) {
	UNIMP("unimplemented")
}

int	__CDECL pthread_rwlockattr_init(pthread_rwlockattr_t *a) {
	UNIMP("unimplemented")
}

int	__CDECL pthread_rwlockattr_setpshared(pthread_rwlockattr_t *a, int s) {
	UNIMP("unimplemented")
}

