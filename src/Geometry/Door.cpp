#include "Door.h"
#include "glm/fwd.hpp"
#include <vector>
/*
 * Generate the geometry of the door (2D)
 */
void Door::makeDoor(GLfloat width, GLfloat height, bool doubleWindow) {
    float c = 0.08;
    float rectWidth = width / 4;
    float rectHeight = height / 2;

    float xPoints[4] = {0.0f, c, c + rectWidth, rectWidth + c + c};
    float yPoints[6] = {
        0, c, rectHeight + c, rectHeight + c + c, rectHeight + c + c + rectHeight, rectHeight + c + c + rectHeight + c};

    std::vector<GLuint> indices = {
        1,  5,  4,  4,  0,  1,  2,  6,  5,  5,  1,  2,  3,  7,  6,  6,  2,  3,  5,  9,  8,  8,  4,  5,  7,  11,
        10, 10, 6,  7,  9,  13, 12, 12, 8,  9,  11, 15, 14, 14, 10, 11, 13, 17, 16, 16, 12, 13, 15, 19, 18, 18,
        14, 15, 17, 21, 20, 20, 16, 17, 19, 23, 22, 22, 18, 19, 18, 22, 21, 21, 17, 18, 10, 14, 13, 13, 9,  10,
    };

    if (!doubleWindow) { // Add a check to connect points to make a full window door
        GLuint fullWindow[6] = {6, 10, 9, 9, 5, 6};
        indices.insert(indices.end(), fullWindow, fullWindow + 6);
    }

    std::vector<glm::vec3> vertices;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 4; j++)
            vertices.push_back(glm::vec3(xPoints[j], yPoints[i], 0.0f));

    this->indices = indices;
    computeVertexNormals(vertices);
    setupMesh();
}