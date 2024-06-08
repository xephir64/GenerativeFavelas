#include "Group.h"

void Group::Add(Mesh mesh) { meshGroup.push_back(mesh); }

void Group::Draw(Shader &shader) {
    for (int i = 0; i < meshGroup.size(); i++)
        meshGroup.at(i).Draw(shader);
}

void Group::Clear() {
    for (int i = 0; i < meshGroup.size(); i++)
        meshGroup.at(i).Delete();
}
