#ifndef WALL_H
#define WALL_H

#include "../Mesh.h"

class Wall : public Mesh {
  public:
    void makeWall(GLfloat width, GLfloat height, GLfloat depth, GLfloat theta);
};

#endif