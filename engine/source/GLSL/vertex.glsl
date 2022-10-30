#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform float factor1;

mat4 rotate3d(float _angle) {
	return mat4(
		cos(_angle), -sin(_angle), 0.0f, 0.0f,
		sin(_angle), cos(_angle), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void main()
{
	gl_Position = vec4(rotate3d(factor1) * vec4(aPos, 1.0));
	ourColor = aColor;
	TexCoord = aTexCoord;
}