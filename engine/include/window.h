#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Shine {
	class Window {
	public:
		GLFWwindow* window;

		Window();
		Window(int major, int minor);

		~Window();

		GLFWwindow* CreateWindow(
			int width, int height,
			const char* title,
			GLFWmonitor* monitor,
			GLFWwindow* share
		);

		void MakeContextCurrent(GLFWwindow* handle);
		void SetFramebufferSizeCallback(GLFWwindow* handle, GLFWframebuffersizefun cbfun);
		void SetMouseButtonCallback(GLFWwindow* handle, GLFWmousebuttonfun cbfun);
	};
}

#endif // WINDOW_H
