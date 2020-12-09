#ifndef VEXTEX_ARRAY_HPP
#define VEXTEX_ARRAY_HPP

#include "Pch.hpp"
#include <glad/glad.h>
#include <array>

// Represent a Vertex Array Object
class VertexArray
{
public:
    VertexArray(
        const std::array<GLfloat, 18>& vertexBuffer,
        const std::array<GLfloat, 12>& texBuffer
    );
    virtual ~VertexArray();

    void setActive();

private:
    GLuint id;
    GLuint vertexBufferId;
    GLuint texBufferId;
};

#endif