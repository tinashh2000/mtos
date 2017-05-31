#include <mtos.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <math.h>
#include <semaphore.h>
#include <locale.h>
#include <unistd.h>
#include <sys/socket.h>

#define ___NI	"%s not implemented ", __FILE__

#define UNIMP(fx)	printf("%s is not implemented in %s, line: %i",fx,__FILE__, __LINE__);\
				return 0;

#define UNIMP0(fx)	printf("%s is not implemented in %s, line: %i",fx,__FILE__, __LINE__);

//				while(1);
EXPORT int errno;


struct timeval;
struct sockaddr;

EXPORTSTART
int __CDECL _errno();
void __CDECL _imp____mb_cur_max();
void __CDECL _imp___pctype();

int __cdecl access(const char *path,int amode);
int __CDECL _isctype( int c, int type );
int __CDECL _mkdir(const char* path);
int __CDECL mkdir(const char* path, int mode);

/*
void __CDECL _chkstk_ms();
void __CDECL __chkstk_ms();
void __CDECL __umoddi3();
void __CDECL __udivdi3();
void __CDECL __divdi3(); 
*/

int errno;

int __CDECL fstat(int, struct stat *);
int __CDECL stat(const char *, struct stat *);
locale_t __CDECL newlocale(int category_mask, const char *locale, locale_t base);
char * __CDECL setlocale(int category, const char *locale);

char* __CDECL getenv (const char* name);
void __CDECL perror (const char *message);

int __cdecl rmdir(const char *);

int __CDECL chmod (const char *path, mode_t mode);

void __CDECL _assert(char *cond, char *file, int line);

ssize_t mtos_send (int, const void *__buff, size_t __len, int __flags);

