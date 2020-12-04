// Windows Graphics Wrapper
#ifndef GRAPHICSWINDOWS_HPP
#define GRAPHICSWINDOWS_HPP
#include "Pch.hpp"
#include "glad/glad.h"
#include "SDL.h"
#include "SDL_opengl.h"

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
//private:
public:
	unsigned int mScreenWidth;
	unsigned int mScreenHeight;
	unsigned int mFlags;
	string mWindowTitle;

	std::shared_ptr<SDL_Window> mWindow;
	std::shared_ptr<SDL_Surface> mWindowSurface;
	SDL_GLContext mOpenGLContext;
};
#endif
