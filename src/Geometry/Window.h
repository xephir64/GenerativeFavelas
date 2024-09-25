#ifndef WINDOW_H
#define WINDOW_H

#include "../Mesh.h"

class Window : public Mesh {
  public:
    void makeWindow(GLfloat width, GLfloat height);
};

#endif