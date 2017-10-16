#include "Input/Clock.h"

#include "Input/Timer.h"

#include <algorithm>

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

			auto delta = currentTick - previousTick;
			elapsedTime += delta;

			for (auto& timer : timers) {
				timer->update(delta);
			}
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
	const Timer * Clock::createTimer()
	{
		Timer* timer = new Timer();
		timers.push_back(timer);
		return timer;
	}
	void Clock::removeTimer(Timer* timer)
	{
		auto element = std::find(timers.begin(), timers.end(), timer);
		timers.erase(element);

		delete timer;
	}
}