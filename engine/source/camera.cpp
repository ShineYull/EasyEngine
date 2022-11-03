#include <camera.h>

namespace Shine {
	Camera::Camera()
	{
	}

	Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 upVector)
	{
		this->lookAt = glm::lookAt(position, target, upVector);
	}

	Camera::~Camera()
	{
	}
}