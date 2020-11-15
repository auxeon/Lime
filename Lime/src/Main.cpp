//
//  main.cpp
//  Lime
//
//  Created by Abhikalp Unakal on 11/10/2020
//  Copyright © 2020 Abhikalp Unakal. All rights reserved.
//



#include "Pch.hpp"
#include "core/Lime.hpp"
#include "core/Colors.hpp"
#include "components/TransformComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "systems/ControllerSystem.hpp"
#include "systems/SpriteSystem.hpp"
#include "utils/Serde.hpp"
#include "cstdlib"

// force the usage of NVIDIA graphics
// telling optimus to switch to nvidia graphics card instead of internal 
//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

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
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		if (e.type == SDL_WINDOWEVENT) {
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				Event event(EventID::E_WINDOW_RESIZED);
				event.setParam<unsigned int>(EventID::P_WINDOW_RESIZED_WIDTH, e.window.data1);
				event.setParam<unsigned int>(EventID::P_WINDOW_RESIZED_HEIGHT, e.window.data2);
				gLimeEngine.sendEvent(event);
			}
		}
		else if (e.type == SDL_QUIT){
			Event event(EventID::E_WINDOW_QUIT);
			gLimeEngine.sendEvent(event);
		}
		else if (gLimeEngine.mInputManager->isKeyPressed(SDL_SCANCODE_ESCAPE)){
			Event e1(EventID::E_WINDOW_KEY_PRESSED);
			e1.setParam<SDL_Scancode>(P_WINDOW_KEY_PRESSED_KEYCODE, SDL_SCANCODE_ESCAPE);
			gLimeEngine.sendEvent(e1);
			Event e2(EventID::E_WINDOW_QUIT);
			gLimeEngine.sendEvent(e2);
		}
		else if (gLimeEngine.mInputManager->mouseMove(e)) {
			Event event(EventID::E_WINDOW_MOUSE_MOVE);
			event.setParam<float>(EventID::P_WINDOW_MOUSE_MOVE_X, gLimeEngine.mInputManager->mX());
			event.setParam<float>(EventID::P_WINDOW_MOUSE_MOVE_Y, gLimeEngine.mInputManager->mY());
			gLimeEngine.sendEvent(event);
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			Event event(EventID::E_WINDOW_MOUSE_DOWN);
			int button;
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				button = mouseButtons::LB;
				break;
			case SDL_BUTTON_MIDDLE:
				button = mouseButtons::MB;
				break;
			case SDL_BUTTON_RIGHT:
				button = mouseButtons::RB;
				break;
			default:
				break;
			}
			event.setParam<int>(EventID::P_WINDOW_MOUSE_DOWN_BUTTON, button);
			event.setParam<float>(EventID::P_WINDOW_MOUSE_DOWN_X, gLimeEngine.mInputManager->mX());
			event.setParam<float>(EventID::P_WINDOW_MOUSE_DOWN_Y, gLimeEngine.mInputManager->mY());
			gLimeEngine.sendEvent(event);
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			Event event(EventID::E_WINDOW_MOUSE_UP);
			int button=0;
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				button = mouseButtons::LB;
				break;
			case SDL_BUTTON_MIDDLE:
				button = mouseButtons::MB;
				break;
			case SDL_BUTTON_RIGHT:
				button = mouseButtons::RB;
				break;
			default:
				break;
			}
			event.setParam<int>(EventID::P_WINDOW_MOUSE_UP_BUTTON, button);
			event.setParam<float>(EventID::P_WINDOW_MOUSE_UP_X, gLimeEngine.mInputManager->mX());
			event.setParam<float>(EventID::P_WINDOW_MOUSE_UP_Y, gLimeEngine.mInputManager->mY());
			gLimeEngine.sendEvent(event);
		}
		else if (e.type == SDL_KEYDOWN) {
			Event event(EventID::E_WINDOW_KEY_PRESSED);
			event.setParam<SDL_Scancode>(P_WINDOW_KEY_PRESSED_KEYCODE, e.key.keysym.scancode);
			gLimeEngine.sendEvent(event);
		}
		else if (e.type == SDL_KEYUP) {
			Event event(EventID::E_WINDOW_KEY_RELEASED);
			event.setParam<SDL_Scancode>(P_WINDOW_KEY_RELEASED_KEYCODE, e.key.keysym.scancode);
			gLimeEngine.sendEvent(event);
		}

	}

}

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define FPS 120
#define MAX_TITLE_LEN 80

void fpsCounter() {
	char title[MAX_TITLE_LEN];
	snprintf(title, MAX_TITLE_LEN, "[Lime] FPS: %f", gLimeEngine.getFPS());
#ifdef _WIN64
	setConsoleTitle(title);
#else
	std::cout << "FPS: " << gLimeEngine.getFPS()<<std::endl;
#endif
}

int main(int argc, char** argv) {
	console();
	sdj::exampleloadsave();
	Log::init();
	
	gLimeEngine.init();
	gLimeEngine.registerComponent<TransformComponent>();
	gLimeEngine.registerComponent<ControllerComponent>();

	// register system and set its signature 
	gLimeEngine.registerSystem<ControllerSystem>();
	gLimeEngine.registerSystem<SpriteSystem>();

	Archetype atype;
	atype.set(gLimeEngine.getComponentType<TransformComponent>());
	atype.set(gLimeEngine.getComponentType<ControllerComponent>());
	gLimeEngine.setSystemArchetype<ControllerSystem>(atype);

	gLimeEngine.mSystemManager->init();

	gLimeEngine.setMaxFPS(FPS);
	gLimeEngine.printGraphicsInfo();
	gLimeEngine.resizeGraphicsWindow(SCREEN_WIDTH,SCREEN_HEIGHT);

	EntityID player1 = gLimeEngine.createEntity();
	gLimeEngine.addComponent(player1, TransformComponent{ 100.0f,100.0f,1.0f });
	gLimeEngine.addComponent(player1, ControllerComponent{
		SDL_SCANCODE_W,
		SDL_SCANCODE_S,
		SDL_SCANCODE_A,
		SDL_SCANCODE_D,
		SDL_SCANCODE_SPACE,
		LMVec3{10.0f,10.0f,10.0f}});

	EntityID player2 = gLimeEngine.createEntity();
	gLimeEngine.addComponent(player2, TransformComponent{ 10.0f,10.0f,1.0f });

	while (gLimeEngine.mIsRunning) {
		sdlPoll();
		gLimeEngine.startFrame();
		gLimeEngine.update();
		//glClearColor(colors::emerald.x, colors::emerald.y, colors::emerald.z, colors::emerald.w);
		//const float clear_color[4] = { 0.4, 0.4, 0.4, 1 };
		const float clear_color[4] = { colors::emerald.x, colors::emerald.y, colors::emerald.z, colors::emerald.w };

		// Clip window
		glClipControl(GL_LOWER_LEFT, GL_NEGATIVE_ONE_TO_ONE);
		// Setup viewport 0
		glViewportIndexedf(0, 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		// Clear color buffer of current framebuffer(0)
		glClearNamedFramebufferfv(0, GL_COLOR, 0, clear_color);
		gLimeEngine.endFrame();
		fpsCounter();
	}
	for (auto& e : gLimeEngine.mEntityManager->mAllocdEntities) {
		gLimeEngine.mEntityManager->destroyEntity(e);
	}

	system("pause");
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