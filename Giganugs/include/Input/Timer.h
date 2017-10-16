#pragma once
#include <chrono>

namespace Giganugs::Input {
	class Clock;

	class Timer
	{
		std::chrono::steady_clock::duration startTime;
		const Clock* clock;

	public:
		Timer(const Clock* clock);
		~Timer();

		void restart();
		std::chrono::duration<float> elapsedSeconds() const;
	};
}
