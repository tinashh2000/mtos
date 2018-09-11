del \MTOS\LIB\libx86-32.a
for %%i in (*.ASM) do MS \A16\AP /COFF %%i
for %%i in (*.obj) do objconv -felf32 %%i

ar -q \MTOS\LIB\libx86_32.a *.obj
ranlib \MTOS\LIB\libx86_32.a