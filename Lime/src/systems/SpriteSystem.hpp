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

    float vertices[48] = {
        // positions           // colors            // texture coords
         0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, // top right [1,1] 0
         0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 0.0f, // bottom right [1,0] 1
        -0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, // bottom left [0,0] 2
       
        -0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, // bottom left [0,0] 2
        -0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f,  // top left [0,1] 3
         0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, // top right [1,1] 0
    };

    unsigned int mVAO;
    Shader mShader;
    bool mDebugDraw=false;

};
#endif // !SPRITESYSTEM_HPP