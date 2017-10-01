// DisplayChronometer.h

#ifndef _DISPLAYCHRONOMETER_h
#define _DISPLAYCHRONOMETER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include<LedControl.h>
#include "CountDown.h"

const int PIN_CLK = 11;
const int PIN_DIN = 13;
const int PIN_LOAD = 12;

class DisplayChronometer : public LedControl
{
public:
	DisplayChronometer();
	DisplayChronometer(int);
	void begin();
	void writeTest();
	void start();
	void start(int, int);
	void setStartTime(int, int);
	void reset();
	void printCurrentTime();

private: //methods
	void turnBuzzerOn();
	void turnBuzzerOff();
	void tickBuzzer();
	String getTimeString(int, int, int);
	long calculateMiliseconds(int, int);
	void fillDigits(String);

private: //properties
	CountDown timer;
	int digitalBuzzerOutput;
	long initialTimeMilis;
};

#endif

