#pragma once
#include "lib/glm/mat4x4.hpp"
#include "lib/glm/vec3.hpp"

namespace Giganugs::Graphics {
	class Camera
	{
	private:
		glm::mat4 projection;
		glm::vec3 m_position;
		float m_width;
		float m_height;

	public:
		Camera(float left, float right, float bottom, float top, float near, float far);
		~Camera();

		void move(const glm::vec2& offset);
		void zoom(float distance);

		float width() const;
		float height() const;
		const glm::vec3& position() const;

		glm::mat4 viewProjection() const;
	};
}
