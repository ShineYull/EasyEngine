#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Shine {
	class Camera {
	public:
		glm::mat4 lookAt;

		Camera();
		Camera(glm::vec3 position, glm::vec3 target, glm::vec3 upVector);
		~Camera();
	private:

	};
}

#endif