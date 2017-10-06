#pragma once
#include "lib/glm/mat4x4.hpp"
#include "lib/glm/vec3.hpp"

namespace Giganugs::Graphics {
	class Camera
	{
	private:
		glm::mat4 projection;
		glm::vec3 position;

	public:
		Camera(float left, float right, float bottom, float top, float near, float far);
		~Camera();

		void move(const glm::vec2& offset);
		void zoom(float distance);

		glm::mat4 viewProjection() const;
	};
}
