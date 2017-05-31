
#pragma once

#include <mtos.h>
#include <mtox.h>

IMPORT BYTE ps2MouseBuffer[32];
IMPORT BYTE	ps2MouseType;
IMPORT UINT32	ps2MouseId;
IMPORT UINT32  ps2MouseIRQs;

IMPORT UINT32  ps2KeyboardId;
IMPORT UINT8  	i8042ExtKey;
IMPORT UINT8	i8042ExtKeyCount;
IMPORT UINT32  i8042Key;



#define STATUS_PORT			0x64
#define KBD_OUT_BUF			0x60
#define KBD_INPT_BUF        0x60
#define KBD_CMD_BUF         0x64
#define KBD_DATA_BUF        0x60
#define PORT_A              0x60
#define PORT_B              0x61

#define PS2_OUTPUT_BUFFER_FULL          01
#define PS2_INPUT_BUFFER_FULL           02

//PS2 Controller Commands
#define PS2_CTRL_ENABLE_CH1             0xAE
#define PS2_CTRL_ENABLE_CH2             0xA8
#define PS2_CTRL_DISABLE_CH1            0xAD
#define PS2_CTRL_DISABLE_CH2            0xA7
#define PS2_CTRL_SELF_TEST              0xAA
#define PS2_CTRL_TEST_KB_PORT           0xAB
#define PS2_CTRL_TEST_MOUSE_PORT        0xA9
#define PS2_CTRL_TEST_MOUSE_PORT        0xA9
#define PS2_CTRL_WRITE_MOUSE_PORT       0xD4


//PS2 Commands
#define PS2_RESET               0xFF
#define PS2_ECHO                0xFE
#define PS2_ENABLE              0xF4
#define PS2_DISABLE             0xF5
#define PS2_SET_DEFAULTS        0xF6
#define PS2_SET_SAMPLE_RATE     0xF3

#define PS2_REPEAT                  0xF7
#define PS2_WRITE_KB_LEDS_CMD       0xED

#define PS2_MOUSE_SET_SCALING11     0xE6
#define PS2_MOUSE_SET_SCALING21     0xE7
#define PS2_MOUSE_SET_RESOLUTION    0xE8
#define PS2_MOUSE_GET_INFO          0xE9
#define PS2_MOUSE_GET_ID            0xF2

//PS2 Responses
#define PS2_OK              0xAA
#define PS2_ACK             0xFA
#define KB_OVERRUN          0xFF
#define KB_RESEND           0xFE
#define KB_BREAK            0xF0
#define KB_FA               0x10
#define KB_FE               0x20
#define KB_PR_LED           0x40


#define MOUSE_LEFTBTN      1
#define MOUSE_RIGHTBTN     2
#define MOUSE_MIDBTN       4

//#define PS2_RETRIES 50
#define PS2_RETRIES 10000
EXPORTSTART

	void    i8042Init(void);
	void	i8042MouseHandler(void);
	void	i8042KeyboardHandler(void);
	void	InitI8042Interrupts(void);
	void	i8042Reset(void);
	void 	ps2ReadWait(void);
	void 	ps2WriteWait(void);
	void 	ps2DataWrite(UINT32 data);
	UINT32 	ps2DataRead(void);
	void 	ps2CtrlWrite(UINT32 ps2Command);
	void 	ps2MouseWrite(UINT32 ps2Command);
	BOOL 	ps2GetDeviceIdX(void);
	BOOL 	ps2SetSampleRateX(UINT32 sRate);
	BOOL 	ps2SetResolutionX(UINT32 sRes);
	BOOL 	ps2SetScalingX(UINT32 scaling);
	BOOL 	ps2EnableX(void);
	BOOL 	ps2MouseResetX(void);
	void	ps2DisableKeyboard(void);
	void	ps2EnableKeyboard(void);
	void	ps2DisableMouse(void);
	void	ps2EnableMouse(void);
	void	ps2MouseReset(void);
	void    ps2SetKeyboardLEDs(UINT32 kbLeds);
	void    ps2SetTypematicRate(UINT32 kbRate);
	void	i8042MouseHandler(void);
	void	i8042KeyboardHandler(void);

EXPORTEND

extern BYTE	ps2MouseType;
