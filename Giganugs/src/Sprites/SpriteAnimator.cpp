#include "Sprites/SpriteAnimator.h"

#include "Input/Timer.h"
#include "Sprites/SpriteAnimation.h"

namespace Giganugs::Sprites {

	SpriteAnimator::SpriteAnimator(const SpriteAnimation* animation, const Input::Timer* timer) : animation(animation), timer(timer)
	{
	}


	SpriteAnimator::~SpriteAnimator()
	{
	}

	uint32_t Giganugs::Sprites::SpriteAnimator::currentFrameIndex() const
	{
		float elapsedTime = std::fmod(timer->elapsedSeconds().count(), animation->secondsPerFrame() * animation->frames.size());
		int32_t frameIndexIndex = static_cast<int32_t>(std::floor(elapsedTime / animation->secondsPerFrame()));

		return animation->frames[frameIndexIndex];
	}
}
