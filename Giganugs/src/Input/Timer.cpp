#include "Input/Timer.h"

namespace Giganugs::Input {

	Timer::Timer() : elapsedTime(0)
	{
	}


	Timer::~Timer()
	{
	}

	void Timer::update(const std::chrono::steady_clock::duration & delta)
	{
		elapsedTime += delta;
	}

	std::chrono::duration<float> Timer::elapsedSeconds() const
	{
		return elapsedTime;
	}
}
