#pragma once
#include "lib/glm/mat4x4.hpp"
#include "lib/glm/vec3.hpp"
#include "lib/glm/vec2.hpp"

namespace Giganugs::Graphics {
	class Camera
	{
	private:
		glm::mat4 projection;
		glm::vec3 m_position;
		float m_width;
		float m_height;
		float m_zoom;

	public:
		Camera(float left, float right, float bottom, float top, float near, float far);
		~Camera();

		void move(const glm::vec2& offset);
		void zoom(float distance);

		float width() const;
		float height() const;
		const glm::vec3& position() const;
		float zoom() const;

		glm::mat4 viewProjection() const;

		glm::vec2 unproject(const glm::vec2& screenPosition) const;
	};
}
