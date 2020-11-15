#include "Pch.hpp"
#include "SpriteSystem.hpp"
#include "core/Lime.hpp"
//#include "core/Colors.hpp"

extern Lime gLimeEngine;

void SpriteSystem::init(){

    // TODO setup shaders 

    // Create VBO
    glCreateBuffers(1, &vbo);
    // Allocate memory for data and send it
    glNamedBufferData(vbo, sizeof(points), points, GL_STATIC_DRAW);

    // Create VAO
    glCreateVertexArrays(1, &vao);

    // Enable vertex attribute (location = 0)
    glEnableVertexArrayAttrib(vao, 0);

    // Setup vertex array attributes
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    // Setup vertex buffer for this VAO
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(float) * 3);

    glBindVertexArray(vao);
}

void SpriteSystem::update(){

    //TODO 
    // for all entities draw array and send transform 

    // Draw triangle
    glDrawArrays(GL_LINE_LOOP, 0, 6);
}

void SpriteSystem::onEvent(Event& e){

}

SpriteSystem::~SpriteSystem(){

}
