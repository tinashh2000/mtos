#define _MTOX_THREADS
#define _MTOX_MMMGR
#define _MTOX_SYS
#define _MTOX_FILESYS
#define _MTOX_DEVICES
#define _MTOX_EVENTS
#define _MTOX_UI

#include <mtos.h>

typedef struct {
	void *EnvString;

} ENVIRONMENT_BLOCK;

typedef struct {
	UINT32	envSize;		//Size of the structure, including all headers etc.
	UINT32	envLength;		//Size of the used part of the structure
	UINT32	numVariables;	//Number of variables
	MWORD	lock;

} ENV_STRING_HEADER;

typedef struct {
	UINT16	entryLength;	//Length of whole string including null terminators. ptr + stringLength must point to the next entry
	UINT16	nameLength;		//Length of the string
	char	envVarName[];	//The string name
} ENV_VAR;

#define S_ENVHEADER(p) ((ENV_STRING_HEADER*) p)
int minEnvSize = 4096;

//Format for each variable is: {entrylength},{namelength},{null terminated varname},{null terminated varContents}{null terminator}
//String length is length of whole entry, name length is length of name without null character

char *ShellGetEnvironmentStringTable(char *str) {
	void *envstr;

	if (GetEnvironmentBlockItem(GetCurrentProcess(), &envstr, offsetof(ENVIRONMENT_BLOCK, EnvString), sizeof(char*)) && envstr != 0) {
		return envstr;
	}
	return 0;
}

BOOL	ShellSetEnvironmentStringTable(char *str) {
	return SetEnvironmentBlockItem(GetCurrentProcess(), &str, offsetof(ENVIRONMENT_BLOCK, EnvString), sizeof(char*));
}

char *ShellGetEnvironmentString(char *name) {
	void *envstr;

	if (GetEnvironmentBlockItem(GetCurrentProcess(), &envstr, offsetof(ENVIRONMENT_BLOCK, EnvString), sizeof(char*)) && envstr != 0) {
		//S_ENVHEADER(envstr)
		if (LockVariable(&S_ENVHEADER(envstr)->lock)) {
			UINT32 remainVars;
			UINT16 nameSz = strlen(name);
			if ((remainVars = S_ENVHEADER(envstr)->numVariables) > 0) {
				ENV_VAR *env = (ENV_VAR*)(BYTEPTR(envstr) + sizeof(ENV_STRING_HEADER));

				do {
					if (env->nameLength == nameSz) {
						if (strcmp(&env->envVarName[0], name) == 0) {
							UnlockVariable(&S_ENVHEADER(envstr)->lock);
							return &env->envVarName[env->nameLength + 1];
						}
					}
				} while (remainVars-- > 0);
			}
			UnlockVariable(&S_ENVHEADER(envstr)->lock);
		}
	}
	return FALSE;
}

ENV_VAR *FindEnvString(ENV_STRING_HEADER *envstr, char *name) {
	UINT32 remainVars;
	UINT16 nameSz = strlen(name);
	if ((remainVars = S_ENVHEADER(envstr)->numVariables) > 0) {
		ENV_VAR *env = (ENV_VAR*)(BYTEPTR(envstr) + sizeof(ENV_STRING_HEADER));

		do {
			if (env->nameLength == nameSz) {
				if (strcmp(&env->envVarName[0], name) == 0) {
					return env;
				}
			}
			env = (ENV_VAR*)(BYTEPTR(env) + env->entryLength);
			printf("<<@@%x>>",remainVars);
		} while (remainVars-- > 0);
	}
	return 0;
}

BOOL	QuickDeleteEnvironmentString(ENV_STRING_HEADER *envstr, ENV_VAR *env) {
	UINT32	eSz = env->entryLength;
	ENV_VAR* nextEnv = (ENV_VAR*)(BYTEPTR(env) + env->entryLength);
	UINT32	copySz = (S_ENVHEADER(envstr)->envLength + BYTEPTR(envstr)) - BYTEPTR(nextEnv);
	memmove(env, nextEnv, copySz);
	S_ENVHEADER(envstr)->envLength -= eSz;
	printf("<<!!%x>>", S_ENVHEADER(envstr)->numVariables);
	S_ENVHEADER(envstr)->numVariables--;
}

