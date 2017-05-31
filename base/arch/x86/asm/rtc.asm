initRTC PROC
    cli         ;Disable ALL maskable interrupts
    
    mov al,0Bh  ;CMOS Register B
    out 70h,al  ;Tell CMOS we want to access it
    in al,71h   ;Read Register B
    or al,01000000b ;Set Bit 6=Periodic interrupt
    
    mov ah,al   ;Save it in ah
    mov al,0Bh  ;CMOS Register B
    out 70h,al  ;Tell CMOS we want to access it
    mov al,ah
    out 71h,al  ;Write It!
    
    mov al,0Ch  ;CMOS Register C
    out 70h,al  ;Tell CMOS we want to access it
    in al,71h   ;Read Register C
    or al,01000000b ;Set Bit 7=Interrupt request
    
    mov ah,al   ;Save it in ah
    mov al,0Ch  ;CMOS Register C
    out 70h,al  ;Tell CMOS we want to access it
    mov al,ah
    out 71h,al  ;Write It!
    
    ;mov al,0Ah ;CMOS Register A
    ;out 70h,al ;Tell CMOS we want to access it
    ;mov al,26h ;Change the interrupt intervals.
    ;out 71h,al ;Write value to CMOS register
    
    MOV AL,0
    OUT 021h,AL
    mov AL,0FEh ;Mask all interrupts except for te RTC clock interrupt
    out 0A1h,al ;Enable RTC clock interrupt only in the slave interrupt contoller
    sti

    RET

initRTC    ENDP

__initRTC             PROC
    PUSHF
    CLI
    PUSH    EAX
    CALL    PrintStr,(_InitRTC)
 rtcListen:
    MOV AL,0Ah
    OUT 0x70,AL
    IN  AL,71h
    TEST    AL,0x80
    JNZ rtcListen

    MOV AL,0AH ;Select CMOS Register A
    OUT 70h,AL ;Tell CMOS we want to access it
    MOV AL,26h ;Change the interrupt intervals.
    OUT 71h,AL ;Write value to CMOS register

    CALL    rtcInitTimer

    CALL    PrintStr,(_Done)
    CALL    PrintStr,(_LF)

    POP EAX
    POPF
    RET
__initRTC             ENDP

shutRTC     PROC
    CALL    rtcShutTimer
    RET
shutRTC     ENDP

rtcWrite    PROC
    OUT 70h,AL
    MOV AL,AH
    OUT 71h,AL
    RET
rtcWrite    ENDP

rtcRead     PROC
    OUT 70h,AL
    IN  AL,71h
    RET
rtcRead     ENDP

rtcGetTime  PROC
    PUSHF
    CLI
    MOV AL,0
    OUT 70h,AL
    IN  AL,71h
    MOV BL,AL
    MOV AL,2
    OUT 70h,AL
    IN  AL,71h
    MOV BH,AL
    MOV AL,4
    OUT 70h,AL
    IN  AL,71h
    POPF
    RET
rtcGetTime  ENDP

rtcSetTime  PROC
    RET
rtcSetTime  ENDP

rtcGetDate  PROC
    PUSHF
    CLI
    MOV AL,6
    OUT 70h,AL
    IN  AL,71h
    MOV BL,AL
    MOV AL,7
    OUT 70h,AL
    IN  AL,71h
    MOV BH,AL
    MOV AL,8
    OUT 70h,AL
    IN  AL,71h
    MOV CL,AL
    MOV AL,9
    OUT 70h,AL
    IN  AL,71h
    MOV AL,CL
    POPF
    RET
rtcGetDate  ENDP

rtcSetDate  PROC
    RET
rtcSetDate  ENDP

rtcInitTimer    PROC
    PUSHF
    CLI		;Disable INTs

    MOV AL,0AH  ;Select CMOS Register A
    OUT 70h,AL  ;Tell CMOS we want to access it
    IN AL,71h   ;Read Register A
    AND AL,NOT (1111b)
    OR  AL,(110b)

    MOV AH,AL   ;Save it IN AH
    MOV AL,0AH  ;Select CMOS Register A
    OUT 70h,AL  ;Tell CMOS we want to access it

    MOV AL,AH
    OUT 71h,AL  ;Write It!

    MOV AL,0BH  ;Select CMOS Register B
    OUT 70h,AL  ;Tell CMOS we want to access it
    IN AL,71h   ;Read Register B
    OR AL,40h	;Set Bit 6=Periodic interrupt

    MOV AH,AL   ;Save it IN AH
    MOV AL,0BH  ;Select CMOS Register B
    OUT 70h,AL  ;Tell CMOS we want to access it

    MOV AL,AH
    OUT 71h,AL  ;Write It!

    MOV EAX,CS
    CALL    setVector,BASE_IRQ + 8,(rtcIRQHandler),EAX

    CALL   EnableIRQ,8

    MOV ECX,10000000h
    LOOP    $

    POPF
    RET
rtcInitTimer    ENDP

rtcShutTimer    PROC
    PUSHF
    CLI
    MOV AL,0BH      ;CMOS Register B
    OUT 70h,AL      ;Tell CMOS we want to access it
    IN AL,71h       ;Read Register B
    AND AL,NOT 40h  ;Set Bit 6=Periodic interrupt
    MOV AH,AL       ;Save it IN AH

    MOV AL,0BH      ;CMOS Register B
    OUT 70h,AL      ;Tell CMOS we want to access it
    MOV AL,AH
    OUT 71h,AL      ;Write It!

    POPF
    RET
rtcShutTimer    ENDP

rtcIRQHandler   PROC
;    INC BYTE [0B82E0h]
    ADD DWORD [RTCTicks],1
    ADC DWORD [RTCTicks][4],0

    PUSH    EAX
    MOV AL,0Ch
    OUT 70h,AL
    IN  AL,71h

    MOV AL,20h
    OUT 0A0h,AL
    OUT 020h,AL

    POP EAX
   
    CALL    acknowledgeIRQ,8

    IRET
rtcIRQHandler   ENDP
