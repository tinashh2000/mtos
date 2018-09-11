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

PAGE_SIZE  = 4096

PUBLIC __chkstk
PUBLIC __alloca_probe
PUBLIC __alloca_probe_16

;SEGMENT '.chkstk' CODE

;    /* 16 byte aligned alloca probe
;     * EAX = size to be allocated */
__alloca_probe_16:
;    /* save the ECX register */
    push ecx

;    /* ecx = top of the previous stack frame */
    lea ecx, [esp + 8]

;    /* Calculate end of allocation */
    sub ecx, eax

;    /* Get the misalignment */
    and ecx, 15

;    /* Add the misalignment to the original alloc size */
    add eax, ecx

;    /* Check for overflow */
    jnc l1

;    /* Set maximum value */
    mov eax, 0ffffffffh
l1:
;    /* Restore ecx */
    pop ecx
;    /* Fall through to __chkstk */

comment #
/*
 _chkstk() is called by all stack allocations of more than 4 KB. It grows the
 stack in areas of 4 KB each, trying to access each area. This ensures that the
 guard page for the stack is hit, and the stack growing triggered
 */
 #
__chkstk:
__alloca_probe:

;    /* EAX = size to be allocated */
;    /* save the ECX register */
    push ecx

;    /* ECX = top of the previous stack frame */
    lea ecx, [esp + 8]

;    /* probe the desired memory, page by page */
    cmp eax, PAGE_SIZE
    jl l_LessThanAPage

 l_MoreThanAPage:

;    /* raise the top of the stack by a page and probe */
    sub ecx, PAGE_SIZE
    test [ecx], eax

;    /* loop if still more than a page must be probed */
    sub eax, PAGE_SIZE
    cmp eax, PAGE_SIZE
    jge l_MoreThanAPage

 l_LessThanAPage:

    ;/* raise the top of the stack by EAX bytes (size % 4096) and probe */
    sub ecx, eax
    test [ecx], eax

;    /* EAX = top of the stack */
    mov eax, esp

    ;/* allocate the memory */
    mov esp, ecx

;    /* restore ECX */
    mov ecx, [eax]

;    /* restore the return address */
    mov eax, [eax + 4]
    push eax

;    /* return */
    ret

;/* EOF */

INCLUDE "EPILOG.AS"
