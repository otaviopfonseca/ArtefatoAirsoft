// DisplayLcdKeypad.h

#ifndef _DISPLAYLCDKEYPAD_h
#define _DISPLAYLCDKEYPAD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

const int ANALOG_BUTTON_READ_PIN = A0;
enum DisplayLcdButton
{
	Up,
	Down,
	Left,
	Right,
	Select,
	None
};

class DisplayLcdKeypad
{
public:
	DisplayLcdKeypad();
	DisplayLcdButton getKeyPressed();
	String getKeyPressedDescription();
	String getKeyPressedDescription(DisplayLcdButton);

private:
	DisplayLcdButton readLcdButtons();
};
#endif

