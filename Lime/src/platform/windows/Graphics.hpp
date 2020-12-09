// Windows Graphics Wrapper
#ifndef GRAPHICSWINDOWS_HPP
#define GRAPHICSWINDOWS_HPP
#include "Pch.hpp"
#include "glad/glad.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "utils/Shader.hpp"

class Event;

class Graphics {
public:
	Graphics();
	void init();
	void update();
	void resize(unsigned int w, unsigned int h);
	string getWindowTitle();
	void setWindowTitle(string s);
	void printInfo();
	void onEvent(Event& );

	// texturing
	void initTextureData(GLuint& texid, string filepath);
	void bindTextureData(GLuint texid);

	// drawing the vertices
	void initRenderData(Shader& shader, float* vertexbuffer,unsigned int buffersize, unsigned int& vao, bool wireframe=false);
	void drawRenderData(unsigned int vao,  glm::mat4 model, glm::vec3 size, unsigned int numvertices=6, bool wireframe=true, GLuint texid=0, int style=GL_TRIANGLES);


//private:
public:
	unsigned int mScreenWidth;
	unsigned int mScreenHeight;
	unsigned int mFlags;
	string mWindowTitle;

	std::shared_ptr<SDL_Window> mWindow;
	std::shared_ptr<SDL_Surface> mWindowSurface;
	SDL_GLContext mOpenGLContext;

	Shader mShader;
	
};
#endif
