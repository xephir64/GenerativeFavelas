#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

struct Vertex {
    glm::vec3 Positions;
    glm::vec3 Normal;
};

class Mesh {
  public:
    // Draw mesh
    void Draw(Shader &shader);
    // Delete buffers/clear memory
    void Delete();
    // Set Mesh position
    void setPosition(glm::vec3 position);
    // Set Mesh color
    void setColor(glm::vec3 color);

  protected:
    // Configure mesh
    void setupMesh();
    // Compute vertex normals
    void computeVertexNormals(std::vector<glm::vec3> vertices);
    // Compute face normal
    glm::vec3 computeFaceNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    // Mesh vertices and index
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    // Mesh color
    glm::vec3 color;
    // Mesh position
    glm::vec3 position;
    // OpenGL Buffers IDs
    GLuint VAO, VBO, EBO;
};

#endif