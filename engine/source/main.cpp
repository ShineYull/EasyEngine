#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);"
"}\0";

const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   vec4 myColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"   vec3 myColorOne = vec3(1.0f, 0.5f, 0.2f);\n"
"   vec2 myColorTwo = vec2(1.0f, 0.5f);\n"
"   FragColor = vec4(myColorTwo.r, myColorTwo.g, myColorOne.b, myColor.a);\n"
"   FragColor = vertexColor;"
"}\n\0";

int main() {
	
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float firstTriangle[] = {
        -0.5f, -0.5f, 0.0f,  // left 
        0.5f, -0.5f, 0.0f,  // right
        0.0f, 0.5f, 0.0f,  // top 
    };
    unsigned int VAOs, VBOs;
    glGenVertexArrays(1, &VAOs);
    glGenBuffers(1, &VBOs);

    glBindVertexArray(VAOs);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramOrange = glCreateProgram();

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderOrange);

    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAOs);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	
    glDeleteVertexArrays(1, &VAOs);
    glDeleteBuffers(1, &VBOs);
    glDeleteProgram(shaderProgramOrange);

    glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}