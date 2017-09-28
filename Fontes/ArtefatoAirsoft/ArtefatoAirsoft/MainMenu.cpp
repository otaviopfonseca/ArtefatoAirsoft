// 
// 
// 

#include "MainMenu.h"
#include "AirsoftGame.h"
#include "SearchAndDestroy.h"
#include "Sabotage.h"

const String menu[] = { "Proc. e Destruir", "Sabotage", "Dominacao" };

MainMenu::MainMenu(int _buzzerPin, DisplayLcdKeypad& _keypad, DisplayLcd& _display)
	: displayKeypad(_keypad), displayLcd(_display) 
{ 
	buzzerPin = _buzzerPin;
}

AirsoftGame MainMenu::getSelectedGame()
{
	int gameIndex = 0;
	displayLcd.reset();
	displayLcd.print("Sel. Modo de Jogo: ");
	DisplayLcdButton buttonPressed = DisplayLcdButton::None;	
	delay(2000);
	displayLcd.reset();	
	displayLcd.print(menu[gameIndex]);
	displayLcd.setCursor(15, 1);
	displayLcd.checkArrows(gameIndex, 2);
	while (true)
	{
		buttonPressed = displayKeypad.waitForKey();
		if (buttonPressed == DisplayLcdButton::Up && gameIndex > 0) {
			tone(buzzerPin, 2400, 30);
			gameIndex--;
			displayLcd.reset();
			displayLcd.print(menu[gameIndex]);
			displayLcd.checkArrows(gameIndex, 2);
			delay(50);
		}

		if (buttonPressed == DisplayLcdButton::Down && gameIndex < 2) {
			tone(buzzerPin, 2400, 30);
			gameIndex++;
			displayLcd.reset();
			displayLcd.print(menu[gameIndex]);
			displayLcd.checkArrows(gameIndex, 2);
			delay(50);
		}

		if (buttonPressed == DisplayLcdButton::Select)
		{
			tone(buzzerPin, 2400, 30);
			return getGameByIndex(gameIndex);
		}
	}
	return AirsoftGame(buzzerPin, displayLcd, displayKeypad);
}

AirsoftGame MainMenu::getGameByIndex(int gameIndex)
{
	/*switch (gameIndex)
	{
		case 0:
			return SearchAndDestroy();
		case 1: 
			return Sabotage();
		case 3:
			return Domination();
		default:
			return SearchAndDestroy();
	}*/
	return AirsoftGame(buzzerPin, displayLcd, displayKeypad);
}