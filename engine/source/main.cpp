#include <iostream>
#include <window.h>
#include <tool/shader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <tool/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geometry/PlaneGeometry.h>
#include <geometry/BoxGeometry.h>
#include <geometry/SphereGeometry.h>
#include <camera.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Shine::Camera *camera);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = SCREEN_WIDTH/2, lastY = SCREEN_HEIGHT/2;
float yaw = 0, pitch = 0;
bool mouseRightDown = false;
bool firstMouse = false;

/* Create Camera */
Shine::Camera camera(glm::vec3(0.0, 0.0f, 3.0));

std::vector <int> DragList;
void DrawGUI()
{
    ImGui::Begin(u8"×÷˜IÓÃ");

    for (size_t i = 0; i < 5; i++)
    {
        ImGui::Button(std::to_string(i).c_str());
        if (i + 1 < 5)
        {
            ImGui::SameLine();
        }
        if (ImGui::BeginDragDropSource())
        {
            ImGui::Text(std::string("Drag : ").append(std::to_string(i)).c_str());
            ImGui::SetDragDropPayload("DragIndexButton", &i, sizeof(int));
            ImGui::EndDragDropSource();
        }
    }
    ImGui::End();

    ImGui::Begin("Drag Window");
    ImGui::Text("Drag Target");
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragIndexButton"))
        {
            DragList.push_back(*(const int*)payload->Data);
        }
        ImGui::EndDragDropTarget();
    }

    for (size_t i = 0; i < DragList.size(); i++)
    {
        if (ImGui::Button(std::to_string(DragList.at(i)).c_str()))
        {
            DragList.erase(DragList.begin() + i);
        }
        if (i + 1 < DragList.size())
        {
            ImGui::SameLine();
        }
    }
    ImGui::End();

    ImGui::Begin("TextEditor");
    ImGui::End();
}

int main() {
    /* imgui */
    const char* glsl_version = "#version 330";

    /***************************** Init Windows ********************************/
    Shine::Window window(3, 3);
    window.CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window.window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    window.MakeContextCurrent(window.window);
    window.SetFramebufferSizeCallback(window.window, framebuffer_size_callback);
    window.SetMouseButtonCallback(window.window, mouse_button_callback);
    window.SetCursorPosCallback(window.window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    /***************************** Init Windows ********************************/

    /* imgui */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext(NULL);
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiViewportFlags_NoDecoration;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiCol_DockingEmptyBg;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

     glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(12.0f,  5.0f, -12.0f),
        glm::vec3(9.5f, -2.2f, 1.5f),
        glm::vec3(7.8f, -2.0f, -9.3f),
        glm::vec3(12.4f, -0.4f, 0.5f),
        glm::vec3(9.7f,  3.0f, -4.5f),
        glm::vec3(11.3f, -2.0f, 1.5f),
        glm::vec3(11.5f,  2.0f, 1.5f),
        glm::vec3(11.5f,  0.2f, 2.5f),
        glm::vec3(9.3f,  1.0f, 2.5f)
    };

    Shine::PlaneGeometry planeGeometry(1.0, 1.0);
    Shine::BoxGeometry boxGeometry(1.0, 1.0, 1.0, 1.0, 1.0);
    Shine::SphereGeometry sphereGeometry(0.5, 20.0, 20.0);
    Shine::Shader ourShader("../../engine/source/GLSL/vertex.glsl", "../../engine/source/GLSL/fragment.glsl");

    /***************************** Create Texture ********************************/
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("../../engine/asset/woodenbox.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
    /***************************** Create Texture ********************************/

    ourShader.use();
    ourShader.setInt("texture1", 0);

    // Open depth test.
    glEnable(GL_DEPTH_TEST);

    float f = 45.0f;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(window.window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window.window, &camera);

        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport();
        DrawGUI();
        ImGui::ShowDemoWindow();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        ourShader.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("view", camera.GetMat4());
        ourShader.setMat4("projection", projection);

        for (int i = 0; i < 10; i++) {
            glm::mat4 model(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            float angle = 20 * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.5f, 0.8f, 0.3f));
            ourShader.setMat4("model", model);

            glBindVertexArray(boxGeometry.VAO);
            glDrawElements(GL_TRIANGLES, boxGeometry.indices.size(), GL_UNSIGNED_INT, 0);
        }
        //glDrawElements(GL_POINTS, planeGeometry.indices.size(), GL_UNSIGNED_INT, 0);
        //glDrawElements(GL_LINE_LOOP, planeGeometry.indices.size(), GL_UNSIGNED_INT, 0);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(10.0, 0.0f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-45.0f), glm::vec3(1.0, 0.0f, 0.0f));
        ourShader.setMat4("model", model);
        glBindVertexArray(planeGeometry.VAO);
        glDrawElements(GL_TRIANGLES, planeGeometry.indices.size(), GL_UNSIGNED_INT, 0);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(10.0, 0.0f, 5.0f));
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-45.0f), glm::vec3(1.0, 0.0f, 0.0f));
        ourShader.setMat4("model", model);
        glBindVertexArray(sphereGeometry.VAO);
        glDrawElements(GL_TRIANGLES, sphereGeometry.indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    boxGeometry.dispose();
    glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window, Shine::Camera *camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->cameraPos += cameraSpeed * camera->cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->cameraPos -= cameraSpeed * camera->cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->cameraPos -= glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->cameraPos += glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            mouseRightDown = true;
            firstMouse = true;
            break;
        default:
            return;
        }
    }
    else if (action == GLFW_RELEASE) {
        switch (button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            mouseRightDown = false;
            break;
        default:
            return;
        }
    }
    return;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!mouseRightDown) {
        return;
    }else if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        printf("xpos:%f\n", xpos);
        printf("ypos:%f\n", ypos);
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    printf("\n");
    printf("%f, %f, %f", glm::normalize(front).x, glm::normalize(front).y, glm::normalize(front).z);
    printf("%f, %f, %f", camera.cameraFront.x, camera.cameraFront.y, camera.cameraFront.z);
    camera.cameraFront = glm::normalize(front);
}