//
//  main.cpp
//  Lime
//
//  Created by Abhikalp Unakal on 11/10/2020
//  Copyright © 2020 Abhikalp Unakal. All rights reserved.
//

#include "Pch.hpp"
#include "core/Lime.hpp"
#include "core/AudioManager.hpp"
#include "cstdlib"
//#include "GL/GL.h"
//#include "GL/GLU.h"
#include "glad/glad.h"
//#include "SDL2-2.0.12/include/SDL_opengl.h"
//#include "utils/RenderGeometry.hpp"
//#include "utils/Shader.hpp"
//#include "SDL.h"

// force the usage of NVIDIA graphics
// telling optimus to switch to nvidia graphics card instead of internal 
//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

Lime gLimeEngine;
Grid gridmap;
AudioManager au;

#ifdef _WIN64
#include "Windows.h"
FILE _iob[] = {
	*stdin,
	*stdout,
	*stderr
};
extern "C" FILE * __cdecl __iob_func(void) {
	return _iob;
}
#pragma comment(lib, "legacy_stdio_definitions.lib")

//allocating console
void console() {
#ifdef _WIN64
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle(L"[Lime]");
	}
#endif
}

// max 80 to prevent using new and having memory leaks 
void setConsoleTitle(const char* title) {
	std::setlocale(LC_ALL, "en_US.utf8");
	std::wcout.imbue(std::locale("en_US.utf8"));
	wchar_t wstr[80];
	// +1 to account for \0 termination
	size_t wsize;
	mbstowcs_s(&wsize, wstr, strlen(title) + 1, title, strlen(title));
	SetConsoleTitle(wstr);
}
#endif


void fpsCounter() {
	char title[MAX_TITLE_LEN];
	snprintf(title, MAX_TITLE_LEN, "[Lime] FPS: %f", gLimeEngine.getFPS());
#ifdef _WIN64
	setConsoleTitle(title);
#else
	std::cout << "FPS: " << gLimeEngine.getFPS()<<std::endl;
#endif
}




///Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes matrices and clear color
bool initGL();

//Input handler
void handleKeys(unsigned char key, int x, int y);

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

		// setting the core profile doesn't allow us to use older deprecated functions 
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			// use glad loader to gain access to openGL calls - needed on windows only 
#ifdef _WIN64
			gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
#endif
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Initialize OpenGL
				if (!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}

	return success;
}

bool initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", glGetString(error));
		success = false;
	}

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", glGetString(error));
		success = false;
	}

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", glGetString(error));
		success = false;
	}

	return success;
}

void handleKeys(unsigned char key, int x, int y)
{
	//Toggle quad
	if (key == 'q')
	{
		gRenderQuad = !gRenderQuad;
	}
}

void update()
{
	//No per frame update needed
}

void render()
{
	//Clear color buffer
	//glClear(GL_COLOR_BUFFER_BIT);

	//Render quad
	if (gRenderQuad)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
		glEnd();
	}
}

void close()
{
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


int main(int argc, char** argv) {

	console();
	gLimeEngine.init();
	gLimeEngine.printGraphicsInfo();

	//// level related stuff here 
	gLimeEngine.load("Lime/level1.json");
	gLimeEngine.systemInit();
	//
	au.Init();
	au.LoadSound("Lime/res/naruto_battle.mp3");
	au.LoadSound("Lime/res/kamehameha_goku.mp3");
	au.LoadSound("Lime/res/youredead_kakashi.mp3");
	//au.PlaySounds("Lime/res/naruto_battle.mp3");



	//init();

	while (gLimeEngine.mIsRunning) {
	//while (1){
		// The code between glBegin/glEnd has no effect when you use only the core OpenGL functionality
// Draw a square using the (deprecated) fixed pipeline functionality

		sdlPoll();
			//Initialize Projection Matrix

		//SDL_GL_SwapWindow(gWindow);
		gLimeEngine.startFrame();

		gLimeEngine.update();

		////gr.drawRect(glm::vec2(0, 0), glm::vec2{ 40.0f,40.0f }, 0.0f, glm::vec4{ 1.0f,1.0f,0.0f,1.0f });
		gLimeEngine.endFrame();
		fpsCounter();
	}
	au.Shutdown();
	//gLimeEngine.save("Lime/level1.json");
	system("pause");

	return 0;
}