ssize_t mtos_recv (int, void *__buff, size_t __len, int __flags);
int mtos_select (int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
int mtos_closesocket(SOCKET s);
SOCKET mtos_accept(SOCKET,struct sockaddr*,int*);
int mtos_bind(SOCKET,const struct sockaddr*,int);
int mtos_closesocket(SOCKET);
int mtos_connect(SOCKET,const struct sockaddr*,int);
int mtos_ioctlsocket(SOCKET,long,u_long *);
int mtos_getpeername(SOCKET,struct sockaddr*,int*);
int mtos_getsockname(SOCKET,struct sockaddr*,int*);
int mtos_getsockopt(SOCKET,int,int,char*,int*);
int mtos_socket (int __family, int __type, int __protocol);


typedef void * DIR;
DIR *opendir(const char *name) {
	UNIMP("opendir")
}
struct dirent *readdir(DIR *dirp){
	UNIMP("readdir")
}

int closedir(DIR *dirp) {
	UNIMP("closedir")
}

void __CDECL _Unwind_SjLj_Register() {

	UNIMP0("Unwind Register")
	
}

void __CDECL _Unwind_SjLj_Resume() {

	UNIMP0("Unwind Resume")
	
}


void __CDECL _Unwind_SjLj_Unregister() {
	UNIMP0("Unwind Unregister")
}

void __CDECL _Unwind_SjLj_RaiseException () {
		UNIMP0("Unwind RaiseException")
}

void __CDECL _Unwind_SjLj_Resume_or_Rethrow (){
		UNIMP0("Unwind Resume_or_Rethrow")
}

void __CDECL _Unwind_GetDataRelBase() {
	UNIMP0("Unwind GetDataRelBase")
}


void __CDECL _Unwind_GetRegionStart() {
	UNIMP0("Unwind GetRegionStart")
	
}
void __CDECL _Unwind_GetTextRelBase() {
	UNIMP0("Unwind GetTextRelBase")	
}

void __CDECL _Unwind_GetLanguageSpecificData() {
	UNIMP0("Unwind GetLanguageSpecificData")
}

void __CDECL _Unwind_GetIPInfo() {
	UNIMP0("Unwind GetIPInfo")
}
void __CDECL _Unwind_SetGR() {
	UNIMP0("Unwind SetGR")
	
}
void __CDECL _Unwind_SetIP() {
		UNIMP0("Unwind SetIP")

}

void __CDECL __shmem_grab() {
	UNIMP0("shmem_grab")
}

float       __CDECL  strtof( const char *str, char **str_end ) {
	UNIMP("strtof")	
}

int		__cdecl strcoll( const char *lhs, const char *rhs ){
	UNIMP("strcoll")	
}
size_t	__cdecl strxfrm ( char*dest, const char *src, size_t count ){
	UNIMP("strxfrm")
}
int		__cdecl	wcscoll ( const wchar_t *lhs, const wchar_t *rhs){
	UNIMP("wcscoll")		
}
size_t	__cdecl wcsxfrm( wchar_t* dest, const wchar_t* src, size_t count){
	UNIMP("wcsxfrm")		
}
size_t	__cdecl strftime( char *str, size_t count, const char *format, const struct tm *time ){
	UNIMP("strftime")		
}
size_t __cdecl wcsftime( wchar_t* str, size_t count, const wchar_t* format, struct tm* time ){
	UNIMP("wcsftime")		
}

int  __CDECL mbsinit(const mbstate_t *_P) {
	return (_P == NULL || *_P == 0);
}

size_t __CDECL wcrtomb( char *s, wchar_t wc, mbstate_t *ps) {
	UNIMP("wcrtomb")		
}

size_t __CDECL mbrtowc( wchar_t* pwc, const char* s, size_t n, mbstate_t* ps ) {
	UNIMP("mbrtowc")		
}

wctype_t __cdecl wctype( const char* str ){
	UNIMP("wctype")		
}
int		__CDECL wctob( wint_t c ){
	UNIMP("wctob")		
}
wint_t __CDECL btowc( int c ){
	UNIMP("btowc")		
}

long double __CDECL  strtold( const char *str, char **str_end ) {
	UNIMP("strtold")	
}

void __CDECL _Unwind_DeleteException () {
	UNIMP0("DeleteException")		
}

int __CDECL __fpclassify( double x )
{
	union{ double d; uint64_t u;}u = {x};

	uint32_t	exp = (uint32_t) ( (u.u & 0x7fffffffffffffffULL) >> 52 );

	if( 0 == exp )
	{
		if( u.u & 0x000fffffffffffffULL )
			return FP_SUBNORMAL;
	
		return FP_ZERO;
	}

	if( 0x7ff == exp )
	{	
		if( u.u & 0x000fffffffffffffULL )
			return FP_NAN;

		return FP_INFINITE;
	}

	return FP_NORMAL;
}
EXPORTEND


//double __CDECL ceil (double d){}


ssize_t mtos_send (int s, const void *__buff, size_t __len, int __flags) {
	UNIMP("send")		
}

int mtos_connect (SOCKET s, const struct sockaddr *addr, socklen_t sz) {
	UNIMP("connect")		
}

int fcntl(int fd, int cmd, ...) {
	UNIMP("fcntl")		
}

int mtos_socket (int __family, int __type, int __protocol) {
	UNIMP("socket")	
}

int mtos_closesocket(SOCKET s) {
	UNIMP("closesocket")	
	return 0;
}

ssize_t mtos_recv (int p1, void *__buff, size_t __len, int __flags) {
	UNIMP("recv")		
}

int mtos_select (int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
	UNIMP("select")		
}

int __cdecl rmdir(const char *dir) {
	UNIMP("rmdir")		
}

struct lconv * __CDECL localeconv(void) {
	UNIMP("localeconv")	
	return 0;
}

int __CDECL rename(const char *oldnm, const char *newnm){
	return -1;
	UNIMP("rename")	
	return 0;
}

int __cdecl open(const char *file, int mode, ...) {
	return -1;
	UNIMP("open");
}

int __cdecl close(int hnd) {
	return -1;
	UNIMP("close");
}

ssize_t __cdecl read(int hnd, void *buf, size_t size){
	return -1;
	UNIMP("read");	
}

ssize_t __cdecl write(int hnd, const void *src, size_t size) {
	return -1;
	UNIMP("write");
}

int __CDECL chmod (const char *path, mode_t mode)
{
	return -1;
  UNIMP("chmod");
  return -1;
}


void __cdecl perror (const char *message) {
	UNIMP0("perror")	
}


char * __CDECL getcwd(char * buf, size_t size) {
	UNIMP("getcwd")	
	return 0;
}

void __CDECL _assert(char *cond, char *file, int line) {
    static char buffer[256];

	printf("Assertion failed : %s, file : %s, line: %i", cond, file, line);
    abort();
}

int  __CDECL unlink(const char *name)
{
	UNIMP("unlink")		
  return -1;
}

void __CDECL _imp___pctype(){
	UNIMP0("pctype")	
}

void __CDECL _imp____mb_cur_max() {
	UNIMP0("mb_cur_max")
}

locale_t __CDECL newlocale(int category_mask, const char *locale, locale_t base) {
	UNIMP("newlocale")	
	return 0;
}

char* __CDECL getenv (const char* name) {
	return 0;
	printf("<%s>",name);
	UNIMP("getenv")	
	return 0;
}

void __CDECL  freelocale(locale_t locobj) {
	UNIMP0("freelocale")	
}
	   
char * __CDECL setlocale(int category, const char *locale) {
	UNIMP("setlocale")	
	return 0;
}

locale_t __CDECL uselocale(locale_t newloc) {
	UNIMP("uselocale")	
	return 0;
}

int __CDECL __errno() {
	UNIMP("__errno")	
	return 0;
}

int __CDECL _errno() {
	UNIMP("errno")	
	return 0;
}

 int __CDECL _isctype( int c, int type ) {
	UNIMP("isctype")	
 return 0;
 }
 
int __CDECL fflush(FILE *stream){
	return -1;
	UNIMP("fflush");
	return 0;
}

int __CDECL remove(const char *filename) {
	return -1;
	UNIMP("remove");
	return 0;
}

/*
void __CDECL _chkstk_ms() {
	UNIMP("_chkstk_ms");
	while(1);
}

void __CDECL __chkstk_ms() {
	UNIMP("__chkstk_ms");
	while(1);
}

void __CDECL __umoddi3() {
	UNIMP("__umoddi3");
}

void __CDECL __udivdi3() {
	UNIMP("__udivdi3");
}

void __CDECL __divdi3() {
	UNIMP("__divdi3");
}
*/

int __CDECL fstat(int fd,struct stat *st) {
	return -1;
	UNIMP("fstat")
}

int __STDCALL fstatx(int fd,void *st) {
	return -1;
	UNIMP("fstat")
}

int __cdecl fstattest(int fd,struct stat *st) {
	return -1;
	UNIMP("fstat")
}

int __cdecl access(const char *path,int amode) {
	return -1;
	UNIMP("access")
}

void __cdecl rewind (FILE *fp)
{
//    fseek (fp, 0L, SEEK_SET);
}

int __CDECL munmap(void *p, unsigned int t) {
	UNIMP("munmap")
}

void  __cdecl *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset) {
	UNIMP0("mmap")
}

