#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Shine {
	class Camera {
	public:
		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;

		Camera();
		Camera(glm::vec3 position, glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 upVector = glm::vec3(0.0, 1.0, 0.0));
		~Camera();

		glm::mat4 GetMat4();
	private:

	};
}

#endif