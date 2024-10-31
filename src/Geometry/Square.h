#ifndef SQUARE_H
#define SQUARE_H

#include "../Mesh.h"

class Square : public Mesh {
  public:
    void makeSquare(GLfloat width, GLfloat height);
};

#endif