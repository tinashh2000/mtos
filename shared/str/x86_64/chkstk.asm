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

_chkstk:
        push   rcx
        push   rax
        cmp    rax, 0x1000	;$0x1000,%rax
        lea	rcx, [rsp][24]	;lea    24(%rsp),%rcx
        jb     p1
p2:
        sub		rcx, 0x1000	;sub    $0x1000,%rcx
        test   rcx,rcx		;%rcx,(%rcx)
        sub    rax, 0x1000	;$0x1000,%rax
        cmp    rax, 0x1000	;$0x1000,%rax
        ja     p2
p1:
        sub    rcx,rax	;%rax,%rcx
        test   rcx,rcx	;%rcx,(%rcx)
        pop    rax
        pop    rcx
        ret

INCLUDE "EPILOG.AS"
