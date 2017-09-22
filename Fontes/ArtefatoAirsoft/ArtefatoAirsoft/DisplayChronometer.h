// DisplayChronometer.h

#ifndef _DISPLAYCHRONOMETER_h
#define _DISPLAYCHRONOMETER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include<LedControl.h>

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

private: //methods
	void turnBuzzerOn();
	void turnBuzzerOff();


private: //properties
	int digitalBuzzerOutput = 0;
	int firstnum = 0;
	int secondnum = 0;
	int thirdnum = 0;
	int fournum = 0;
	int fivenum = 0;
	int sixnum = 0;
	int sevennum = 0;
	int eightnum = 0;

	long int countnumber = 24001000;
};

#endif

