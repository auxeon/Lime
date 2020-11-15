#ifndef SPRITESYSTEM_HPP
#define SPRITESYSTEM_HPP

#include "glad/glad.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "core/System.hpp"
#include "Pch.hpp"
#include "core/System.hpp"

class SpriteSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
	~SpriteSystem();
private:
	GLuint vbo;         // vertex buffer
	GLuint vao;         // vertex array
	const float points[18] = {  // vertices of triangle
	// first triangle
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f,  0.5f, 0.0f,  // top left 
	// second triangle
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left
	//0.0f,  0.5f,  0.0f,
	//0.5f, -0.5f,  0.0f,
	//-0.5f, -0.5f,  0.0f
	};
};
#endif // !SPRITESYSTEM_HPP