#include "Pch.hpp"
#include "Graphics.hpp"
#include "core/Lime.hpp"

extern Lime gLimeEngine;

/*
The resources which SDL gives us, cannot be release using delete,
as the SDL provides specific functions for every resource type.
In order to be able to use shared_ptr’s automatic resource management capability,
it needs to be customized to call different code than the default delete call.
This is indeed possible: shared_ptr’s constructor takes a second, optional parameter,
which can be a lambda expression. This lambda expression will then be called
(with the payload pointer as its only parameter) by the shared pointer class instead of its default delete call.
*/

static void SDL_DelRes(SDL_Window* r) { SDL_DestroyWindow(r); }
static void SDL_DelRes(SDL_Renderer* r) { SDL_DestroyRenderer(r); }
static void SDL_DelRes(SDL_Texture* r) { SDL_DestroyTexture(r); }
static void SDL_DelRes(SDL_Surface* r) { SDL_FreeSurface(r); }

template <typename T>
std::shared_ptr<T> sdl_shared(T* t) {
	return std::shared_ptr<T>(t, [](T* t) { SDL_DelRes(t); });
}

Graphics::Graphics() {
	// set screen width and height
	mScreenWidth = 800;
	mScreenHeight = 600;
	mWindowTitle = "[Lime]";
	mOpenGLContext = NULL;
	mWindow = NULL;
	mWindowSurface = NULL;
	mFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	// registering event callbacks
	gLimeEngine.addEventListener(EventID::E_WINDOW_RESIZED, [this](Event& e) {this->onEvent(e); });
	gLimeEngine.addEventListener(EventID::E_WINDOW_QUIT, [this](Event& e) {this->onEvent(e); });
}
void Graphics::init() {
	// initialize sdl with the video subsystem initialization flags
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LM_CORE_ERROR("Graphics: SDL init error : {}", SDL_GetError());
	}

	// creating the window to render to with the necessary flags
	mWindow = sdl_shared<SDL_Window>(SDL_CreateWindow(mWindowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mScreenWidth, mScreenHeight, mFlags));
	if (NULL == mWindow) {
		LM_CORE_ERROR("Graphics: Error creating window : {}", SDL_GetError());
		assert(mWindow != NULL);
	}

	// set opengl version flags
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	// setting the core profile doesn't allow us to use older deprecated functions 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// creating the main sdl opengl context now
	mOpenGLContext = SDL_GL_CreateContext(mWindow.get());
	mWindowSurface = sdl_shared<SDL_Surface>(SDL_GetWindowSurface(mWindow.get()));

	// use glad loader to gain access to openGL calls - needed on windows only 
#ifdef _WIN64
		gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
#endif
}
void Graphics::update() {
	//glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(mWindow.get());
}
void Graphics::resize(unsigned int w, unsigned int h) {
	mScreenWidth = w;
	mScreenHeight = h;
	SDL_SetWindowSize(mWindow.get(), w, h);
	glViewport(0, 0, w, h);
}
string Graphics::getWindowTitle() {
	return mWindowTitle;
}
void Graphics::setWindowTitle(string s) {
	mWindowTitle = s;
}
void Graphics::printInfo() {
	// let's print out the OpenGL version info 
	LM_CORE_INFO("Graphics: OpenGL version: {}", glGetString(GL_VERSION));
	LM_CORE_INFO("Graphics: OpenGL renderer: {}", glGetString(GL_RENDERER));
	LM_CORE_INFO("Graphics: Width: {}", mScreenWidth);
	LM_CORE_INFO("Graphics: Height: {}", mScreenHeight);
	LM_CORE_INFO("Graphics: Title: {}", mWindowTitle);
}

void Graphics::onEvent(Event& e){
	if (e.getType() == EventID::E_WINDOW_RESIZED) {
		auto w = e.getParam<unsigned int>(EventID::P_WINDOW_RESIZED_WIDTH);
		auto h = e.getParam<unsigned int>(EventID::P_WINDOW_RESIZED_HEIGHT);
		resize(w, h);
		LM_CORE_INFO("Window resize Event: {}x{}", w, h);
	}
	else if (e.getType() == EventID::E_WINDOW_QUIT) {
		gLimeEngine.mIsRunning = false;
		LM_CORE_INFO("[EVENT ID: {}] Window quit event", e.getType());
	}

}

