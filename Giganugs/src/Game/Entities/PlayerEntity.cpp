#include "Game/Entities/PlayerEntity.h"

#include "Resources/Catalogs/SpriteAnimationCatalog.h"

#include "Input/Clock.h"
#include "Input/Timer.h"

#include "Game/Context.h"

namespace Giganugs::Game::Entities {

	PlayerEntity::PlayerEntity(const std::string& type, const Resources::SpriteAnimationCatalog* animations, const Input::Timer* timer, Direction facingDirection)
		:Entity(glm::vec2(), glm::vec2()), 
		upAnimation(animations->locate(type + "_walk_up.anim"), timer),
		downAnimation(animations->locate(type + "_walk_down.anim"), timer),
		leftAnimation(animations->locate(type + "_walk_left.anim"), timer),
		rightAnimation(animations->locate(type + "_walk_right.anim"), timer),
		facingDirection(facingDirection)
	{ }


	PlayerEntity::~PlayerEntity()
	{
	}

	void PlayerEntity::Update(std::chrono::duration<float> timeDelta, Context& context)
	{
	}
	void PlayerEntity::move(Direction direction, float distance)
	{
		facingDirection = direction;
		switch (facingDirection) {
			case Up: m_position += glm::vec2(0, distance); break;
			case Right: m_position += glm::vec2(distance, 0); break;
			case Down: m_position += glm::vec2(0, -distance); break;
			case Left: m_position += glm::vec2(-distance, 0); break;
		}

	}
	const Sprites::SpriteAnimator & PlayerEntity::currentAnimator() const
	{
		switch (facingDirection) {
			case Up: return upAnimation;
			case Right: return rightAnimation;
			case Down: return downAnimation;
			case Left: return leftAnimation;
			default: return upAnimation;
		}
	}
}
