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
#include "GameKeypad.h"

class AirsoftGame {

protected:
	int gameMinutes;
	int bombMinutes;
	int activateSeconds;
	bool soundEnable;
	bool mosfetEnable;
	bool usePassword;
	bool gameOver;
	CountDown gameTimer;
	CountDown bombTimer;
	CountDown armingTimer;
	DisplayChronometer mainChronometer;
	MembraneKeypad mainKeypad;
	DisplayLcd& display;
	DisplayLcdKeypad& keypad;
	int buzzerPin;
	String password;
	String passwordMirror;
	static GameKeypad gameKeypad;
	static bool arming;
	static bool defusing;
	void startGameTimer();
	void startBombTimer();
	void printGameTimer();
	void printBombTimer();
	void setCode();
	bool comparePassword();
	void beep();
	void beepError();
	void disarmedSplash();
	void explodeSplash();
	
public:
	AirsoftGame(int, DisplayLcd&, DisplayLcdKeypad&);
	void configGame();
	virtual void startGame() = 0;
	static void armingDesarmingEvent(KeypadEvent key);
	static void begin();

private:
	void configGameTime();
	void configBombTime();
	void configActivateTime();
	void configSound();
	void configMosfet();
	void configPassword();
	void setNewPass();
	void setPass();
	String getTimeString(int hours, int minutes, int seconds, int miliseconds);
	void startGameCountdown();
};

#endif

