#define _MTOX_FILESYS
#define _MTOX_UI

#include "i8042.h"
#include "i8042.hxx"
    
//UINT32 inMouse=0;

#define xx_printf(str,...) ;//
void	i8042Reset() {
		while (inportb(0x64) & 2);
		outportb(0x64,0xFE);
}

void ps2ReadWait() {
	UINT cc=0;
    while (((inportb(0x64) & PS2_OUTPUT_BUFFER_FULL) == 0) && cc <PS2_RETRIES) {
//        Delay(1);
		cc++;
	}
}

void ps2WriteWait() {
	UINT cc=0;
    while ((inportb(0x64) & PS2_INPUT_BUFFER_FULL) && cc < PS2_RETRIES){
//        Delay(1);
		cc++;
	}
}

void ps2DataWrite(UINT32 data){
	ps2WriteWait();
	outportb(0x60,data);
    inportb(0x60);
}

UINT32 ps2DataRead(){
	ps2ReadWait();
    return ((UINT32) inportb(0x60)) & 0xFF;
}

void ps2CtrlWrite(UINT32 ps2Command) {
	ps2WriteWait();
	outportb(0x64,ps2Command);
}

void ps2MouseWrite(UINT32 ps2Command) {
	ps2CtrlWrite(0xD4);
	ps2WriteWait();
	outportb(0x60,ps2Command);
	ps2DataRead();
}

BOOL ps2GetDeviceIdX() {
    UINT32 data;
    UINT32 c=0;

//    do {
        ps2MouseWrite(PS2_MOUSE_GET_ID);
        data = ps2DataRead();

//        d_printf("<gdx%i:%x>",c,((UINT32)data) & 0xFF);

        if (data == 0xFF) return FALSE;
        ps2MouseType = (char) data;
        c++;


//    } while (data != PS2_ACK && data != PS2_OK && c < PS2_RETRIES);
    if (c>=PS2_RETRIES) return FALSE;
    return TRUE;
}

BOOL ps2SetSampleRateX(UINT32 sRate) {
    UINT32 data;
  
    UINT32 c=0;

    do {
        do {
            ps2MouseWrite(PS2_SET_SAMPLE_RATE);
            data = ps2DataRead();
            if (data == 0xFF) return FALSE;
            c++;
            xx_printf("xssr!<%i:%x>",c,((UINT32)data) & 0xFF);
        } while (data != PS2_ACK && data != PS2_OK && c < PS2_RETRIES);
        if (c>=PS2_RETRIES) return FALSE;
        c=0;
        do {
            ps2MouseWrite(sRate);

            data = ps2DataRead();
            if (data == 0xFF) return FALSE;
            if (data == KB_RESEND) break;

            c++;
            xx_printf("(xssr%i:%x>",c,((UINT32)data) & 0xFF);
        } while (data != PS2_ACK && data != PS2_OK && c < PS2_RETRIES);
    } while(data == KB_RESEND);

    if (c>=PS2_RETRIES) return FALSE;
    return TRUE;
}

BOOL ps2SetResolutionX(UINT32 sRes) {
    UINT32 data;
    UINT32 c=0;

    do {
        ps2MouseWrite(PS2_MOUSE_SET_RESOLUTION);
        data = ps2DataRead();
        if (data == 0xFF) return 0;
        c++;
    } while (data != PS2_ACK && c < PS2_RETRIES);
    if (c>=PS2_RETRIES) return FALSE;
    c=0;
    do {
        ps2MouseWrite(sRes);
        data = ps2DataRead();
        if (data == 0xFF) return FALSE;
        c++;
    } while (data != PS2_ACK && c < PS2_RETRIES);
    if (c>=PS2_RETRIES) return FALSE;

    return TRUE;
}

BOOL ps2SetScalingX(UINT32 scaling) {
    UINT32 data;

    UINT32 c=0;

    do {
        ps2MouseWrite(scaling);
        data = ps2DataRead();

        if (data == 0xFF) return FALSE;

        c++;
    } while (data != PS2_ACK && c < PS2_RETRIES);
    if (c>=PS2_RETRIES) return FALSE;

    return TRUE;
}

BOOL ps2EnableX() {
    UINT32 data;

    UINT32 c=0;

    do {
        ps2MouseWrite(PS2_ENABLE);
        data = ps2DataRead();

        if (data == 0xFF) return 0;

        c++;
    } while (data != PS2_ACK && c < PS2_RETRIES);
    if (c>=PS2_RETRIES) return FALSE;
    return TRUE;
}

BOOL ps2MouseResetX() {
    UINT32 data=0;
    UINT32 c=0;

	do {

		ps2MouseWrite(PS2_RESET);

        data = (ps2DataRead() & 0xFF);
        xx_printf("<mr%i:%x>",c,((UINT32)data) & 0xFF);

        if (data == 0xFF) return FALSE;
        c++;
    } while (data != PS2_ACK && data != PS2_OK && c < PS2_RETRIES);

    if (c>=PS2_RETRIES) return FALSE;

	data = ps2DataRead();

    if (data == 0xFF) return FALSE;

	data = ps2DataRead();

    if (data == 0xFF) return FALSE;

    return TRUE;
}

