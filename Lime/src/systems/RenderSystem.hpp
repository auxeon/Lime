#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP
#include "Pch.hpp"
#include "core/System.hpp"
#include "utils/Shader.hpp"



class RenderSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;


    float vertices[30] = {
        // positions           // colors            
         0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f,    // top right [1,1] 0
         0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 0.0f,    // bottom right [1,0] 1
        -0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 0.0f,    // bottom left [0,0] 2
        -0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f,    // top left [0,1] 3
         0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f    // top right [1,1] 0
    };

	Shader mShader;
	unsigned int mVAO;

};

#endif // !RENDERSYSTEM_HPP