int  __CDECL stat(const char *file, struct stat * st)
{
	return -1;
	UNIMP("stat")
}

int __CDECL _mkdir(const char* path) {
	return -1;
	UNIMP("_mkdir")
	return 0;
}

int __CDECL mkdir(const char* path, int mode) {
	return -1;
	UNIMP("_mkdir")
	return 0;
}

int __CDECL 	fileno(FILE *f) {
	UNIMP("_fileno")
	return 0;
}

int __CDECL sem_init (sem_t *__sem, int __pshared, unsigned int __value) {
	UNIMP("sem_init")	
	return 0;
}
/* Free resources associated with semaphore object SEM.  */
int __CDECL sem_destroy (sem_t *__sem) {
	return -1;
	UNIMP("sem_destroy")	
		return 0;
}
/* Open a named semaphore NAME with open flaot OFLAG.  */
sem_t *__CDECL sem_open (const char *__name, int __oflag, ...) {
	UNIMP("sem_open")	
	return 0;
}
/* Close descriptor for named semaphore SEM.  */
int __CDECL sem_close (sem_t *__sem) {
	return -1;
	UNIMP("sem_close")	
		return 0;
}
/* Remove named semaphore NAME.  */
int __CDECL sem_unlink (const char *__name) {
	UNIMP("sem_unlink")	
		return 0;
}
/* Wait for SEM being posted.  */
int __CDECL sem_wait (sem_t *__sem) {
	return -1;
	UNIMP("sem_wait")	
		return 0;
}



/* Test whether SEM is posted.  */
int __CDECL sem_trywait (sem_t *__sem) {
	return -1;
	UNIMP("sem_trywait")	
	return 0;
}
/* Post SEM.  */
int __CDECL sem_post (sem_t *__sem) {
	UNIMP("sem_post")
	return 0;
}

/* Get current value of SEM and store it in *SVAL.  */
int __CDECL sem_getvalue (sem_t *__restrict __sem, int *__restrict __sval) {
	UNIMP("sem_getvalue")	
		return 0;
}

int __CDECL sscanf(const char *buf, const char *fmt, ...) {
	UNIMP("sscanf")	
	return 0;
}

time_t __CDECL time(time_t *tm) {
	return 0;
	UNIMP("time")	
	return 0;
}

size_t __CDECL strcspn(const char *s1, const char *s2)
{	/* find index of first s1[i] that matches any s2[] */
	const char *sc1, *sc2;

	for (sc1 = s1; *sc1 != '\0'; ++sc1)
		for (sc2 = s2; *sc2 != '\0'; ++sc2)
			if (*sc1 == *sc2)
				return (sc1 - s1);
	return (sc1 - s1);	/* terminating nulls match */
}

size_t __CDECL strspn(const char *s1, const char *s2)
{	/* find index of first s1[i] that matches no s2[] */
	const char *sc1, *sc2;

	for (sc1 = s1; *sc1 != '\0'; ++sc1)
		for (sc2 = s2; ; ++sc2)
			if (*sc2 == '\0')
				return (sc1 - s1);
			else if (*sc1 == *sc2)
				break;
	return (sc1 - s1);	/* null doesn't match */
}
