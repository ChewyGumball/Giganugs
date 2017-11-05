#include "Game/Entities/PlayerEntity.h"

#include "Resources/Catalogs/SpriteAnimationCatalog.h"

#include "Input/Clock.h"
#include "Input/Timer.h"

#include "Game/Context.h"

namespace Giganugs::Game::Entities {

	PlayerEntity::PlayerEntity(const std::string& type, const Resources::SpriteAnimationCatalog* animations, const Input::Timer* timer)
		:Entity(glm::vec2(), glm::vec2()), 
		upAnimation(animations->locate(type + "_walk_up.anim"), timer),
		downAnimation(animations->locate(type + "_walk_down.anim"), timer),
		leftAnimation(animations->locate(type + "_walk_left.anim"), timer),
		rightAnimation(animations->locate(type + "_walk_right.anim"), timer)
	{ }


	PlayerEntity::~PlayerEntity()
	{
	}

	void PlayerEntity::Update(std::chrono::duration<float> timeDelta, Context& context)
	{
	}
}
