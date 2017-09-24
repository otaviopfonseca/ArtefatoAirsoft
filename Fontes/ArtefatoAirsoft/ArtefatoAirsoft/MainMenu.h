// MainMenu.h

#ifndef _MAINMENU_h
#define _MAINMENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "DisplayLcdKeypad.h"
#include "DisplayLcd.h"
#include "AirsoftGame.h"

class MainMenu {
private: 
	DisplayLcdKeypad& displayKeypad;
	DisplayLcd& displayLcd;
	int buzzerPin;

public:
	MainMenu(int, DisplayLcdKeypad&, DisplayLcd&);
	AirsoftGame getSelectedGame();
};

#endif

