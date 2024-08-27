#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Config.h"
#include "GridHelper.h"
#include "Group.h"
#include "Mesh.h"
#include "Shader.h"
#include "Wall.h"

#include "FavelasConfig.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float xOffset = 0.1f;
float yOffset = 1.5f;
float zOffset = 0.5f;

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Generative Favelas | OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    Group wallGroup;
    FavelasConfig favConfig;
    favConfig.generateConfiguration();
    BlockConfig config = favConfig.getConfig();

    for (int i = 0; i < config.rows.size(); i++) {
        RowOfHouse rows = config.rows.at(i);
        float totalHousesWidth = 0.0f;
        for (int j = 0; j < rows.houses.size(); j++) {
            House house = rows.houses.at(j);

            Wall wall;
            wall.makeWall(house.width, house.height, house.depth, -0.3f);

            float xPos = totalHousesWidth;
            float yPos = i * 2.0f;
            float zPos = -i * 1.5;

            wall.setPosition(glm::vec3(xPos, yPos, zPos));
            wall.setColor(glm::vec3(house.r, house.g, house.b));
            wallGroup.Add(wall);

            totalHousesWidth += house.width + xOffset;
        }
        totalHousesWidth = 0.0f;
    }

    // Print config
    /*for (const auto &row : config.rows) {
        std::cout << "Row width: " << row.houseWidth << "\n";
        for (const auto &house : row.houses) {
            std::cout << "House width: " << house.width << ", rotation: " << house.rotation
                      << ", height: " << house.height << ", depth: " << house.depth
                      << ", depthOffset: " << house.depthOffset << "\n";
        }
        std::cout << "------\n";
    }*/

    GridHelper gridH;
    gridH.makeGridHelper(20);

    Shader shaderProgram("./../resources/shaders/shader.vert", "./../resources/shaders/shader.frag");

    shaderProgram.use();
    shaderProgram.setVec3("lightPos", lightPos);
    shaderProgram.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shaderProgram.setVec3("viewPos", camera.Position);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.use();

        glm::mat4 projection =
            glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shaderProgram.setMat4("projection", projection);

        glm::mat4 view = camera.GetViewMatrix();
        shaderProgram.setMat4("view", view);

        wallGroup.Draw(shaderProgram);
        /*
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
                shaderProgram.setMat4("model", model);
                shaderProgram.setVec3("objectColor", glm::vec3(0.0f, 0.5f, 0.31f));
                gridH.Draw();*/

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    wallGroup.Clear();
    glDeleteProgram(shaderProgram.ID);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}