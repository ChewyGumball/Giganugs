#include "Game/Entities/PlayerEntity.h"

#include "Resources/Catalogs/SpriteAnimationCatalog.h"

#include "Input/Clock.h"
#include "Input/Timer.h"

#include "Game/Context.h"

#include "Input/KeyboardState.h"

namespace Giganugs::Game::Entities {

	PlayerEntity::PlayerEntity(const std::string& type, const Resources::SpriteAnimationCatalog* animations, const Input::Clock* clock, Direction facingDirection)
		:Entity(glm::vec2(), glm::vec2()), 
		walkTimer(clock),
		upAnimation(animations->locate(type + "_walk_up.anim"), &walkTimer),
		downAnimation(animations->locate(type + "_walk_down.anim"), &walkTimer),
		leftAnimation(animations->locate(type + "_walk_left.anim"), &walkTimer),
		rightAnimation(animations->locate(type + "_walk_right.anim"), &walkTimer),
		facingDirection(facingDirection)
	{ }


	PlayerEntity::~PlayerEntity()
	{
	}

	void PlayerEntity::Update(std::chrono::duration<float> timeDelta, Context& context)
	{
		float speed = 128;

		if (context.gameClock->isRunning()) {
			moving = false;
			if ((*context.keyboard)[Giganugs::Input::Key::RightArrow] == Giganugs::Input::InputState::Pressed) {
				move(Giganugs::Right, speed * timeDelta.count());
			}
			if ((*context.keyboard)[Giganugs::Input::Key::LeftArrow] == Giganugs::Input::InputState::Pressed) {
				move(Giganugs::Left, speed * timeDelta.count());
			}
			if ((*context.keyboard)[Giganugs::Input::Key::UpArrow] == Giganugs::Input::InputState::Pressed) {
				move(Giganugs::Up, speed * timeDelta.count());
			}
			if ((*context.keyboard)[Giganugs::Input::Key::DownArrow] == Giganugs::Input::InputState::Pressed) {
				move(Giganugs::Down, speed * timeDelta.count());
			}

			if (!moving && walkTimer.isRunning()) {
				walkTimer.stop();
			}
			else if (moving && !walkTimer.isRunning()) {
				walkTimer.restart();
			}
		}
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

		moving = true;
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
