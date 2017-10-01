// 
// 
// 

#include "SearchAndDestroy.h"

SearchAndDestroy::SearchAndDestroy(int _buzzerPin, DisplayLcd& _display, DisplayLcdKeypad& _displayKeypad)
	: AirsoftGame(_buzzerPin, _display, _displayKeypad)
{
}

void SearchAndDestroy::startGame()
{
	startGameTimer();
	search();
}


void SearchAndDestroy::search()
{
	display.reset();
	while (true)
	{
		printGameTimer();
	}
}

void SearchAndDestroy::destroy()
{
}
