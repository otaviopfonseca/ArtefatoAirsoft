// MembraneKeypadOneWire.h

#ifndef _MEMBRANEKEYPADONEWIRE_h
#define _MEMBRANEKEYPADONEWIRE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <OnewireKeypad.h>
#define MAX_KEYS 16

#define ROWS 4
#define COLUMNS 4
#define PIN A1
#define ROW_RES 4700
#define	COL_RES 1000
#define Precision ExtremePrec 

class MembraneKeypadOneWire : public OnewireKeypad<Print, MAX_KEYS>
{
public:
	MembraneKeypadOneWire();
	int getRealNumber();
	char getKeyPressed();
	char waitForKey();
};

#endif

