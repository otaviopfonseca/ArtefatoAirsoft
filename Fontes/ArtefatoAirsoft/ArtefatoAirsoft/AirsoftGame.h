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
	bool soundEnable;
	bool mosfetEnable;
	bool usePassword;
	CountDown gameTimer;
	CountDown bombTimer;
	DisplayChronometer mainChronometer;
	MembraneKeypad mainKeypad;
	DisplayLcd& display;
	DisplayLcdKeypad& keypad;
	int buzzerPin;
	String password;
	String passwordMirror;
	
public:
	AirsoftGame(int, DisplayLcd&, DisplayLcdKeypad&);
	void configGame();

private:
	void configGameTime();
	void configBombTime();
	void configActivateTime();
	void configSound();
	void configMosfet();
	void configPassword();
	void setNewPass();
	void setPass();
	void setCode();
	void beep();
	bool comparePassword();
	

};

#endif

