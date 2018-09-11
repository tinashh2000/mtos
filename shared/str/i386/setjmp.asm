;****************************************************************************************
;* Copyright (C) 2018 Tinashe Mutandagayi                                               *
;*                                                                                      *
;* This file is part of the MT-Operating System source code. The author(s) of this file *
;* is/are not liable for any damages, loss or loss of information, deaths, sicknesses   *
;* or other bad things resulting from use of this file or software, either direct or    *
;* indirect.                                                                            *
;* Terms and conditions for use and distribution can be found in the license file named *
;* LICENSE.TXT. If you distribute this file or continue using it,                       *
;* it means you understand and agree with the terms and conditions in the license file. *
;* binding this file.                                                                   *
;*                                                                                      *
;* Happy Coding :)                                                                      *
;****************************************************************************************

INCLUDE "PROLOG.AS"


JB_BP = 0
JB_BX = 1
JB_DI = 2
JB_SI = 3
JB_SP = 4
JB_IP = 5

PCOFF = 0

JMPBUF  = 4

PUBLIC setjmp, _setjmp, __setjmp

setjmp:
_setjmp:
__setjmp:
    xor eax, eax
    mov edx, JMPBUF[esp]

    ;Save registers.
    mov [edx + (JB_BP*4)], ebp ;Save caller's frame pointer. 
    mov [edx + (JB_BX*4)], ebx
    mov [edx + (JB_DI*4)], edi
    mov [edx + (JB_SI*4)], esi
    lea ecx, JMPBUF[esp]    ; Save SP as it will be after we return.
    mov [edx + (JB_SP*4)], ecx
    mov ecx, PCOFF[esp]     ; Save PC we are returning to now. 
    mov [edx + (JB_IP*4)], ecx
    ret

	COMMENT #
/*
 * int
 * _setjmp3(jmp_buf env, int nb_args, ...);
 *
 * Parameters:
 *   [ESP+04h] - jmp_buf env
 * Registers:
 *   None
 * Returns:
 *   0
 * Notes:
 *   Sets up the jmp_buf
 */
 #
 
PUBLIC setjmp3, _setjmp3, __setjmp3
setjmp3:
_setjmp3:
__setjmp3:
    xor eax, eax
    mov edx, JMPBUF[esp]

    ;Save registers.  
    mov [edx + (JB_BP*4)], ebp ;/* Save caller's frame pointer.  */
    mov [edx + (JB_BX*4)], ebx
    mov [edx + (JB_DI*4)], edi
    mov [edx + (JB_SI*4)], esi
    lea ecx, JMPBUF[esp]    ;/* Save SP as it will be after we return.  */
    mov [edx + (JB_SP*4)], ecx
    mov ecx, PCOFF[esp]     ;/* Save PC we are returning to now.  */
    mov [edx + (JB_IP*4)], ecx
    ret
COMMENT #
/*
 * void
 * longjmp(jmp_buf env, int value);
 *
 * Parameters:
 *   [ESP+04h] - jmp_buf setup by _setjmp
 *   [ESP+08h] - int     value to return
 * Registers:
 *   None
 * Returns:
 *   Doesn't return
 * Notes:
 *   Non-local goto
 */
 #
 
PUBLIC longjmp, _longjmp
longjmp:
_longjmp:
    mov ecx, JMPBUF[esp]   ;/* User's jmp_buf in %ecx.  */

    mov eax, [esp + 8]      ;/* Second argument is return value.  */
    ;/* Save the return address now. ; */
    mov edx, [ecx + (JB_IP*4)]
   ; /* Restore registers.  */
    mov ebp, [ecx + (JB_BP*4)]
    mov ebx, [ecx + (JB_BX*4)]
    mov edi, [ecx + (JB_DI*4)]
    mov esi, [ecx + (JB_SI*4)]
    mov esp, [ecx + (JB_SP*4)]
    ;/* Jump to saved PC.  */
    jmp edx

INCLUDE "EPILOG.AS"
