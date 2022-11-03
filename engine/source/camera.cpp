#include <camera.h>

namespace Shine {
	Camera::Camera()
	{
		this->cameraPos = glm::zero<glm::vec3>();
		this->cameraFront = glm::zero<glm::vec3>();
		this->cameraUp = glm::zero<glm::vec3>();
	}

	Camera::Camera(glm::vec3 position, glm::vec3 Front, glm::vec3 upVector)
	{
		this->cameraPos = position;
		this->cameraFront = Front;
		this->cameraUp = upVector;
	}

	Camera::~Camera()
	{
	}

	glm::mat4 Camera::GetMat4() {
		return glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);
	}
}