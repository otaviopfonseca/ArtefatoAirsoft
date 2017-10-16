// 
// 
// 

#include "AirsoftGame.h"

const unsigned int PASSWORD_SIZE = 8;
const unsigned int COUNTDOWN_BEGIN = 5;
bool AirsoftGame::armingOrDefusing = false;
bool AirsoftGame::cancelling = false;
GameKeypad AirsoftGame::gameKeypad = GameKeypad();

void AirsoftGame::startGameTimer()
{
	gameTimer.start(((long)gameMinutes) * ((long)60) * ((long)1000));
}

void AirsoftGame::startBombTimer()
{
	mainChronometer.begin();
	mainChronometer.setStartTime(bombMinutes, 0);
	mainChronometer.start();
}

void AirsoftGame::printGameTimer()
{
	long currentMilis = gameTimer.remaining();
	long hours = (currentMilis / 6000000);
	long minutes = (currentMilis / 60000) % 60;
	long seconds = (currentMilis / 1000) % 60;
	long miliseconds = currentMilis % 1000;
	if (miliseconds < 100)
		beep();
	String timeString = getTimeString(hours, minutes, seconds, miliseconds);
	if (gameTimer.remaining() > 0)
	{
		display.setCursor(3, 0);
		display.print("TEMPO DE JOGO");
		display.setCursor(3, 1);
		display.print(timeString);
	}
}

String AirsoftGame::getTimeString(int hours, int minutes, int seconds, int miliseconds)
{
	String strHours = "";
	if (hours < 10)
		strHours += "0";
	strHours += hours;

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

	return strHours + ":" + strMinutes + ":" + strSeconds + "." + strMilis;
}

void AirsoftGame::printBombTimer()
{
	long currentMilis = mainChronometer.getTimer().remaining();
	long hours = (currentMilis / 6000000);
	long minutes = (currentMilis / 60000) % 60;
	long seconds = (currentMilis / 1000) % 60;
	long miliseconds = currentMilis % 1000;
	if (miliseconds < 100)
		beep();
	String timeString = getTimeString(hours, minutes, seconds, miliseconds);
	if (mainChronometer.getTimer().remaining() > 0)
	{
		display.setCursor(3, 0);
		display.print("DETONACAO EM");
		display.setCursor(3, 1);
		display.print(timeString);
	}
	mainChronometer.printCurrentTime();
}

AirsoftGame::AirsoftGame(int _buzzerPin, DisplayLcd & _display, DisplayLcdKeypad & _displayKeyboard)
	: display(_display), keypad(_displayKeyboard)
{
	gameTimer = CountDown();
	bombTimer = CountDown();
	mainChronometer = DisplayChronometer(_buzzerPin);
	mainKeypad = MembraneKeypad();
	buzzerPin = _buzzerPin;
	armingTimer = CountDown();
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
	display.reset();
	startGameCountdown();
	gameKeypad.addEventListener(armingDesarmingEvent);
}

void AirsoftGame::armingDesarmingEvent(KeypadEvent key)
{
	KeyState state = gameKeypad.getState();
	switch (state)
	{	
		case KeyState::RELEASED:
		{
			switch (key)
			{
			case GameKeypad::RED_BUTTON_TEAM:
				armingOrDefusing = false;
				break;
			case GameKeypad::GREEN_BUTTON_TEAM:
				cancelling = false;
				break;
			}
		}
		case KeyState::HOLD:
		{
			switch (key)
			{
			case GameKeypad::RED_BUTTON_TEAM:
				armingOrDefusing = true;
				break;
			case GameKeypad::GREEN_BUTTON_TEAM:
				cancelling = true;
				break;
			}
		}
		default:
			break;
	}
}

void AirsoftGame::begin()
{
	gameKeypad.addEventListener(armingDesarmingEvent);
}

void AirsoftGame::startGameCountdown()
{	
	display.reset();
	display.setCursor(1, 0);
	display.print("PRONTO P/ INICIAR");
	display.setCursorDown();
	display.print("PRES. ALGUM BOTAO");
	mainKeypad.waitForKey();
	display.reset();
	display.setCursor(1, 0);
	display.print("INICIANDO JOGO");
	for (int i = COUNTDOWN_BEGIN; i > 0; i--) {
		display.setCursor(5, 1);
		beep();
		display.print("EM ");
		display.print(i);
		delay(1000);
	}
	display.reset();
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
}

bool AirsoftGame::comparePassword()
{
	return password.equals(passwordMirror);
}

void AirsoftGame::beep()
{
	tone(buzzerPin, 2400, 30);
}

void AirsoftGame::beepError()
{
	tone(buzzerPin, 100, 30);
}


