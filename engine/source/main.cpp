#include <iostream>
#include <window.h>
#include <tool/shader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <tool/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float* pMixValue);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    float mixValue = 0.5f;

    /***************************** Init Windows ********************************/
    Shine::Window window(3, 3);
    window.CreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window.window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    window.MakeContextCurrent(window.window);
    window.SetFramebufferSizeCallback(window.window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    /***************************** Init Windows ********************************/

    /***************************** Create Vertex ********************************/
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
    };
    unsigned int VAOs, VBOs, EBO;
    glGenVertexArrays(1, &VAOs);
    glGenBuffers(1, &VBOs);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAOs);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /* position attrib */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /* color attrib */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /* texture coord attrib */
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    /***************************** Create Vertex ********************************/

    /* Create Shader Program */
    Shine::Shader ourShader("../../engine/source/GLSL/vertex.glsl", "../../engine/source/GLSL/fragment.glsl"); // you can name your shader files however you like

    /***************************** Create Texture ********************************/
    /* create texture1 */
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("../../engine/asset/woodenbox.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    /* create texture2 */
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    data = stbi_load("../../engine/asset/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
    /***************************** Create Texture ********************************/

    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    // or set it via the texture class
    ourShader.setInt("texture2", 1);



    ////transform
    //glm::vec4 position(1.0f, 1.0f, 1.0f, 1.0f);
    //glm::mat4 translate(1.0f);
    ////displacement
    //translate = glm::translate(translate, glm::vec3(1.0f, 0.0f, 0.0f));
    //position = translate * position;
    //std::cout << position.x << "--" << position.y << "--" << position.z << std::endl;
    //
    ////scale
    //translate = glm::scale(translate, glm::vec3(2.0f, 3.0f, 4.0f));
    //position = translate * position;
    //std::cout << position.x << "--" << position.y << "--" << position.z << std::endl;

    ////rotate
    //translate = glm::rotate(translate, (float)glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //position = translate * position;
    //std::cout << position.x << "--" << position.y << "--" << position.z << std::endl;

    while (!glfwWindowShouldClose(window.window))
    {
        processInput(window.window, &mixValue);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // create transformations
        //glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        //use shader program
        ourShader.use();

        // set Uniform value
        ourShader.setFloat("factor", mixValue);
        //ourShader.setMat4("transform", transform);
        ourShader.setFloat("factor1", (float)glfwGetTime());

        // render container
        glBindVertexArray(VAOs);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }
	
    glDeleteVertexArrays(1, &VAOs);
    glDeleteBuffers(1, &VBOs);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window, float *pMixValue)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        *pMixValue += 0.001f;
        if (*pMixValue > 1.0f) *pMixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        *pMixValue -= 0.001f;
        if (*pMixValue < 0.0f) *pMixValue = 0.0f;
    }
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}