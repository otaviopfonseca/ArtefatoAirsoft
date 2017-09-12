// DisplayLcd.h

#ifndef _DISPLAYLCD_h
#define _DISPLAYLCD_h 1

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LiquidCrystal.h>


class DisplayLcd : public LiquidCrystal
{

private:
	int CursorAtual = 0;
public:
	DisplayLcd();
	void Escrever(String dado);
};

#endif

