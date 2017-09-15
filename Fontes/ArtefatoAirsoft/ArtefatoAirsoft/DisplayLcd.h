// DisplayLcd.h

#ifndef _DISPLAYLCD_h
#define _DISPLAYLCD_h 1

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

const int PIN_RS = 8;
const int PIN_ENABLE = 9;
const int PIN_D4 = 4;
const int PIN_D5 = 5;
const int PIN_D6 = 6;
const int PIN_D7 = 7;

const int LINE_BEGIN = 0;
const int LINE_UP = 0;
const int LINE_DOWN = 1;

const int NUM_ROWS = 2;
const int NUM_COLUMNS = 16;

#include <LiquidCrystal.h>


class DisplayLcd : public LiquidCrystal
{

private: //Propriedades
	int CursorAtual = 0;	

public: //Métodos
	DisplayLcd();
	void begin();
	void reset();
	void setCursorUp();
	void setCursorDown();
};

#endif

