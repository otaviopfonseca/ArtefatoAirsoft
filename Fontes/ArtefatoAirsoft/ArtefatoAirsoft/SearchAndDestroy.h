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
private:
	void search();
	void destroy();

public:
	SearchAndDestroy(int, DisplayLcd&, DisplayLcdKeypad&);
	// Inherited via AirsoftGame
	virtual void startGame() override;
};

#endif

