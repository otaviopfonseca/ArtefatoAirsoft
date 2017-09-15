// 
// 
// 

#include "DisplayLcd.h"


DisplayLcd::DisplayLcd() :
	LiquidCrystal(PIN_RS, PIN_ENABLE, PIN_D4, PIN_D5, PIN_D6, PIN_D7)
{
}

void DisplayLcd::begin()
{
	LiquidCrystal::begin(NUM_COLUMNS, NUM_ROWS);
}

void DisplayLcd::reset()
{
	LiquidCrystal::clear();
	this->setCursorUp();
}

void DisplayLcd::setCursorUp()
{
	LiquidCrystal::setCursor(LINE_BEGIN, LINE_UP);
}

void DisplayLcd::setCursorDown()
{
	LiquidCrystal::setCursor(LINE_BEGIN, LINE_DOWN);
}

