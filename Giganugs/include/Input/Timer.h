#pragma once
#include <chrono>

namespace Giganugs::Input {
	class Timer
	{
		std::chrono::steady_clock::duration elapsedTime;
	public:
		Timer();
		~Timer();

		void update(const std::chrono::steady_clock::duration& delta);

		std::chrono::duration<float> elapsedSeconds() const;
	};
}
