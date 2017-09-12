// 
// 
// 

#include "DisplayLcd.h"

const int pinoRS = 8;
const int pinoEnable = 9;
const int pinoD4 = 4;
const int pinoD5 = 5;
const int pinoD6 = 6;
const int pinoD7 = 7;

DisplayLcd::DisplayLcd() : 
	LiquidCrystal(pinoRS, pinoEnable, pinoD4, pinoD5, pinoD6, pinoD7)
{
}


void DisplayLcd::Escrever(String dado)
{
}
