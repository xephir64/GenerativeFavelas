#ifndef GROUP_H
#define GROUP_H
#include "Mesh.h"

class Group {
  public:
    // Add a mesh
    void Add(Mesh mesh);
    // Draws all meshes
    void Draw(Shader &shader);
    // Clear all meshes and cleanup memory
    void Clear();
  private:
    std::vector<Mesh> meshGroup;
};

#endif