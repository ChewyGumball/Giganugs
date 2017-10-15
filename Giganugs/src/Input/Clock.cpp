#include "Input/Clock.h"


namespace Giganugs::Input {
	Clock::Clock() : previousTick(clock.now()), currentTick(clock.now()), elapsedTime(0), paused(false)
	{
	}


	Clock::~Clock()
	{
	}
	void Clock::pause()
	{
		paused = true;
		previousTick = currentTick;
	}
	void Clock::resume()
	{
		paused = false;
	}
	std::chrono::duration<float> Clock::tick()
	{
		if (!paused) {
			previousTick = currentTick;
			currentTick = clock.now();
			elapsedTime += currentTick - previousTick;
		}

		return deltaTickTime();
	}
	std::chrono::duration<float> Clock::deltaTickTime() const
	{
		return currentTick - previousTick;
	}
	std::chrono::duration<float> Clock::totalElapsedTime() const
	{
		return elapsedTime;
	}
}