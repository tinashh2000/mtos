del *.obj
for %%i in (*.ASM) do MS \A16\AP /COFF %%i

REM del clibx86.a
REM ar -q clibx86.a *.obj

del *.lib
lib *.obj
ren *.lib clib86.lib
copy *.lib \MTOS\LIB