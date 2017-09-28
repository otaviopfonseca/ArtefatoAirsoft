// SearchAndDestroy.h

#ifndef _SEARCHANDDESTROY_h
#define _SEARCHANDDESTROY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "AirsoftGame.h"

class SearchAndDestroy : public AirsoftGame 
{

public:
	SearchAndDestroy(int, DisplayLcd&, DisplayLcdKeypad&);
};

#endif