BOOL	ShellDeleteEnvironmentString(char *name) {
	void *envstr;

	if (GetEnvironmentBlockItem(GetCurrentProcess(), &envstr, offsetof(ENVIRONMENT_BLOCK, EnvString), sizeof(char*)) && envstr != 0) {
		//S_ENVHEADER(envstr)
		if (LockVariable(&S_ENVHEADER(envstr)->lock)) {
			ENV_VAR *env;
			if ((env = FindEnvString(envstr, name))) {
				QuickDeleteEnvironmentString(envstr, env);
				UnlockVariable(&S_ENVHEADER(envstr)->lock);
				return TRUE;
			}
			UnlockVariable(&S_ENVHEADER(envstr)->lock);
		}
	}
	return FALSE;
}


BOOL	ShellSetEnvironmentString(char *name, char*contents) {
	ENV_VAR *env;

	void *envstr;
	if (GetEnvironmentBlockItem(GetCurrentProcess(), &envstr, offsetof(ENVIRONMENT_BLOCK, EnvString), sizeof(char*)) && envstr != 0) {
		printf("env!:%x", envstr);
		if (LockVariable(&S_ENVHEADER(envstr)->lock)) {
			UINT16 nameSz = strlen(name);
			UINT16 contentsSz = strlen(contents);
			if ((env = FindEnvString(envstr, name)))
				QuickDeleteEnvironmentString(envstr, env);
			
			UINT32 entrySize = nameSz + contentsSz + sizeof(ENV_VAR) + 2;	//2 is for null terminators
			while ((S_ENVHEADER(envstr)->envLength + entrySize) > S_ENVHEADER(envstr)->envSize) {
				void *p = realloc(envstr, ALIGN_SIZE(entrySize + S_ENVHEADER(envstr)->envSize));
				if (p) {
					ShellGetEnvironmentStringTable(p);
					envstr = p;
				}
				else {

					UnlockVariable(&S_ENVHEADER(envstr)->lock);
					return FALSE;
				}
			}

			env = (ENV_VAR*) (BYTEPTR(envstr) + S_ENVHEADER(envstr)->envLength);
			env->entryLength = entrySize;
			env->nameLength = nameSz;
			memcpy(&env->envVarName[0],name,nameSz + 1);
			memcpy(&env->envVarName[nameSz + 1], contents, contentsSz);
			S_ENVHEADER(envstr)->envLength += entrySize;
			S_ENVHEADER(envstr)->numVariables++;
			UnlockVariable(&S_ENVHEADER(envstr)->lock);
			return TRUE;
			}
	}
	return 0;
}

BOOL	ShellInitializeEnvironment() {
	InitializeEnvironmentBlock(GetCurrentProcess());
	char *ptr = malloc(minEnvSize);
	if (ptr) {
		if (ShellSetEnvironmentStringTable(ptr)) {
			S_ENVHEADER(ptr)->envSize = minEnvSize;
			S_ENVHEADER(ptr)->numVariables = 0;
			S_ENVHEADER(ptr)->envLength = sizeof(ENV_STRING_HEADER);
			char *workingBuffer = malloc(32768);
			printf("sh:%x", ptr);
			printf("<<11::%x>>", S_ENVHEADER(ptr)->numVariables);
			ShellSetEnvironmentString("PATH", "0:/mtos");
			printf("<<22::%x>>", S_ENVHEADER(ptr)->numVariables);
			ShellSetEnvironmentString("HOME", "0:/mtos");
			printf("<<33::%x>>", S_ENVHEADER(ptr)->numVariables);
			ShellSetEnvironmentString("OS", "MTOS");
			printf("<<44::%x>>", S_ENVHEADER(ptr)->numVariables);
			ShellSetEnvironmentString("OSVersion", "1.0");
			printf("<<55::%x>>", S_ENVHEADER(ptr)->numVariables);
			ShellSetEnvironmentString("CURDIR", "0:/mtos");
			printf("<<66::%x>>", S_ENVHEADER(ptr)->numVariables);
			ShellSetEnvironmentString("OS", "MTOX");
			printf("<<<len:%x->%x>>>", (sizeof(ENV_STRING_HEADER) + (sizeof(ENV_VAR) * 5) + 8 + 2 + 9 + 14 + 4 + 3 + 8 + 15), S_ENVHEADER(ptr)->envLength);

			free(workingBuffer);
			return TRUE;
		}
		free(ptr);
	}
	return FALSE;
}

char *ShellGetCurrentPath() {
	return ShellGetEnvironmentString("MTOS_CURPATH");
}



char *ShellGetOSVersion() {

}