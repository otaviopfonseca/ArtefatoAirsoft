// GameKeypad.h

#ifndef _GAMEKEYPAD_h
#define _GAMEKEYPAD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Keypad.h>

#define ROWS_GAME_KEYPAD 1
#define COLUMNS_GAME_KEYPAD 2

class GameKeypad : public Keypad 
{

public:
	static const char RED_BUTTON_TEAM = 'R';
	static const char GREEN_BUTTON_TEAM = 'G';

public:
	GameKeypad();

};

#endif

