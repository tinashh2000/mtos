del \MTOS\LIB\libclib86.a
for %%i in (*.ASM) do MS \A16\AP /COFF %%i
for %%i in (*.obj) do objconv -felf32 %%i

ar -q \MTOS\LIB\libclib86.a *.obj
ranlib \MTOS\LIB\libclib86.a