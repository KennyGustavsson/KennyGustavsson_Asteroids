#include "timer.h"

void Timer::Start()
{
	_startTime = std::chrono::system_clock::now();
}

float Timer::elapsedMilliSeconds()
{
	std::chrono::time_point<std::chrono::system_clock> endTime;
	endTime = std::chrono::system_clock::now();

	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - _startTime).count();
}

float Timer::elapsedSeconds()
{
	return elapsedMilliSeconds() / 1000.0f;
}

