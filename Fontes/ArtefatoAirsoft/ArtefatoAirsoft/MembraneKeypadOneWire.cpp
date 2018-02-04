// 
// 
// 

#include "MembraneKeypadOneWire.h"


char KEYS_ANALOG_ONE_WIRE_KEYPAD[] = {
	'A','3','2','1',
	'B','6','5','4',
	'C','9','8','7',
	'D','#','0','*'
};

MembraneKeypadOneWire::MembraneKeypadOneWire()
	: OnewireKeypad(Serial, KEYS_ANALOG_ONE_WIRE_KEYPAD, ROWS, COLUMNS, PIN, ROW_RES, COL_RES)
{
	//SetHoldTime(1000);
}

int MembraneKeypadOneWire::getRealNumber()
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

char MembraneKeypadOneWire::getKeyPressed()
{
	char keyPressed = ONE_WIRE_NO_KEY;
	while (keyPressed == ONE_WIRE_NO_KEY)
	{
		keyPressed = this->Getkey();
	}
	return keyPressed;
}

char MembraneKeypadOneWire::waitForKey()
{
	return getKeyPressed();
}

