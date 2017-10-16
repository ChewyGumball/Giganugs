#pragma once
#include <chrono>
#include <stdint.h>

namespace Giganugs::Input {
	class Timer;
}

namespace Giganugs::Sprites {
	class SpriteAnimation;

	class SpriteAnimator
	{
		const SpriteAnimation* animation;
		const Input::Timer* timer;

	public:
		SpriteAnimator(const SpriteAnimation* animation, const Input::Timer* timer);
		~SpriteAnimator();

		uint32_t currentFrameIndex() const;
	};
}
