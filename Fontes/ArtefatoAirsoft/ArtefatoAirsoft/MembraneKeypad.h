// MembraneKeypad.h

#ifndef _MEMBRANEKEYPAD_h
#define _MEMBRANEKEYPAD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Keypad.h>
#define ROWS_MEMBRANE 4
#define COLUMNS_MEMBRANE 4


class MembraneKeypad : public Keypad
{
public:
	MembraneKeypad();
	void begin(void(*listener)(char));

};
#endif

