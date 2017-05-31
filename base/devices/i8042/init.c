#define _MTOX_FILESYS
#define _MTOX_UI

#include "i8042.h"
    
//UINT32 inMouse=0;

#define xx_printf(str,...) ;//

#include "i8042.h"

void    i8042Init() {
    UINT32 sb;
    UINT8 mtype=3;
    ps2MouseType = 4;

//    printf("ps2Reset");

//	ps2DisableKeyboard();

	ps2MouseWrite(0xF5);

    ps2CtrlWrite(0xA8);
    ps2CtrlWrite(0x20);

    sb = 2 | (0xDF & ps2DataRead());

    ps2CtrlWrite(0x60);
    ps2DataWrite(sb);

    ps2MouseWrite(0xF6);
    ps2DataRead();

//    printf("<SetSampleRate>");    //Enable scroll
    if (!ps2SetSampleRateX(200) || !ps2SetSampleRateX(100) ||
        !ps2SetSampleRateX(80))
        return;

//    printf("<GetDevice>");

    if (!ps2GetDeviceIdX())
        return;

    if (ps2MouseType != 0) mtype=4;

//    printf("<SetSampleRate2>");   //Enable 5buttons
    if (!ps2SetSampleRateX(200) || !ps2SetSampleRateX(200)||
        !ps2SetSampleRateX(80))
        return;

 //   printf("<GetDeviceID>");
    if (!ps2GetDeviceIdX())
        return;

//    printf("<SetSampleRate>");    //Set samplerate
    ps2SetSampleRateX(0x28);
//    printf("<GetDeviceID>");
	ps2GetDeviceIdX();

//    printf("<SetRes>");
	ps2SetResolutionX(3);
//    printf("<SetScaling>");

	ps2SetScalingX(PS2_MOUSE_SET_SCALING11);
	
	DisableInterrupts();
	
    ps2MouseWrite(0xF4);
    ps2DataRead();

	ps2MouseIRQs = 0;
    ps2MouseType = 4;

    ps2MouseType = mtype;

//	ps2EnableKeyboard();

//	ps2SetKeyboardLEDs(7);
//	ps2SetTypematicRate(0);
	
//    printf("RegKYB");
    ps2KeyboardId = OSRegisterKeyboard();
    ps2MouseId = OSRegisterMouse();
//    printf("Done::%i",ps2MouseId );

    InitI8042Interrupts();
    cprintf("Done 8042 mtyp%i\r\n",mtype);
	
	EnableInterrupts();

    return;

}


void InitI8042Interrupts() {
	ApicSetLegacyInterruptVector(1,(INTHANDLER)i8042KeyboardHandler);
    ApicSetLegacyInterruptVector(12,(INTHANDLER)i8042MouseHandler);

}
