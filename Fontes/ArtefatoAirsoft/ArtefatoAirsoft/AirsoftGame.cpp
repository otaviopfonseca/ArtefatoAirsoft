// 
// 
// 

#include "AirsoftGame.h"

const unsigned int PASSWORD_SIZE = 8;

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
	configGameTime();
	display.reset();
	configBombTime();
	display.reset();
	configActivateTime();
	display.reset();
	configSound();
	display.reset();
	configMosfet();
	display.reset();
	configPassword();
}

void AirsoftGame::configGameTime()
{
	byte decompositeTime[4];
	display.reset();
	display.print("TEMPO DE JOGO:");
	delay(100);
	display.setCursorDown();
	display.print("00:00 hh:mm");
	display.cursor();
	display.blink();
	display.setCursorDown();
	byte cursorPosition = 0;
	for (int indexTimeChar = 0; indexTimeChar<4; indexTimeChar++) 
	{
		while (true) 
		{
			if (indexTimeChar == 2 && cursorPosition == 0) 
			{
				display.print(":");
				cursorPosition = 1;
			}

			byte buttonPressedValue = mainKeypad.getRealNumber();
			if (buttonPressedValue != 11)
			{
				decompositeTime[indexTimeChar] = buttonPressedValue;
				display.print(buttonPressedValue);
				beep();
				break;
			}
		}
	}
	display.noCursor();
	display.noBlink();
	display.setCursor(13, 1);
	display.print("OK?");

	while (true) 
	{
		DisplayLcdButton buttonPressed = keypad.waitForKey();
		if (buttonPressed == DisplayLcdButton::Select) 
		{
			beep();
			gameMinutes = ((decompositeTime[0] * 600) + (decompositeTime[1] * 60) + (decompositeTime[2] * 10) + (decompositeTime[3]));
			break;
		}
		else
		{
			configGameTime();
		}
	}
	display.reset();
}

void AirsoftGame::configBombTime()
{
	byte decompositeTime[2];
	display.reset();
	display.print("TEMPO DA BOMBA: ");
	delay(100);
	display.setCursorDown();
	display.print("00 MINUTOS");
	display.cursor();
	display.blink();
	display.setCursorDown();;
	for (int indexTimeChar = 0; indexTimeChar<2; indexTimeChar++)
	{
		while (true) 
		{
			byte buttonPressedValue = mainKeypad.getRealNumber();
			if (buttonPressedValue != 11)
			{
				decompositeTime[indexTimeChar] = buttonPressedValue;
				display.print(buttonPressedValue);
				beep();
				break;
			}
		}
	}
	display.noCursor();
	display.noBlink();
	display.setCursor(13, 1);
	display.print("OK?");

	while (true) 
	{
		DisplayLcdButton buttonPressed = keypad.waitForKey();
		if (buttonPressed == DisplayLcdButton::Select)
		{
			beep();
			bombMinutes = ((decompositeTime[0] * 10) + (decompositeTime[1]));
			break;
		}
		else
		{
			beep();
			configBombTime();
		}
	}
	beep();
	display.reset();
}

void AirsoftGame::configActivateTime()
{
	byte decompositeTime[2];
	display.reset();
	display.print("TEMPO PARA ARMAR:");
	delay(100);
	display.setCursor(0, 1);
	display.print("00 SEGUNDOS");
	display.cursor();
	display.blink();
	display.setCursorDown();
	for (int indexTimeChar = 0; indexTimeChar<2; indexTimeChar++)
	{
		while (true) 
		{
			byte varu = mainKeypad.getRealNumber();
			if (varu != 11) 
			{
				decompositeTime[indexTimeChar] = varu;
				display.print(varu); 
				beep();
				break;
			}
		}
	}
	display.noCursor();
	display.noBlink();
	display.setCursor(13, 1);
	display.print("OK?");

	while (true) 
	{
		DisplayLcdButton buttonPressed = keypad.waitForKey();
		if (buttonPressed == DisplayLcdButton::Select)
		{
			beep();
			activateSeconds = ((decompositeTime[0] * 10) + (decompositeTime[1]));
			break;
		}
		else
		{
			beep();
			configActivateTime();
		}
	}
	beep();
	display.reset();
}

void AirsoftGame::configSound()
{
	display.reset();
	display.print("ATIVAR SOM");
	display.setCursorDown();
	display.print("A : SIM B : NAO");
	char keyPressed = '\0';
	while (true)
	{
		keyPressed = mainKeypad.getKeyPressed();
		if (keyPressed == 'A') 
		{
			this->soundEnable = true;
			beep();
			break;
		}

		if (keyPressed == 'B') 
		{
			this->soundEnable = false;
			beep();
			break;
		}
	}
}

void AirsoftGame::configMosfet()
{
	display.reset();
	display.print("ATIVAR SIRENE");
	display.setCursorDown();
	display.print("A : SIM B : NAO");
	char keyPressed = '\0';
	while (true)
	{
		keyPressed = mainKeypad.getKeyPressed();
		if (keyPressed == 'A') 
		{
			this->mosfetEnable = true;
			beep();
			break;
		}
		if (keyPressed == 'B') 
		{
			this->mosfetEnable = false;
			beep();
			break;
		}
	}
}

void AirsoftGame::configPassword()
{
	display.reset();
	display.print("ATIVAR SENHA");
	display.setCursorDown();
	display.print("A : SIM B : NAO");
	char keyPressed = '\0';
	while (true)
	{
		keyPressed = mainKeypad.getKeyPressed();
		if (keyPressed == 'A') {
			beep();
			setNewPass();
			usePassword = true;
			break;
		}
		if (keyPressed == 'B') {
			beep();
			usePassword = false;
			break;
		}
	}
	beep();
}

void AirsoftGame::setNewPass() 
{
	display.reset();
	display.print("DIGITE A SENHA");
	setPass();

	display.reset();
	display.print("REDIGITE A SENHA");
	setCode();

	if (comparePassword()) 
	{
		display.reset();
		display.print("SENHA OK");
		delay(2000);			
	}
	else 
	{
		display.reset();
		display.print("SENHA INCORRETA!"); 
		beep();
		delay(2000);
		setNewPass();
	}
}

void AirsoftGame::setPass() {
	password = "";
	display.setCursorDown();
	char keyPressed = '\0';
	int cursorPosition = 0;
	while (password.length() < PASSWORD_SIZE)
	{
		keyPressed = mainKeypad.getKeyPressed();
		password += keyPressed;

		if (cursorPosition != 0) {
			display.setCursor(cursorPosition - 1, 1);
			display.print("*");
			display.print(keyPressed);
		}
		else
		{
			display.print(keyPressed);
		}
		beep();
		if(keyPressed != '\0')
			cursorPosition++;
	}
	Serial.println(password);
}

void AirsoftGame::setCode() 
{
	passwordMirror = "";
	display.setCursorDown();
	char keyPressed = '\0';	
	int cursorPosition = 0;
	while (passwordMirror.length() < PASSWORD_SIZE)
	{
		keyPressed = mainKeypad.getKeyPressed();
		passwordMirror += keyPressed;
		
		if (passwordMirror != 0) {
			display.setCursor(cursorPosition - 1, 1);
			display.print("*");
			display.print(keyPressed);
		}
		else
		{
			display.print(keyPressed);
		}
		beep();
		if (keyPressed != '\0')
			cursorPosition++;
	}
	Serial.println(passwordMirror);
}

bool AirsoftGame::comparePassword()
{
	return password.equals(passwordMirror);
}

void AirsoftGame::beep()
{
	tone(buzzerPin, 2400, 30);
}


