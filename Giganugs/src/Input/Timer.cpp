#include "Input/Timer.h"

#include "Input/Clock.h"

namespace Giganugs::Input {

	Timer::Timer(const Clock* clock) : clock(clock), running(true), startTime(clock->totalElapsedTime())
	{
	}


	Timer::~Timer()
	{
	}

	bool Timer::isRunning() const
	{
		return running;
	}

	void Timer::stop() {
		running = false;
	}

	void Timer::restart()
	{
		startTime = clock->totalElapsedTime();
		running = true;
	}

	std::chrono::duration<float> Timer::elapsedSeconds() const
	{
		if (running) {
			return clock->totalElapsedTime() - startTime;
		}
		else {
			return std::chrono::duration<float>::zero();
		}
	}
}
