del \MTOS\LIB\libx86-64.a
for %%i in (*.ASM) do MS \A16\AP /COFF64 %%i
REM for %%i in (*.obj) do objconv -felf32 %%i

ar -q \MTOS\LIB\libx86-64.a *.obj
ranlib \MTOS\LIB\libx86-64.a