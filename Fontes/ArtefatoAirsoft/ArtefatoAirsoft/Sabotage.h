// Sabotage.h

#ifndef _SABOTAGE_h
#define _SABOTAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "AirsoftGame.h"

class Sabotage : public AirsoftGame
{
public:
	Sabotage(int, DisplayLcd&, DisplayLcdKeypad&);

	// Inherited via AirsoftGame
	virtual void startGame() override;
};

#endif

