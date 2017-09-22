// 
// 
// 

#include "CountUpDownTimer.h"

CountUpDownTimer::CountUpDownTimer(bool type, bool precision = HIGH) : _type(type), _precision(precision)
{
	SetStopTime((type ? 0xFFFF : 0)); // 18h 12m 15s
	time = precision ? micros() : millis();
	Clock = 0;
	Reset = false, Stop = true, Paused = true;
	timeFlag = false;
	duration = precision ? 1000000 : 1000;
}
unsigned long CountUpDownTimer::_InternalClock()
{
	return _precision ? micros() : millis();
}

boolean CountUpDownTimer::Timer()
{
	timeFlag = false;
	if (!Stop && !Paused) // if not Stopped or Paused, run timer
	{
		if (Paused)
			time = _InternalClock();

		if ((_intTime = _InternalClock()) - time > duration) // check the time difference and see if 1 second has elapsed
		{
			_type == UP ? Clock++ : Clock--;

			timeFlag = true;

			if ((_type == DOWN && Clock == 0) || TimeCheck()) // check to see if the clock is 0
				Stop = true; // If so, stop the timer

			time = _intTime;

			if (_intTime < time)
				time = 0;  // check to see if micros() has rolled over, if not, then increment "time" by duration
		}
	}

	return !Stop; // return the state of the timer
}

void CountUpDownTimer::ResetTimer()
{
	if (_type)
		Clock = 0;
	else
		SetTimer(R_clock);
	Stop = false;
}

void CountUpDownTimer::StartTimer()
{
	Watch = _InternalClock();
	Stop = false;
	Paused = false;
	if (_type == UP)
		Clock = 0;
}

void CountUpDownTimer::StopTimer()
{
	Stop = true;
}

void CountUpDownTimer::StopTimerAt(unsigned long hours, unsigned long minutes, unsigned long seconds)
{
	if (TimeCheck(hours, minutes, seconds))
		Stop = true;
}

void CountUpDownTimer::PauseTimer()
{
	time = _InternalClock();
	Paused = true;
}

void CountUpDownTimer::ResumeTimer() // You can resume the timer if you ever stop it.
{
	Paused = false;
	time = _InternalClock();
}

void CountUpDownTimer::SetTimer(unsigned long hours, unsigned long minutes, unsigned long seconds)
{
	// This handles invalid time overflow ie 1(H), 0(M), 120(S) -> 1h, 2m, 0s
	unsigned int Secs = (seconds / 60), Mins = (minutes / 60);
	if (Secs) minutes += Secs;
	if (Mins) hours += Mins;

	Clock = (hours * 3600) + (minutes * 60) + (seconds % 60);
	R_clock = Clock;
	Stop = false;
}

void CountUpDownTimer::SetTimer(unsigned long seconds)
{
	// StartTimer(seconds / 3600, (seconds / 3600) / 60, seconds % 60);
	Clock = seconds;
	R_clock = Clock;
	Stop = false;
}

void CountUpDownTimer::SetStopTime(unsigned long seconds)
{
	STh = seconds / 3600;
	STm = (seconds / 60) % 60;
	STs = seconds % 60;
	STotaltime = seconds;
}

void CountUpDownTimer::SetStopTime(unsigned long hours, unsigned long minutes, unsigned long seconds)
{
	STh = hours;
	STm = minutes;
	STs = seconds;
	STotaltime = (hours * 3600) + (minutes * 60) + (seconds % 60);
}

unsigned long CountUpDownTimer::ShowHours()
{
	return Clock / 3600;
}

unsigned long CountUpDownTimer::ShowMinutes()
{
	return (Clock / 60) % 60;
}

unsigned long CountUpDownTimer::ShowSeconds()
{
	return Clock % 60;
}

unsigned long CountUpDownTimer::ShowMilliSeconds()
{
	if (_precision == HIGH)
		return ((_intTime - Watch) / 1000.0) + 1;
	else
		return (_intTime - Watch) + 1;
}

unsigned long CountUpDownTimer::ShowMicroSeconds()
{
	if (_precision == LOW)
		return ((_intTime - Watch) / 1000.0) + 1;
	else
		return (_intTime - Watch) + 1;
}

unsigned long CountUpDownTimer::ShowTotalSeconds()
{
	return Clock;
}

unsigned long CountUpDownTimer::ShowStopTime()
{
	return STotaltime;
}

boolean CountUpDownTimer::TimeHasChanged()
{
	return timeFlag;
}

boolean CountUpDownTimer::TimeCheck(unsigned int hours, unsigned int minutes, unsigned int seconds) // output true if timer equals requested time or has passed it.
{
	unsigned long TC = ((hours * 3600) + (minutes * 60) + (seconds % 60));
	if (_type)
		return (Clock >= TC);
	else
		return (Clock <= TC);
}

boolean CountUpDownTimer::TimeCheck() // output true if timer equals requested time or has passed it.
{
	if (_type)
		return Clock >= STotaltime;
	else
		return Clock <= STotaltime;
}
