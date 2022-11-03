#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Shine {
	class Camera {
	public:
		glm::vec3 position;

		Camera();
		Camera(float x, float y, float z);
		~Camera();
	private:

	};
}

#endif