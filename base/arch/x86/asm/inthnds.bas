OPEN "VEC.DAT" FOR OUTPUT AS #1

PRINT #1, "HandleVector:"
PRINT #1, CHR$(9) + "PUSH EAX, ECX, EDX"
PRINT #1, CHR$(9) + "CALL FWORD [EAX]"
PRINT #1, CHR$(9) + "POP EDX, ECX, EAX"
PRINT #1, CHR$(9) + "IRET"
PRINT #1, ""
FOR c = 32 TO 255

PRINT #1, "Intr" + HEX$(c) + ":"
PRINT #1, CHR$(9) + "PUSH    EAX"
PRINT #1, CHR$(9) + "MOV EAX,Handlers + (" + STR$(c) + " * 8)"
PRINT #1, CHR$(9) + "CMP MWORD [EAX],0"
PRINT #1, CHR$(9) + "JNZ HandleVector"
PRINT #1, CHR$(9) + "POP EAX"
PRINT #1, CHR$(9) + "IRET"
PRINT #1, ""
NEXT

