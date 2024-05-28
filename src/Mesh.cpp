#include "Mesh.h"

void Mesh::Draw(Shader &shader) {
    // TODO: Apply Shader before rendering Shader
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

glm::vec3 Mesh::computeFaceNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    glm::vec3 v1 = c - b;
    glm::vec3 v2 = a - b;
    return glm::normalize(glm::cross(v1, v2));
}

void Mesh::computeVertexNormals(std::vector<glm::vec3> vertices) {
    std::vector<glm::vec3> normals(vertices.size(), glm::vec3(0.0f, 0.0f, 0.0f));
    // Compute normal for each vertices
    for (unsigned int i = 0; i < this->indices.size(); i += 3) {
        glm::vec3 A = vertices[this->indices[i]];
        glm::vec3 B = vertices[this->indices[i + 1]];
        glm::vec3 C = vertices[this->indices[i + 2]];
        glm::vec3 normal = computeFaceNormal(A, B, C);
        normals[this->indices[i]] += normal;
        normals[this->indices[i + 1]] += normal;
        normals[this->indices[i + 2]] += normal;
    }
    // Normalize each normal
    for (unsigned int i = 0; i < normals.size(); i++)
        normals[i] = glm::normalize(normals[i]);
    // Create a Vertex struct
    for (unsigned int i = 0; i < vertices.size(); i++) {
        Vertex vert = {vertices[i], normals[i]};
        this->vertices.push_back(vert);
    }
}

void Mesh::setupMesh() {
    // Generate a Vertex Array Object, a Vertex Buffer Object then an Index/Element Buffer
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));

    glBindVertexArray(0);
}

void Mesh::Delete() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}