// AirsoftGame.h

#ifndef _AIRSOFTGAME_h
#define _AIRSOFTGAME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "CountDown.h"
#include "DisplayLcd.h"
#include "DisplayLcdKeypad.h"
#include "DisplayChronometer.h"
#include "MembraneKeypad.h"

class AirsoftGame {

protected:
	int gameMinutes;
	int bombMinutes;
	int activateSeconds;
	CountDown gameTimer;
	CountDown bombTimer;
	DisplayChronometer mainChronometer;
	MembraneKeypad mainKeypad;
	DisplayLcd& display;
	DisplayLcdKeypad& keypad;
	int buzzerPin;
	
public:
	AirsoftGame(int, DisplayLcd&, DisplayLcdKeypad&);
	void configGame();

private:
	void configGameTime();
	void beep();

};

#endif

