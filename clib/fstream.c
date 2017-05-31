/* Seek method constants */
#include <mtos.h>
#include <stdio.h>
#include <filesys.h>

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

FILE *iobs[] = {(FILE *)0, (FILE *)1, (FILE *)2};

FILE **__CDECL _imp___iob() {
		return &iobs;
} 

int __CDECL fputc(int c, FILE *f) {
	int data = c;
	return FS_WriteFile((FILE_CONTEXT)f, (void*)&data, 1) == 1 ? c : EOF;
}

int __CDECL  fputs (const char* str, FILE*f) {
	int	slen = strlen(str);
	if (slen == 0) return 0;
	return 0; // FS_WriteFile((FILE_CONTEXT)f, (void*)str, slen) > 0 ? 1 : EOF;
}


char *	__CDECL fgets(char *str, int n, FILE *stream) {
	
	return NULL;
}

int __CDECL ferror(FILE* _Stream){
	return 0;
}

size_t __CDECL fwrite(const void *ptr, size_t size, size_t n, FILE *stream) {
		return FS_WriteFile((FILE_CONTEXT) stream, (void*)ptr, size * n) / size;
}

FILE * __CDECL fopen(const char * filename, const char * mode) {
	FS_PATH	wfilename;	
	MWORD	flags=0;
	
	if (filename == 0 || mode == 0)
		return NULL;


	if (*mode == 'a') {
		flags |= FS_FILE_OPEN_APPEND;
		mode++;
		if (*mode == '+') {
			flags |= FS_FILE_OPEN_READ;
			mode++;
		}
	}
	else if (*mode == 'r') {
		flags |= FS_FILE_OPEN_READ;
		mode++;
		if (*mode == '+') {
			flags |= FS_FILE_OPEN_WRITE;
			mode++;
		}
	}	
	else if (*mode == 'w') {
		flags |= FS_FILE_OPEN_WRITE;
		mode++;
		if (*mode == '+') {
			flags |= (FS_FILE_OPEN_READ | FS_FILE_OPEN_ERASE);
			mode++;
		}
	}
	else
		return 0;
	
	if (FS_IsUnicode()) {
		wfilename = (FS_PATH) malloc(FS_CHARSZ(MAX_FILELENGTH));
		if (wfilename == 0)
			return 0;

		int c=0;
		while (filename[c] != 0) {
			wfilename[c] = filename[c];
			c++;
		}
		return (FILE*) FS_OpenFile(0,wfilename,flags);
	}
	else
		return (FILE*) FS_OpenFile(0,filename,flags);

	return NULL;
}

FILE * __CDECL _wfopen(const wchar_t * filename, const wchar_t * mode) {
	return NULL;
}

int		__CDECL	fclose ( FILE * stream ) {
	return FS_CloseFile((FILE_CONTEXT) stream) == TRUE ? 0 : EOF;
}

size_t __CDECL fread(void *ptr, size_t size, size_t n, FILE *stream) {
	return FS_ReadFile((FILE_CONTEXT) stream, ptr, size * n) / size;
}

int __CDECL fcloseall(void) {
	return 0;
}

int __CDECL fgetc(FILE *stream) {
	return 0;
}

wchar_t * __CDECL fgetws(const wchar_t * s, int n, FILE *stream) {
		return NULL;
}

int __CDECL fgetpos(FILE *stream, fpos_t *pos) {
	return (*pos = FS_GetFilePos((FILE_CONTEXT) stream)) > 0 ? 0: FS_GetLastError();
}

int __CDECL fgetsize(FILE *stream, fpos_t *pos) {
	*pos = FS_GetFileSize((FILE_CONTEXT) stream);
	return 1;
}

void  __CDECL clearerr ( FILE * stream ) {
	return;
}

int  __CDECL feof ( FILE * stream ) {
	return 0;
}

long int  __CDECL ftell ( FILE * stream ) {
	return 0;
}

int  __CDECL fsetpos ( FILE * stream, const fpos_t * pos ) {
	return 0;
}

int __CDECL fseek(FILE *stream,long int offset, int whence ) {
	
	return 0;
}
