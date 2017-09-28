// 
// 
// 

#include "AirsoftGame.h"

AirsoftGame::AirsoftGame(int _buzzerPin, DisplayLcd & _display, DisplayLcdKeypad & _displayKeyboard) 
	: display(_display), keypad(_displayKeyboard)
{
	gameTimer = CountDown();
	bombTimer = CountDown();
	mainChronometer = DisplayChronometer(_buzzerPin);
	mainKeypad = MembraneKeypad();
	buzzerPin = _buzzerPin;
}

void AirsoftGame::configGame()
{

}

void AirsoftGame::configGameTime()
{
	byte timeAux[4];
	display.reset();
	display.print("Tempo de Jogo:");
	delay(100);
	display.setCursorDown();
	display.print("00:00 hh:mm");
	display.cursor();
	display.blink();
	display.setCursorDown();
	byte var2 = 0;
	for (int i = 0; i<4; i++) 
	{
		while (true) 
		{
			if (i == 2 && var2 == 0) 
			{
				display.print(":");
				var2 = 1;
			}

			byte varu = mainKeypad.getRealNumber();
			if (varu != 11) {

				timeAux[i] = varu;
				Serial.print(varu);
				display.print(varu);
				beep();
				break;
			}
		}
	}
	display.noCursor();
	display.noBlink();
	display.setCursor(13, 1);
	display.print("ok?");

	while (true) {
		DisplayLcdButton buttonPressed = keypad.waitForKey();
		if (buttonPressed == DisplayLcdButton::Select) 
		{
			beep();
			gameMinutes = ((timeAux[0] * 600) + (timeAux[1] * 60) + (timeAux[2] * 10) + (timeAux[3]));
			break;
		}
		else
		{
			configGameTime();
		}
	}
	display.reset();
}

void AirsoftGame::beep()
{
	tone(buzzerPin, 2400, 30);
}


