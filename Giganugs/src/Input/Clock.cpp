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
	void Clock::tick()
	{
		if (!paused) {
			previousTick = currentTick;
			currentTick = clock.now();
			elapsedTime += currentTick - previousTick;
		}
	}

	std::chrono::duration<float> Clock::deltaTickSeconds() const
	{
		return currentTick - previousTick;
	}

	std::chrono::steady_clock::duration Clock::totalElapsedTime() const
	{
		return elapsedTime;
	}

	std::chrono::duration<float> Clock::totalElapsedSeconds() const
	{
		return elapsedTime;
	}
}