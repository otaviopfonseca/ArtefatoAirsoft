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

const int KEYPAD_ENABLE_PIN = 3;

MembraneKeypad::MembraneKeypad() : 
	Keypad(makeKeymap(KEYS), ROW_PINS, COL_PINS, ROWS_MEMBRANE, COLUMNS_MEMBRANE)
{
	pinMode(KEYPAD_ENABLE_PIN, INPUT);
}

void MembraneKeypad::begin(void(*listener)(char))
{
	setHoldTime(50);
	setDebounceTime(50);
	addEventListener(listener);	
}

int MembraneKeypad::getRealNumber()
{	
	char keyPressed = '\0';
	
	while (true) 
	{
		keyPressed = getKeyPressed();
		if (keyPressed) 
		{//
			switch (keyPressed) 
			{
				case '1': return 1;
				case '2': return 2;
				case '3': return 3;
				case '4': return 4;
				case '5': return 5;
				case '6': return 6;
				case '7': return 7;
				case '8': return 8;
				case '9': return 9;
				case '0': return 0;
				default: return 11;
			}
		}
		return 11;
	}
}

char MembraneKeypad::getKeyPressed()
{
	if (!checkEnable())
		return '\0';
	return this->waitForKey();
}

bool MembraneKeypad::checkEnable()
{	
	return digitalRead(KEYPAD_ENABLE_PIN) == HIGH;
}
