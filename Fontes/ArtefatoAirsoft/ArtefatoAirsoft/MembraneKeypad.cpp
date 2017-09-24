// 
// 
// 

#include "MembraneKeypad.h"

byte ROW_PINS[ROWS_MEMBRANE] = { 14, 15, 16, 17 };
byte COL_PINS[COLUMNS_MEMBRANE] = { 18, 19, 20, 21 };
char KEYS[ROWS_MEMBRANE][COLUMNS_MEMBRANE] =
{
	{ '1', '2', '3', 'A' },
	{ '4', '5', '6', 'B' },
	{ '7', '8', '9', 'C' },
	{ '*', '0', '#', 'D' }
};

MembraneKeypad::MembraneKeypad() : 
	Keypad(makeKeymap(KEYS), ROW_PINS, COL_PINS, ROWS_MEMBRANE, COLUMNS_MEMBRANE)
{
	
}

void MembraneKeypad::begin(void(*listener)(char))
{
	setHoldTime(50);
	setDebounceTime(50);
	addEventListener(listener);	
}
