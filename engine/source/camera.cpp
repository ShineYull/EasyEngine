#include <camera.h>

namespace Shine {
	Camera::Camera()
	{
	}

	Camera::Camera(float x, float y, float z)
	{
		this->position = glm::vec3(x, y, z);
	}

	Camera::~Camera()
	{
	}
}