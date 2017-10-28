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
		if (GameKeypad::RED_BUTTON_TEAM == gameKeypad.getKey() && usePassword) 
		{
			display.clear();
			display.setCursor(2, 0);
			display.print("ARMANDO BOMBA");
			delay(1000);
			display.clear();
			display.setCursor(0, 0);
			display.print("DIGITE A SENHA");
			setCode();
			if (comparePassword()) {
				destroy();
			}
			display.clear();
			display.setCursor(3, 0);
			display.print("SENHA INVALIDA");
			if (soundEnable)
				beepError();
			delay(500);
			display.reset();
		}

		while (arming && !usePassword)
		{			
			display.reset();
			display.setCursor(2, 0);
			display.print("ARMANDO BOMBA");
			display.setCursorDown();
			unsigned int percent = 0;
			unsigned long timeCalcVar = 0;
			while (arming)
			{
				if(!armingTimer.isRunning())
					armingTimer.start(activateSeconds * 1000);

				gameKeypad.getKey();
				timeCalcVar = armingTimer.remaining();

				unsigned long seconds = armingTimer.remaining() / 1000;
				percent = (((float)activateSeconds - (float)seconds) / ((float)activateSeconds) * 100.0);
				display.drawPorcent(percent);
				if (percent >= 100)
				{					
					destroy();
				}
			}
			display.reset();
		}
		if (gameOver)
			return;
	}
}

void SearchAndDestroy::destroy()
{
	arming = false;
	defusing = false;
	display.clear();
	display.setCursor(3, 0);
	display.print("BOMBA ARMADA");
	delay(1000);
	gameTimer.stop();	
	startBombTimer();
	armingTimer.stop();
	
	while (true) 
	{
		printBombTimer();
		if (GameKeypad::GREEN_BUTTON_TEAM == gameKeypad.getKey() && usePassword) 
		{
			display.clear();
			display.setCursorDown();
			display.print("DESARMANDO");
			delay(1000);
			display.clear();
			display.setCursorUp();
			display.print("DIGITE A SENHA");

			setCode();
			if (comparePassword()) 
				disarmedSplash();
			
			display.clear();
			display.setCursor(3, 0);
			display.print("SENHA INVALIDA");
			display.reset();
		}

		if (defusing && !usePassword)// disarming bomb
		{
			display.clear();
			display.setCursor(3, 0);
			display.print("DESARMANDO");
			display.setCursor(0, 1);
			unsigned int percent = 0;
			unsigned long timeCalcVar = 0;
			while (defusing)
			{
				if (!armingTimer.isRunning())
					armingTimer.start(activateSeconds * 1000);

				gameKeypad.getKey();
				timeCalcVar = armingTimer.remaining();

				unsigned long seconds = armingTimer.remaining() / 1000;
				percent = (((float)activateSeconds - (float)seconds) / ((float)activateSeconds) * 100.0);
				display.drawPorcent(percent);
				if (percent >= 100)
					disarmedSplash();
			}
		}
		if (gameOver)
			return;
	}
}
