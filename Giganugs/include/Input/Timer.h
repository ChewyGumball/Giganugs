#pragma once
#include <chrono>

namespace Giganugs::Input {
	class Clock;

	class Timer
	{
		const Clock* clock;
		bool running;
		std::chrono::steady_clock::duration startTime;

	public:
		Timer(const Clock* clock);
		~Timer();

		bool isRunning() const;
		void stop();
		void restart();
		std::chrono::duration<float> elapsedSeconds() const;
	};
}
