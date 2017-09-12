/*
 Name:		ArtefatoAirsoft.ino
 Created:	9/5/2017 1:39:00 PM
 Author:	DTI-Otavio
*/
#include "DisplayLcd.h"
#define DEBUG_SERIAL    1
#include<LiquidCrystal.h>

const int pinoRS = 8;
const int pinoEnable = 9;
const int pinoD4 = 4;
const int pinoD5 = 5;
const int pinoD6 = 6;
const int pinoD7 = 7;

LiquidCrystal lcd(pinoRS, pinoEnable, pinoD4, pinoD5, pinoD6, pinoD7);  // MODEL_02

const int numRows = 2;
const int numCols = 16;

#define LINE_UP         0
#define LINE_DOWN       1
#define LINE_BEGIN      0

const int Analog_Button_Pin = A0;

#define NUM_KEYS 6

char messages[][17] =
{
	"                ",
	" RIGHT  Key OK  ",
	" UP     Key OK  ",
	" DOWN   Key OK  ",
	" LEFT   Key OK  ",
	" SELECT Key OK  "
};

int adc_key_values[] =
{
	0,    // button RIGHT     0.00V
	134,    // button UP        0.65V
	309,    // button DOWN      1.50V
	481,    // button LEFT      2.35V
	722,    // button SELECT    3.52V
	1023     // button NOT_PRESS 5.00V
};


// the setup function runs once when you press reset or power the board
void setup() 
{
	lcd.begin(numCols, numRows);
	lcd.print("LCD Shield ");
	delay(400);

#ifdef DEBUG_SERIAL
	Serial.begin(9600);
	Serial.println("Arduino - Button LCD shield");

#endif
	delay(1000);
	lcd.setCursor(LINE_BEGIN, LINE_UP);
	lcd.print("Press any KEY  ");

#ifdef DEBUG_SERIAL
	Serial.println("Press any KEY  ");
#endif
}

// the loop function runs over and over again until power down or reset
void loop() {
	int iPinValue;
	int iKey;

	iPinValue = analogRead(Analog_Button_Pin);

	iKey = get_key(iPinValue);

	lcd.setCursor(LINE_BEGIN, LINE_DOWN);
	//lcd.clear();
	lcd.print("                ");
	lcd.setCursor(LINE_BEGIN, LINE_DOWN);
	//lcd.print( iPinValue );
	lcd.print(messages[iKey]);

#ifdef DEBUG_SERIAL

	Serial.print(" : ");
	Serial.print(iPinValue);
	Serial.print(" : ");
	Serial.print(iKey);
	Serial.print(" : ");
	Serial.print(messages[iKey]);
	Serial.println(" ");

#endif
	delay(500);
}

int get_key(int input) {

	int k;

	for (k = 1; k<NUM_KEYS; k++) {
		if (input < adc_key_values[k]) {
			return k;
		}
	}

	if (k >= NUM_KEYS) {
		k = 0;
	}

	return k;

}
