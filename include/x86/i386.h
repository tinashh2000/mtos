#define PAGE_SIZE   4096
#define PAGE_ALIGN  4096
#define PAGE_ALIGNMASK  ~(4095)

#define ALIGN_ADDRESS(addr) ((addr + PAGE_ALIGN - 1) & PAGE_ALIGNMASK)
#define ALIGN_SIZE(size) ((size + PAGE_ALIGN - 1) & PAGE_ALIGNMASK)
#define ALIGN32(addr) ((addr + 3) & ~3)
#define ALIGN64(addr) ((addr + 7) & ~7)
#define ALIGN128(addr) ((addr + 15) & ~15)
