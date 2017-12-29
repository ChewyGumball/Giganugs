#pragma once
#include <chrono>
#include "lib/glm/glm.hpp"

namespace Giganugs::Game {
	struct Context;
}

namespace Giganugs::Game::Entities {
	class Entity
	{
	protected:
		glm::vec2 m_position;
		glm::vec2 m_bounds;

	public:
		Entity(const glm::vec2& position, const glm::vec2& bounds);
		~Entity();

		glm::vec2 position() const;

		virtual void Update(std::chrono::duration<float> timeDelta, Context& context) = 0;
	};
}
