#pragma once
#include <chrono>

class Timer
{
public:
	void Start();

	float elapsedMilliSeconds();
	float elapsedSeconds();

private:
	std::chrono::time_point<std::chrono::system_clock> _startTime;
};