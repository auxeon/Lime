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
	Shader mShader;
    // set up vertex data (and buffer(s)) and configure vertex attributes
    float mVertices[32] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int mIndices[6] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
    };
    // vertex related
    unsigned int mVBO, mVAO, mEBO;
    // texture related
    unsigned int mTexture1, mTexture2;
    bool mDebugDraw=false;

    // active camera
    EntityID activeCam;
};
#endif // !SPRITESYSTEM_HPP