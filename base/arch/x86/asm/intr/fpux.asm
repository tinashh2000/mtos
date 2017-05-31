CoprocessorAbsent:
    PUSH    EAX,EBX,ECX,EDX

    CALL    GetCurrentEXU

    LEA EBX,[EAX*4][(LastFPUThread)]  ;Get last thread to use FPU
    MOV ECX,[EBX]
    TEST    ECX,ECX                 ;If present save its registers
    JNZ smrSave
    CALL    GetCurrentThread        ;If not just mark current as last to use FPU
    MOV [EBX],EAX
    CLI
    CLTS
    FWAIT       ;Reset state of FPU
    FINIT
    TEST    BYTE [x86MediaFlags],AVX_INSTR
    JNZ  smrSSE
    TEST    BYTE [x86MediaFlags],SSE_INSTR
    JZ smrDone
 smrSSE:
    MOV EBX,ESP
    MOV ECX,ESP
    AND ECX,0Fh
    MOV ESP,ECX
    PUSH    DWORD(0),DWORD(0),DWORD(0),DWORD(0)     ;Reset SSE and AVX state
    MOVDQA XMM0,[ESP]
    MOVDQA XMM1,[ESP]
    MOVDQA XMM2,[ESP]
    MOVDQA XMM3,[ESP]
    MOVDQA XMM4,[ESP]
    MOVDQA XMM5,[ESP]
    MOVDQA XMM6,[ESP]
    MOVDQA XMM7,[ESP]
    MOV ESP,EBX
 smrDone:
    POP EDX,ECX,EBX,EAX
    IRET

 smrSave:        

    CLI
    CLTS
    TEST    BYTE [x86MediaFlags],AVX_INSTR
    JNZ smrSaveSSE
    TEST    BYTE [x86MediaFlags],SSE_INSTR
    JNZ smrSaveSSE

    ADD ECX,(SIZE MWORD)    ;Go past thread signature.
    FNSAVE  [ECX].FPUState   ;Save SSE state

    CALL    GetCurrentThread        ;If not just mark current as last to use FPU
    MOV [EBX],EAX   ;;Save in last FPU current 

    ADD EAX,(SIZE MWORD)
    FRSTOR [EAX].FPUState

    JMP smrDone

 smrSaveSSE:

    ADD ECX,(SIZE MWORD)        
    FXSAVE  [ECX].FPUState      ;Save SSE state

    CALL    GetCurrentThread
    MOV [EBX],EAX

    ADD EAX,(SIZE MWORD)
    FXRSTOR [EAX].FPUState

    JMP smrDone

