@echo off

IF "%WINDIR%"=="" GOTO DosX
GOTO WinX

:DosX

\a16\ap x86sys
IF ERRORLEVEL 1 goto EndMake
copy x86sys.obj \MTOS\LIB
goto EndMake

:WinX

\DOS\MS \A16\AP X86SYS
IF ERRORLEVEL 1 goto EndMake
copy X86SYS.OBJ \MTOS\LIB

:EndMake
