@echo off

IF "%WINDIR%"=="" GOTO DosX
GOTO WinX

:DosX

\A16\AP LIBC.ASM
IF ERRORLEVEL 1 goto EndMake
copy LIBC.OBJ \MTOS\BASE

goto EndMake

:WinX

\DOS\MS \A16\AP LIBC.ASM
IF ERRORLEVEL 1 goto EndMake
copy LIBC.OBJ \MTOS\BASE

:EndMake
