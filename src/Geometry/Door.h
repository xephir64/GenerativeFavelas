#ifndef DOOR_H
#define DOOR_H

#include "../Mesh.h"

class Door : public Mesh {
  public:
    void makeDoor(GLfloat width, GLfloat height, bool doubleWindow);
};

#endif