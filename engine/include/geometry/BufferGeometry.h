#ifndef BUFFERGEOMETRY_H
#define BUFFERGEOMETRY_H

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

namespace Shine {
	struct Vertex
	{
		glm::vec3 Position;  // 顶点位置
		glm::vec3 Normal;    // 法线
		glm::vec2 TexCoords;  // 纹理坐标

		glm::vec3 Tangent;   // 切线
		glm::vec3 Bitangent; // 副切线

	};
	
	class BufferGeometry
	{
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		unsigned int VAO;

		BufferGeometry();
		~BufferGeometry();

		void logParameters();
		void computeTangents();
		void dispose();

	private:
		glm::mat4 matrix = glm::mat4(1.0f);
	
	protected:
		unsigned int VBO, EBO;
		void setupBuffers();
	};
}

#endif // BUFFERGEOMETRY_H