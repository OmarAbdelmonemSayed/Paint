#pragma once

#include <glad/glad.h>
#include "Color4.h"

class Vector3 {
public:
    GLfloat x, y, z;
    GLfloat R, G, B, A;
    GLfloat PointSize;
    Vector3(GLfloat x, GLfloat y, GLfloat z, Color4 c, GLfloat PointSize) : x(x), y(y), z(z), R(c.R), G(c.G), B(c.B), A(c.A), PointSize(PointSize) {}
    Vector3() {}
};