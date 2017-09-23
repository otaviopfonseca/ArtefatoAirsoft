/*
 Name:		ArtefatoAirsoft.ino
 Created:	9/5/2017 1:39:00 PM
 Author:	DTI-Otavio
*/
#include "CountDown.h"
#include "CountUpDownTimer.h"
#include "DisplayChronometer.h"
#include "DisplayLcdKeypad.h"
#include "DisplayLcd.h"
#define DEBUG_SERIAL    1

const int buzzerPin = 10;
DisplayLcd lcd = DisplayLcd();
DisplayLcdKeypad keypadLcd = DisplayLcdKeypad();
DisplayChronometer chronometer = DisplayChronometer(buzzerPin);


// the setup function runs once when you press reset or power the board
void setup() 
{	
	//lcd.begin();
	chronometer.begin();
//	lcd.print("LCD Shield ");
//	delay(400);	
//
//#ifdef DEBUG_SERIAL
	Serial.begin(9600);
//	Serial.println("Arduino - Button LCD shield");
//
//#endif
//	delay(1000);
//	lcd.setCursorUp();
//	lcd.print("Press any KEY  ");
//	
//
//#ifdef DEBUG_SERIAL
//	Serial.println("Press any KEY  ");
//#endif
}

// the loop function runs over and over again until power down or reset
void loop() {
	//lcd.setCursorDown();
	//lcd.print("                ");
	//lcd.setCursorDown();
	//lcd.setCursorDown();
	//String keyPressDescription = keypadLcd.getKeyPressedDescription();
	//lcd.print(keyPressDescription);
	//delay(500);
	chronometer.start(1, 30);
	chronometer.writeTest();	
	//delay(1000);
}