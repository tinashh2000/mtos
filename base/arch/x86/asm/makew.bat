\DOS\MS \a16\ap x86sys
IF ERRORLEVEL 1 goto EndMake
objconv -felf32 x86sys.obj
copy x86sys.o \MTOS\LIB
:EndMake
