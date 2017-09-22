// CountUpDownTimer.h

#ifndef _COUNTUPDOWNTIMER_h
#define _COUNTUPDOWNTIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#define UP 1
#define DOWN 0

class CountUpDownTimer
{
public:
	CountUpDownTimer(bool, bool precision = HIGH);
	unsigned long _InternalClock();
	boolean Timer();
	void ResetTimer();
	void StartTimer();
	void StopTimer();
	void StopTimerAt(unsigned long, unsigned long, unsigned long);
	void PauseTimer();
	void ResumeTimer(); 
	void SetTimer(unsigned long, unsigned long, unsigned long);
	void SetTimer(unsigned long);
	void SetStopTime(unsigned long);
	void SetStopTime(unsigned long, unsigned long, unsigned long);
	unsigned long ShowHours();
	unsigned long ShowMinutes();
	unsigned long ShowSeconds();
	unsigned long ShowMilliSeconds();
	unsigned long ShowMicroSeconds();
	unsigned long ShowTotalSeconds();
	unsigned long ShowStopTime();
	boolean TimeHasChanged();
	boolean TimeCheck(unsigned int, unsigned int, unsigned int);
	boolean TimeCheck();

private:
	unsigned long duration;
	unsigned long STh, STm, STs, STotaltime;
	unsigned long Watch, _intTime, time;
	unsigned long Clock, R_clock;
	boolean Reset, Stop, Paused;
	volatile boolean timeFlag;
	bool _type, _precision;
};

#endif

