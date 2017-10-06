#include "Graphics/Camera.h"

#include "lib/glm/gtx/transform.hpp"

namespace Giganugs::Graphics {
	Camera::Camera(float left, float right, float bottom, float top, float near, float far)
		:projection(glm::ortho(left, right, bottom, top, near, far))
	{
	}


	Camera::~Camera()
	{
	}

	void Camera::move(const glm::vec2 & offset)
	{
		position += glm::vec3(offset, 0);
	}

	void Camera::zoom(float distance)
	{
		//view = glm::scale(view, glm::vec3(distance, distance, distance));
	}

	glm::mat4 Camera::viewProjection() const
	{
		float x = std::floor(position.x);
		float y = std::floor(position.y);
		float z = std::floor(position.z);
		return projection * glm::translate(glm::vec3(x, y, z));
	}
}
