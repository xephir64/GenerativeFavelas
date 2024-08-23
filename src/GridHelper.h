#ifndef GRID_HELPER_H
#define GRID_HELPER_H

#include "Mesh.h"

class GridHelper {
  public:
    void makeGridHelper(unsigned int n);
    void Draw();

  private:
    void setupMesh();
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec4> indices;
    GLuint VAO, VBO, EBO;
};

#endif