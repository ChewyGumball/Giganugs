#pragma once
#include "Game/Entities/Entity.h"

#include <string>

#include "Sprites/SpriteAnimator.h"

namespace Giganugs {
	namespace Resources {
		class SpriteAnimationCatalog;
	}
	namespace Input {
		class Timer;
	}
}

namespace Giganugs::Game::Entities {
	class PlayerEntity : public Entity
	{
		Sprites::SpriteAnimator upAnimation;
		Sprites::SpriteAnimator downAnimation;
		Sprites::SpriteAnimator leftAnimation;
		Sprites::SpriteAnimator rightAnimation;

	public:
		PlayerEntity(const std::string& type, const Resources::SpriteAnimationCatalog* animations, const Input::Timer* timer);
		~PlayerEntity();

		// Inherited via Entity
		virtual void Update(std::chrono::duration<float> timeDelta, Context& context) override;
	};
}
