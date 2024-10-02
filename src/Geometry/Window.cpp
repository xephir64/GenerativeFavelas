#include "Window.h"
/*
 * Generate the geometry of the window (2D)
 */
void Window::makeWindow(GLfloat width, GLfloat height) {
    GLfloat c = 0.09;
    GLfloat windowWidth = width / 2 - c;
    GLfloat windowHeight = height / 2 - c;

    GLfloat xVect[] = {0,
                       c,
                       c + windowWidth,
                       c + windowWidth + c,
                       c + windowWidth + c + windowWidth,
                       c + windowWidth + c + windowWidth + c};
    GLfloat yVect[] = {0,
                       c,
                       windowHeight + c,
                       windowHeight + c + c,
                       windowHeight + c + c + windowHeight,
                       windowHeight + c + c + windowHeight + c};

    std::vector<GLuint> indices = {6,  0,  1,  1,  7,  6,  7,  1,  2,  2,  8,  7,  8,  2,  3,  3,  9,  8,  9,  3,  4,
                                   4,  10, 9,  10, 4,  5,  5,  11, 10, 12, 6,  7,  7,  13, 12, 14, 8,  9,  9,  15, 14,
                                   16, 10, 11, 11, 17, 16, 18, 12, 13, 13, 19, 18, 19, 13, 14, 14, 20, 19, 20, 14, 15,
                                   15, 21, 20, 21, 15, 16, 16, 22, 21, 22, 16, 17, 17, 23, 22, 24, 18, 19, 19, 25, 24,
                                   26, 20, 21, 21, 27, 26, 28, 22, 23, 23, 29, 28, 30, 24, 25, 25, 31, 30, 31, 25, 26,
                                   26, 32, 31, 32, 26, 27, 27, 33, 32, 33, 27, 28, 28, 34, 33, 34, 28, 29, 29, 35, 34};

    std::vector<glm::vec3> vertices;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            vertices.push_back(glm::vec3(xVect[i], yVect[j], 0.0f));

    this->indices = indices;
    computeVertexNormals(vertices);
    setupMesh();
}