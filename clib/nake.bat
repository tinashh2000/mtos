DEL *.OBJ

cl /X /GS- /Gz /I\MTOS\INCLUDE *.c /c
IF ERRORLEVEL 1 goto EndMake

COPY STDLIB\*.OBJ
COPY I386\*.OBJ
IF EXIST CLIB.LIB GOTO LibPresent
LIB *.OBJ
REN *.LIB CLIB.LIB
GOTO EndMake
:LibPresent
LIB CLIB.LIB *.obj
COPY CLIB.LIB \MTOS\OBJ
:EndMake
DEL *.OBJ