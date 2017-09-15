// 
// 
// 

#include "DisplayChronometer.h"

DisplayChronometer::DisplayChronometer() :
	LedControl(PIN_DIN, PIN_CLK, PIN_LOAD)
{
}

DisplayChronometer::DisplayChronometer(int buzzerPinOutput) :
	LedControl(PIN_DIN, PIN_CLK, PIN_LOAD)
{
	digitalBuzzerOutput = buzzerPinOutput;
}

void DisplayChronometer::begin()
{
	shutdown(0, false);
	setIntensity(0, 10);
	clearDisplay(0);
	if(digitalBuzzerOutput != 0)
	{
		pinMode(digitalBuzzerOutput, OUTPUT);
		digitalWrite(digitalBuzzerOutput, LOW);  //Buzzer Off at startup
	}
}

void DisplayChronometer::writeTest()
{
	for (int i = 0; i<8; i++) {
		setDigit(0, i, i + 1, (i + 1) % 2 == 0);
		delay(1000);
	}
}

void DisplayChronometer::turnBuzzerOn()
{
	if(digitalBuzzerOutput != 0)
		digitalWrite(digitalBuzzerOutput, HIGH);
}

void DisplayChronometer::turnBuzzerOff()
{
	if (digitalBuzzerOutput != 0)
		digitalWrite(digitalBuzzerOutput, LOW);
}



