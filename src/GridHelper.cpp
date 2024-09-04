#include "GridHelper.h"
#include "Mesh.h"

void GridHelper::makeGridHelper(unsigned int n) {
    for (int j = 0; j <= n; j++) {
        for (int i = 0; i <= n; i++) {
            float x = (float)i / (float)n;
            float y = 0;
            float z = (float)j / (float)n;
            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {

            int row1 = j * (n + 1);
            int row2 = (j + 1) * (n + 1);

            indices.push_back(glm::uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
            indices.push_back(glm::uvec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));
        }
    }

    setupMesh();
}

void GridHelper::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec4), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindVertexArray(0);
}

void GridHelper::Draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, indices.size() * 4, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}
