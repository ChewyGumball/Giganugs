#include "Game/Entities/Entity.h"

#include "Graphics/Camera.h"


namespace Giganugs::Game::Entities {

	Entity::Entity(const glm::vec2& position, const glm::vec2& bounds)
		:m_position(position), m_bounds(bounds)
	{
	}


	Entity::~Entity()
	{
	}
	glm::vec2 Entity::position() const
	{
		return m_position;
	}
	glm::vec2 Entity::bounds() const
	{
		return m_bounds;
	}
	bool Entity::isInView(const Graphics::Camera & camera)
	{
		glm::vec2 cameraPosition = camera.position();
		return cameraPosition.x <= m_position.x && cameraPosition.x + camera.width() >= m_position.x &&
			cameraPosition.y <= m_position.y && cameraPosition.y + camera.height() >= m_position.y;
	}
}
