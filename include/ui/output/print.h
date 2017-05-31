typedef int (*PRINTSTRPROC)(const CHARPTR);
typedef int(*PRINTWSTRPROC)(const WCHARPTR);

typedef int (*PRINTSTRXPROC)(G_COR x,G_COR y,G_COLOR col,const CHARPTR strx);
typedef int (*PRINTWSTRXPROC)(G_COR x,G_COR y,G_COLOR col,const WCHARPTR strx);

typedef int (*PRINTCHARPROC)(CHAR32 c);
//typedef int(*PRINTWCHARPROC)(WCHAR c);

typedef BOOL (*INITPRINTPROC)(void);

EXPORTSTART
	int PrintChar(CHAR32 ch);
	int PrintStr(const CHARPTR str);
	int PrintWStr(const WCHARPTR str);
	int PrintStrX(G_COR x,G_COR y,G_COLOR col,const CHARPTR str);
	int PrintWStrX(G_COR x,G_COR y,G_COLOR col,const WCHARPTR str);
EXPORTEND