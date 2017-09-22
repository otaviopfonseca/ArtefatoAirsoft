// 
// 
// 

#include "CountDown.h"

CountDown::CountDown(const enum Resolution res)
{
	setResolution(res);
	stop();
}

void CountDown::setResolution(const enum Resolution res)
{
	_res = res;
	switch (_res)
	{
	case MICROS:
		_gettime = micros;
		break;
	case SECONDS:
		_gettime = seconds;
		break;
	case MILLIS:
	default:
		_gettime = millis;
		break;
	}
	_ticks = 0;
}

void CountDown::start(uint32_t ticks)
{
	_state = CountDown::RUNNING;
	_starttime = _gettime();
	_ticks = ticks;
}

void CountDown::start(uint8_t days, uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	uint32_t ticks = 86400UL * days + 3600UL * hours + 60UL * minutes + seconds;
	if (ticks > 4294967) ticks = 4294967;  // prevent underlying millis() overflow
	setResolution(SECONDS);
	start(ticks);
}

void CountDown::stop()
{
	calcRemaining();
	_state = CountDown::STOPPED;
}

void CountDown::cont()
{
	if (_state == CountDown::STOPPED)
	{
		start(_remaining);
	}
}

uint32_t CountDown::remaining()
{
	calcRemaining();
	return _remaining;
}

void CountDown::calcRemaining()
{
	if (_state == CountDown::RUNNING)
	{
		uint32_t t = _gettime() - _starttime;
		_remaining = _ticks > t ? _ticks - t : 0;
		if (_remaining == 0)
		{
			_state = CountDown::STOPPED;
		}
	}
}
