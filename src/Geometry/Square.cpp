#include "Square.h"

void Square::makeSquare(GLfloat width, GLfloat height) {
    GLfloat xVect[2] = {0.0f, width};
    GLfloat yVect[2] = {0.0f, height};

    std::vector<GLuint> indices({
        2,
        0,
        1,
        1,
        3,
        2,
    });

    std::vector<glm::vec3> vertices;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            vertices.push_back(glm::vec3(xVect[j], yVect[i], 0.0f));
        }
    }

    this->indices = indices;
    computeVertexNormals(vertices);
    setupMesh();
}