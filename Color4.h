#pragma once
#include <glad/glad.h>

class Color4 {
public:
    GLfloat R, G, B, A;
    Color4(GLfloat R, GLfloat G, GLfloat B, GLfloat A) : R(R), G(G), B(B), A(A) {}
    Color4() {}
};