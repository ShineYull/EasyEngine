#include <window.h>

namespace Shine {
	Window::Window() {}

	Window::Window(int major, int minor) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	}

	Window::~Window() {

	}

	GLFWwindow* Window::CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
		Window::window = glfwCreateWindow(width, height, title, monitor, share);
		
		return Window::window;
	}

	void Window::MakeContextCurrent(GLFWwindow* handle) {
		glfwMakeContextCurrent(handle);
	}

	void Window::SetFramebufferSizeCallback(GLFWwindow* handle, GLFWframebuffersizefun cbfun) {
		glfwSetFramebufferSizeCallback(handle, cbfun);
	}
}
