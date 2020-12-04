#ifndef SPRITESYSTEM_HPP
#define SPRITESYSTEM_HPP

#include "Pch.hpp"
#include "core/System.hpp"
#include "utils/Shader.hpp"
// oncreate camera component 
// fire event to sprite sysstem 

class SpriteSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
private:
    float vertices[32] = {
        // positions           // colors            // texture coords
         0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f  // top left 
    };
    unsigned int indices[6] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    Shader mShader;
    bool mDebugDraw=false;

};
#endif // !SPRITESYSTEM_HPP