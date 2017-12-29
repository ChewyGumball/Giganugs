#pragma once
#include "Game/Entities/Entity.h"

#include <string>

#include "Sprites/SpriteAnimator.h"

#include "Game/Data/Direction.h"
#include "Game/Item.h"

#include "Input/Timer.h"


namespace Giganugs {
	namespace Resources {
		class SpriteAnimationCatalog;
	}
	namespace Input {
		class Clock;
	}
}

namespace Giganugs::Game::Entities {
	class PlayerEntity : public Entity
	{
		Input::Timer walkTimer;
		Sprites::SpriteAnimator upAnimation;
		Sprites::SpriteAnimator downAnimation;
		Sprites::SpriteAnimator leftAnimation;
		Sprites::SpriteAnimator rightAnimation;

		bool moving;

	public:
		Direction facingDirection;
		Item carriedItem;

		PlayerEntity(const std::string& type, const Resources::SpriteAnimationCatalog* animations, const Input::Clock* clock, Direction facingDirection);
		~PlayerEntity();

		// Inherited via Entity
		virtual void Update(std::chrono::duration<float> timeDelta, Context& context) override;

		void move(Direction direction, float distance);

		const Sprites::SpriteAnimator& currentAnimator() const;
	};
}
