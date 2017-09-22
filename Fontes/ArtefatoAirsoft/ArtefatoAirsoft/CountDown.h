// CountDown.h

#ifndef _COUNTDOWN_h
#define _COUNTDOWN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class CountDown
{
public:
	enum Resolution { MILLIS, MICROS, SECONDS };

	explicit CountDown(const enum Resolution res = MILLIS);
	void setResolution(const enum Resolution res = MILLIS);

	void start(uint32_t ticks);
	void start(uint8_t days, uint8_t hours, uint8_t minutes, uint8_t seconds);
	void stop();
	void cont();

	uint32_t remaining();
	bool isRunning() const { return _state == CountDown::RUNNING; };
	enum Resolution resolution() const { return _res; };

private:
	// ??
	enum State { RUNNING, STOPPED };

	uint32_t _ticks;
	uint32_t _remaining;
	enum State _state;
	enum Resolution _res;
	unsigned long _starttime;

	void calcRemaining();
	unsigned long(*_gettime)(void);
	static unsigned long seconds() { return millis() / 1000; };
};

#endif

