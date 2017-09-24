// 
// 
// 

#include "MainMenu.h"

const String menu[] = { "Proc. e Destruir", "Sabotage", "Dominacao" };

MainMenu::MainMenu(int _buzzerPin, DisplayLcdKeypad& _keypad, DisplayLcd& _display)
	: displayKeypad(_keypad), displayLcd(_display) 
{ 
	buzzerPin = _buzzerPin;
}

AirsoftGame MainMenu::getSelectedGame()
{
	int i = 0;
	displayLcd.reset();
	
	DisplayLcdButton buttonPressed = DisplayLcdButton::None;	
	displayLcd.print(menu[i]);
	displayLcd.setCursor(15, 1);
	displayLcd.checkArrows(i, 2);
	while (true)
	{
		buttonPressed = displayKeypad.waitForKey();
		if (buttonPressed == DisplayLcdButton::Up && i > 0) {
			tone(buzzerPin, 2400, 30);
			i--;
			displayLcd.reset();
			displayLcd.print(menu[i]);
			displayLcd.checkArrows(i, 2);
			delay(50);
		}
		if (buttonPressed == DisplayLcdButton::Down && i < 2) {
			tone(buzzerPin, 2400, 30);
			i++;
			displayLcd.reset();
			displayLcd.print(menu[i]);
			displayLcd.checkArrows(i, 2);
			delay(50);
		}

	}
	return AirsoftGame();
}

