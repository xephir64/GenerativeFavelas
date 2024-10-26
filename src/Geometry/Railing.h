#ifndef RAILING_H
#define RAILING_H
#include "../Mesh.h"

class Railing : public Mesh {
  public:
    void makeRailing(GLfloat width, GLfloat height, GLfloat depth, GLfloat angle, GLboolean cross);
};

#endif