#include "Graphics/Camera.h"

#include "lib/glm/gtx/transform.hpp"

namespace Giganugs::Graphics {
	Camera::Camera(float left, float right, float bottom, float top, float near, float far)
		:projection(glm::ortho(left, right, bottom, top, near, far)), m_width(right - left), m_height(top - bottom)
	{
	}


	Camera::~Camera()
	{
	}

	void Camera::move(const glm::vec2 & offset)
	{
		m_position += glm::vec3(offset, 0);
	}

	void Camera::zoom(float distance)
	{
		//view = glm::scale(view, glm::vec3(distance, distance, distance));
	}

	float Camera::width() const
	{
		return m_width;
	}

	float Camera::height() const
	{
		return m_height;
	}

	const glm::vec3 & Camera::position() const
	{
		return m_position;
	}

	glm::mat4 Camera::viewProjection() const
	{
		float x = std::floor(m_position.x);
		float y = std::floor(m_position.y);
		float z = std::floor(m_position.z);
		return projection * glm::translate(glm::vec3(x, y, z));
	}
}
