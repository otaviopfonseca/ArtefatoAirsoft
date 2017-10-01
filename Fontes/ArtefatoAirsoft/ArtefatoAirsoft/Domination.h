// Domination.h

#ifndef _DOMINATION_h
#define _DOMINATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "AirsoftGame.h"

class Domination : public AirsoftGame {
public:
	Domination(int, DisplayLcd&, DisplayLcdKeypad&);

	// Inherited via AirsoftGame
	virtual void startGame() override;
};

#endif

