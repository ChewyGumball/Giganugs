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
		
	public:
		Clock();
		~Clock();

		void pause();
		void resume();

		void tick();

		std::chrono::duration<float> deltaTickSeconds() const;
		std::chrono::steady_clock::duration totalElapsedTime() const;
		std::chrono::duration<float> totalElapsedSeconds() const;
	};
}

