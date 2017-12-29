#pragma once
#include "Game/Entities/Entity.h"

#include <string>

#include "Sprites/SpriteAnimator.h"

#include "Game/Data/Direction.h"
#include "Game/Item.h"


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
		Direction facingDirection;
		Item carriedItem;

		PlayerEntity(const std::string& type, const Resources::SpriteAnimationCatalog* animations, const Input::Timer* timer, Direction facingDirection);
		~PlayerEntity();

		// Inherited via Entity
		virtual void Update(std::chrono::duration<float> timeDelta, Context& context) override;

		void move(Direction direction, float distance);

		const Sprites::SpriteAnimator& currentAnimator() const;
	};
}
