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

		while (armingOrDefusing && !usePassword)
		{			
			display.reset();
			display.setCursor(2, 0);
			display.print("ARMANDO BOMBA");
			display.setCursorDown();
			unsigned int percent = 0;
			unsigned long xTime = millis(); 
			unsigned long timeCalcVar = 0;
			while (armingOrDefusing)
			{
				if(!armingTimer.isRunning())
					armingTimer.start(activateSeconds * 1000);

				gameKeypad.getKey();
				timeCalcVar = armingTimer.remaining();

				unsigned long seconds = armingTimer.remaining() / 1000;
				percent = (((float)activateSeconds - (float)seconds) / ((float)activateSeconds) * 100.0);
				display.drawPorcent(percent);
				/*String remaining = "Segundos: ";
				Serial.println(remaining += seconds);*/
				/*String percentual = "Percentual: ";
				Serial.println(percentual += percent);*/
				if (percent >= 100)
				{					
					destroy();
				}
			}
			display.reset();
		}
	}
}

void SearchAndDestroy::destroy()
{
	display.clear();
	display.setCursor(3, 0);
	display.print("BOMBA ARMADA");
	delay(1000);
	int minutos = bombMinutes - 1;
	unsigned long iTime = millis();
	unsigned long aTime;
	int largoTono = 50;
	gameTimer.stop();	
	startBombTimer();
	//MAIN LOOP
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
			if (comparePassword()) {
				//disarmedSplash(); TODO
			}
			display.clear();
			display.setCursor(3, 0);
			display.print("SENHA INVALIDA");
			display.reset();
		}

		if (armingOrDefusing && !usePassword)// disarming bomb
		{
			display.clear();
			
			display.setCursor(3, 0);
			display.print("DESARMANDO");
			display.setCursor(0, 1);
			unsigned int percent = 0;
			unsigned long xTime = millis();
			//while (defuseando)
			//{
			//	keypad.getKey();
			//	//check if game time runs out during the disabling
			//	aTime = millis() - iTime;
			//	if ((minutos - aTime / 60000 == 0 && 59 - ((aTime / 1000) % 60) == 0) || minutos - aTime / 60000>4000000000) {
			//		endGame = true;
			//	}
			//	timeCalcVar = (millis() - xTime) % 1000;
			//	if (timeCalcVar >= 0 && timeCalcVar <= 20)
			//	{
			//		digitalWrite(GREENLED, HIGH);
			//		if (soundEnable)tone(tonepin, tonoAlarma1, 200);
			//	}
			//	if (timeCalcVar >= 480 && timeCalcVar <= 500)
			//	{
			//		if (soundEnable)tone(tonepin, tonoAlarma2, 200);
			//		digitalWrite(GREENLED, LOW);
			//	}
			//	unsigned long seconds = (millis() - xTime);
			//	percent = seconds / (ACTIVATESECONDS * 10);
			//	drawPorcent(percent);

			//	//BOMB DISARMED GAME OVER
			//	if (percent >= 100)
			//	{
			//		disarmedSplash();
			//	}
			//}
			//digitalWrite(REDLED, LOW);
			//digitalWrite(GREENLED, LOW);
			//cls();
		}
	}
}
