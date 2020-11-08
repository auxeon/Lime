//
//  main.cpp
//  Lime
//
//  Created by Abhikalp Unakal on 11/10/2020
//  Copyright © 2020 Abhikalp Unakal. All rights reserved.
//

// force the usage of NVIDIA graphics


#include "Pch.hpp"
#include "core/Lime.hpp"
#include "core/Colors.hpp"
#include "cstdlib"

// telling optimus to switch to nvidia graphics card instead of internal 
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

// global game engine orchestrator 
Lime gLimeEngine;

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


void sdlPoll() {
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_KEYDOWN)
		{
			switch (Event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				gLimeEngine.mIsRunning = false;
				break;
			default:
				break;
			}
		}
		else if (Event.type == SDL_QUIT)
		{
			gLimeEngine.mIsRunning = false;
		}
	}

}

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

void fpsCounter() {
	char title[80];
	snprintf(title, 80, "[Lime] FPS : %f", gLimeEngine.getFPS());
#ifdef _WIN64
	setConsoleTitle(title);
#else
	std::cout << "FPS : " << gLimeEngine.getFPS()<<std::endl;
#endif
}

int main(int argc, char** argv) {
	console();
	Log::init();
	gLimeEngine.init();
	gLimeEngine.resizeGraphicsWindow(800,600);
	gLimeEngine.printGraphicsInfo();

	while (gLimeEngine.mIsRunning) {
		sdlPoll();
		gLimeEngine.startFrame();
		glClearColor(colors::emerald.x, colors::emerald.y, colors::emerald.z, colors::emerald.w);
		gLimeEngine.updateGraphics();
		gLimeEngine.endFrame();
		fpsCounter();
	}
	return 0;
}

// dump
// ECS DEMO
//std::cout << "ECS DEMO\n-------------\n";
//gLimeEngine.init();
//std::cout << "game engine init done\n";

//gLimeEngine.registerComponent<TransformComponent>();
//std::cout << "TransformCompomnent registered\n";


//// SERDE DEMO
//// PLAIN COMPONENT
//std::cout << "\nSERDE COMPONENT\n-------------\n";
//sdj::exampleloadsave();

//// LEVEL
//std::cout << "\nSERDE LEVEL\n-------------\n";
//EntityID player1 = gLimeEngine.createEntity();
//gLimeEngine.addComponent(player1, TransformComponent{ 1.0f,1.0f,1.0f });
//EntityID player2 = gLimeEngine.createEntity();
//gLimeEngine.addComponent(player2, TransformComponent{ 1.0f,1.0f,1.0f });
//sdj::levelloadsave();

//gLimeEngine.destroyEntity(player1);
//gLimeEngine.destroyEntity(player2);
//std::cout << "\nEntities destroyed\n";