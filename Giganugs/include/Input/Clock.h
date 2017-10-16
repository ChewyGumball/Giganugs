#pragma once
#include <chrono>
#include <vector>
namespace Giganugs::Input {
	class Timer;

	class Clock
	{
		std::chrono::steady_clock clock;
		std::chrono::steady_clock::time_point previousTick;
		std::chrono::steady_clock::time_point currentTick;
		std::chrono::steady_clock::duration elapsedTime;
		bool paused;

		std::vector<Timer*> timers;

	public:
		Clock();
		~Clock();

		void pause();
		void resume();

		std::chrono::duration<float> tick();

		std::chrono::duration<float> deltaTickTime() const;
		std::chrono::duration<float> totalElapsedTime() const;

		const Timer* createTimer();
		void removeTimer(Timer* timer);
	};
}

