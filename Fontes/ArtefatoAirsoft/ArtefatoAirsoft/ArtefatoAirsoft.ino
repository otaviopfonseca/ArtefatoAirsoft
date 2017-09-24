/*
 Name:		ArtefatoAirsoft.ino
 Created:	9/5/2017 1:39:00 PM
 Author:	DTI-Otavio
*/
#include "Domination.h"
#include "Sabotage.h"
#include "MainMenu.h"
#include "SearchAndDestroy.h"
#include "AirsoftGame.h"
#include "MembraneKeypad.h"
#include "CountDown.h"
#include "CountUpDownTimer.h"
#include "DisplayChronometer.h"
#include "DisplayLcdKeypad.h"
#include "DisplayLcd.h"
#include "MembraneKeypad.h"
#define DEBUG_SERIAL    1

const int buzzerPin = 10;
DisplayLcd lcd = DisplayLcd();
DisplayLcdKeypad keypadLcd = DisplayLcdKeypad();
DisplayChronometer chronometer = DisplayChronometer(buzzerPin);
MembraneKeypad keyboard = MembraneKeypad();
MainMenu startupMenu = MainMenu(buzzerPin, keypadLcd, lcd);

// the setup function runs once when you press reset or power the board
void setup() 
{		
	Serial.begin(9600);
	lcd.begin();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	startupMenu.getSelectedGame();
}