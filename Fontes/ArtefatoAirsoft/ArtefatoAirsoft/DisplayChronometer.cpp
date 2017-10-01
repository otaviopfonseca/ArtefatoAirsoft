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
	timer = CountDown(CountDown::Resolution::MILLIS);
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
	while (timer.remaining() > 0 && timer.isRunning())
	{
		printCurrentTime();
	}
}

void DisplayChronometer::start()
{
	if (initialTimeMilis > 0)
		timer.start(initialTimeMilis);
}

void DisplayChronometer::start(int minutes, int seconds)
{
	initialTimeMilis = calculateMiliseconds(minutes, seconds);
	timer.start(initialTimeMilis);
	printCurrentTime();
}

void DisplayChronometer::setStartTime(int minutes, int seconds)
{
	initialTimeMilis = calculateMiliseconds(minutes, seconds);
	printCurrentTime();
}

void DisplayChronometer::reset()
{
	fillDigits("000000");
	timer.stop();	
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

void DisplayChronometer::tickBuzzer()
{
	turnBuzzerOn();
	delay(50);
	turnBuzzerOff();
}

void DisplayChronometer::printCurrentTime()
{
	long currentMilis = timer.remaining();
	if (currentMilis <= 0)
		currentMilis = 0;
	long minutes = (currentMilis / 60000);
	long seconds = (currentMilis / 1000) % 60;
	long miliseconds = currentMilis % 1000;
	if (miliseconds < 100)
		tickBuzzer();
	String timeString = getTimeString(minutes, seconds, miliseconds);
	fillDigits(timeString);
}

String DisplayChronometer::getTimeString(int minutes, int seconds, int miliseconds)
{	
	String strMinutes = "";
	if (minutes < 10) 
		strMinutes += "0";
	strMinutes += minutes;

	String strSeconds = "";
	if (seconds < 10)
		strSeconds += "0";
	strSeconds += seconds;

	String strMilis = "";
	if (miliseconds < 100)
		strMilis += "0";
	if (miliseconds < 10)
		strMilis += "0";
	strMilis += miliseconds;
	
	return strMinutes + strSeconds + strMilis;
}

long DisplayChronometer::calculateMiliseconds(int minutes, int seconds)
{
	return (((((long)minutes) * 60) + (long)seconds) * 1000);;
}

void DisplayChronometer::fillDigits(String timeString)
{
	setChar(0, 1, timeString.charAt(6), false);
	setChar(0, 2, timeString.charAt(5), false);
	setChar(0, 3, timeString.charAt(4), false);
	setChar(0, 4, timeString.charAt(3), true);
	setChar(0, 5, timeString.charAt(2), false);
	setChar(0, 6, timeString.charAt(1), true);
	setChar(0, 7, timeString.charAt(0), false);
}



