#ifndef SKYBOX_H
#define SKYBOX_H

#include <string>
#include <vector>

#include "Shader.h"

class Skybox {
  public:
    void loadCubemap(std::vector<std::string> faces);
    void Draw(Shader &shader);

  private:
    void setupMesh();
    GLuint VAO, VBO, textureID;
};

#endif