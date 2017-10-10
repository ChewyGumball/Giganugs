#include "Game/Entities/Entity.h"


namespace Giganugs::Game::Entities {

	Entity::Entity(const glm::vec2& position, const glm::vec2& bounds)
		:m_position(position), m_bounds(bounds)
	{
	}


	Entity::~Entity()
	{
	}
}
