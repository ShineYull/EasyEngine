#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <tool/shader.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

    Shine::Shader ourShader("../../engine/source/GLSL/vertex.glsl", "../../engine/source/GLSL/fragment.glsl"); // you can name your shader files however you like

    float firstTriangle[] = {
        // 位置              // 颜色
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };
    unsigned int VAOs, VBOs;
    glGenVertexArrays(1, &VAOs);
    glGenBuffers(1, &VBOs);

    glBindVertexArray(VAOs);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

    /* position attrib */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /* color attrib */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /* uniform location */
    int uniformlocationOfferset = glGetUniformLocation(ourShader.ID, "offerset");

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        glUniform4f(uniformlocationOfferset, 0.5f, 0.0f, 0.0f, 0.0f);
        glBindVertexArray(VAOs);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	
    glDeleteVertexArrays(1, &VAOs);
    glDeleteBuffers(1, &VBOs);

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