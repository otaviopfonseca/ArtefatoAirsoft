// 
// 
// 

#include "DisplayLcd.h"

byte bar1[8] = {
	B10000,
	B10000,
	B10000,
	B10000,
	B10000,
	B10000,
	B10000,
	B10000,
};
byte bar2[8] = {
	B11000,
	B11000,
	B11000,
	B11000,
	B11000,
	B11000,
	B11000,
	B11000,
};
byte bar3[8] = {
	B11100,
	B11100,
	B11100,
	B11100,
	B11100,
	B11100,
	B11100,
	B11100,
};
byte bar4[8] = {
	B11110,
	B11110,
	B11110,
	B11110,
	B11110,
	B11110,
	B11110,
	B11110,
};
byte bar5[8] = {
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
};
byte up[8] = {
	B00000,
	B00100,
	B01110,
	B11111,
	B11111,
	B00000,
	B00000,
};

byte down[8] = {
	B00000,
	B00000,
	B11111,
	B11111,
	B01110,
	B00100,
	B00000,
};

DisplayLcd::DisplayLcd() :
	LiquidCrystal(PIN_RS, PIN_ENABLE, PIN_D4, PIN_D5, PIN_D6, PIN_D7)
{
	createChar(0, bar1);
	createChar(1, bar2);
	createChar(2, bar3);
	createChar(3, bar4);
	createChar(4, bar5);
	createChar(5, up);
	createChar(6, down);
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

void DisplayLcd::checkArrows(byte i, byte maxx) 
{
	if (i == 0) {
		setCursor(15, 1);
		write(6);
	}
	if (i == maxx) {
		setCursor(15, 0);
		write(5);
	}
	if (i>0 && i<maxx) {
		setCursor(15, 1);
		write(6);
		setCursor(15, 0);
		write(5);
	}
}

