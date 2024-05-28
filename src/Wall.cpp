#include "Wall.h"
/*
 * Generate the geometry of the house wall
 */
void Wall::makeWall(GLfloat width, GLfloat height, GLfloat depth, GLfloat theta) {
    GLfloat xPos[] = {0, width};
    GLfloat yPos[] = {0, height};
    GLfloat zPos[] = {0, depth};

    //      6________ 7
    //      /|      /|
    //    4/_|_____/5|
    //     | |_____|_|
    //     |2/     | /3
    //     |/______|/
    //    0         1

    std::vector<GLuint> indices({
        0, 1, 4, 1, 5, 4, // Front
        2, 0, 6, 0, 4, 6, // Left
        1, 7, 5, 1, 3, 7, // Right
        0, 1, 2, 1, 3, 2, // Down
        4, 5, 6, 5, 7, 6, // Up
        2, 3, 6, 3, 7, 6  // Back
    });

    std::vector<glm::vec3> vertices;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                if (i == 1 && j == 1)
                    vertices.push_back(glm::vec3(xPos[k], yPos[j] + theta, zPos[i]));
                else
                    vertices.push_back(glm::vec3(xPos[k], yPos[j], zPos[i]));
            }
        }
    }

    this->indices = indices;
    computeVertexNormals(vertices);
    setupMesh();
}