void	ps2DisableKeyboard() {
	ps2CtrlWrite(PS2_CTRL_DISABLE_CH1);
}

void	ps2EnableKeyboard() {
	ps2CtrlWrite(PS2_CTRL_ENABLE_CH1);
}

void	ps2DisableMouse() {
	ps2CtrlWrite(PS2_CTRL_DISABLE_CH2);
}

void	ps2EnableMouse() {
	ps2CtrlWrite(PS2_CTRL_ENABLE_CH2);
}

void	ps2MouseReset() {
}

void    ps2SetKeyboardLEDs(UINT32 kbLeds) {
	ps2DataWrite(PS2_WRITE_KB_LEDS_CMD);
	ps2DataRead();
	ps2DataWrite(kbLeds);
	ps2DataRead();
} 

void    ps2SetTypematicRate(UINT32 kbRate) {
	ps2DataWrite(PS2_SET_SAMPLE_RATE);
	ps2DataRead();
	ps2DataWrite(kbRate);
	ps2DataRead();
	
	ps2SetKeyboardLEDs(2);
}
UINT8 tx=0;


void	i8042MouseHandler() {
    PROCESS_EVENT pevt;

    ps2MouseBuffer[ps2MouseIRQs] = (INT8) ps2DataRead();
    ps2MouseIRQs++;
    if (ps2MouseType == ps2MouseIRQs) {
        UINT32 mstate = (UINT32) (ps2MouseBuffer[0] & 7);
        INT32 x = (INT32) ((signed char) ps2MouseBuffer[1]);
        INT32 y = -((INT32) ((signed char) ps2MouseBuffer[2]));
        INT32 scroll = ((INT32) ((signed char) ps2MouseBuffer[3]));

        ps2MouseIRQs = 0;
		pevt.EventClass = EVT_MOUSE_EVENT;
		pevt.EventTime  = GetTicksMS();
		pevt.EventID = MOUSE_CHANGE_STATE;	//Tell object that the mouse was released over it
		pevt.eWord1 = (ps2MouseId << 16) | mstate;
		pevt.eWord2 = x;
		pevt.eWord3 = y;
		pevt.eWord4 = scroll;
		pevt.eWord5 = 0x54321;

		SendProcessEvent(GetUiProcess(),&pevt);

	}
    else if (ps2MouseIRQs>5) {
        ps2MouseIRQs = 0;
    }
	EOI();
}

void	i8042KeyboardHandler() {
    PROCESS_EVENT pevt;
    UINT32 k = inportb(0x60);

    if (i8042ExtKey) {
		if (i8042ExtKey == 1 && ((k == 0x2a || k == 0xB7)) ) {
			i8042Key = 	0xE000 | (k & 0x7F);
			i8042ExtKey = 9;
//			printf ("%x,",k);
			EOI();
			return;
		}

		if (i8042ExtKey == 9 && k == 0xE0) {
			EOI();
			return;
		}

		if (i8042ExtKey == 1)
			i8042Key = (k & 0x7F) << 8;
		else
			i8042Key = (i8042Key << 8) | (k & 0x7F);

		if (--i8042ExtKeyCount > 0) {
//			printf ("%x,",k);
			EOI();
			return;
		}

		if (i8042ExtKey == 9 && i8042Key == 0xe0372a) {
			i8042Key = 0xe02a37;
		}

		i8042ExtKey = 0;
//		printf ("%x>",k);
	}
	else if (k == 0xE0) {
		i8042ExtKey = 1;
		i8042ExtKeyCount = 1;
		i8042Key = 0;
//		printf("<<%x,",k);
	    EOI();
		return;
	}
	else if (k == 0xE1) {
		i8042ExtKey=2;
		i8042ExtKeyCount = 2;
		i8042Key = 0xE1;
//		printf("<<<%x,",k);
	    EOI();
		return;
	}
	else {
        i8042Key = (k & 0x7F) & 0xFF;
//		printf("<%x>",k);
	}

	pevt.EventClass = EVT_KEYBOARD_EVENT;
	pevt.EventTime  = GetTicksMS();
	pevt.eWord1 = ps2KeyboardId;
	pevt.eWord2 = i8042Key;
	pevt.eWord3 = 0;
	pevt.eWord4 = 0;

    if (k & 0x80) {
		pevt.EventID = KEY_RELEASE;	//Tell object that the mouse was released over it
	}
	else {
		pevt.EventID = KEY_DEPRESS;	//Tell object that the mouse was released over it
	}

	//printf("%x", k);
	if (!(k & 0x80) && k == 0x3C) {
		DisableInterrupts();
		ClearScreen();
		EnableInterrupts();
//		RenDraw();
		ResetXY();
		DisplayProcesses();
	}

	SendProcessEvent(GetUiProcess(), &pevt);
//	printf("\r\n<ievt:%i>", pevt.EventID);
    EOI();
	return;
}
