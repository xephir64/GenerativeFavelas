#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glad/glad.h>

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
      protected:
        // COnfigure mesh
        void setupMesh();
        // Compute vertex normals
        void computeVertexNormals(std::vector<glm::vec3> vertices);
        // Compute face normal
        glm::vec3 computeFaceNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c);
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        GLuint VAO, VBO, EBO;
};

#endif