The x86 assembly part of the OS is a self-contained library which can be assembled using the African Assembler found at this link.
https://github.com/tinashh2000/asmpp.

===The Bootloader===
The boot loader is capable of loading COFF executables and therefore the OS kernel is a COFF/PE binary. The bootloader initializes protected mode on behalf of the kernel, therefore the OS kernel has no real-mode code. The boot-loader does all the real-mode stuff and switches to protected mode.

===Hardware Abstraction===

The assembly portion deals with most of the hardware stuff.

The high-level kernel is written in a way that allows it to be easily portable to another architecture although initially it was developed and tested on the x86_64 architectures.

===Assembly Portion===
The part written in assembly takes care of most of the low-level concerns and takes care of things like interrupts, atomic locking etc.

===Building x86 kernel===
The x86 source is found at https://github.com/tinashh2000/mtos/tree/master/base/arch/x86/asm. It can be assembled by running the make.bat which invokes the assembler. Make sure you edit the make.bat to point to the right directory of the assembler.
The assembler only works in MS-DOS therefore it doesnt run on 64-bit windows. You need to use 32-bit windows, or DosBox or alternatively, you can download an MS-DOS emulator software. I used MS-DOS player http://takeda-toshiya.my.coocan.jp/ or direct download: http://takeda-toshiya.my.coocan.jp/msdos/msdos.zip
