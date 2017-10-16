#include "Input/Timer.h"

#include "Input/Clock.h"

namespace Giganugs::Input {

	Timer::Timer(const Clock* clock) : clock(clock)
	{
		restart();
	}


	Timer::~Timer()
	{
	}

	void Timer::restart()
	{
		startTime = clock->totalElapsedTime();
	}

	std::chrono::duration<float> Timer::elapsedSeconds() const
	{
		return clock->totalElapsedTime() - startTime;
	}
}
