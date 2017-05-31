#define _MTOX_THREADS

#include <mtox.h>
#include "vmm.hxx"

BOOL    InitVMM() {
    InitLock(&VMMLock,"VMMLock");
    InitGlobalPages();
    return TRUE;
}
