//
//  main.cpp
//  Lime
//
//  Created by Abhikalp Unakal on 11/10/2020
//  Copyright © 2020 Abhikalp Unakal. All rights reserved.
//



#include "Pch.hpp"
#include "core/Lime.hpp"
#include "components/TransformComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "components/CameraComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "systems/ControllerSystem.hpp"
#include "systems/CameraSystem.hpp"
#include "systems/SpriteSystem.hpp"
#include "utils/Serde.hpp"
#include "cstdlib"
#include "core/AudioManager.hpp"

// force the usage of NVIDIA graphics
// telling optimus to switch to nvidia graphics card instead of internal 
//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

Lime gLimeEngine;
std::shared_ptr<CameraSystem> camSystem;


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
			if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				gLimeEngine.sendEvent(EventID::E_GRAPHICS_DEBUG_TOGGLE);
			}
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
	gLimeEngine.registerComponent<SpriteComponent>();
	gLimeEngine.registerComponent<CameraComponent>();

	// register system and set its signature 
	gLimeEngine.registerSystem<ControllerSystem>();
	gLimeEngine.registerSystem<SpriteSystem>();
	gLimeEngine.registerSystem<CameraSystem>();

	// Controller System
	{
		Archetype atype;
		atype.set(gLimeEngine.getComponentType<TransformComponent>());
		atype.set(gLimeEngine.getComponentType<ControllerComponent>());
		gLimeEngine.setSystemArchetype<ControllerSystem>(atype);
	}

	// Sprite System 
	{
		Archetype atype;
		atype.set(gLimeEngine.getComponentType<SpriteComponent>());
		gLimeEngine.setSystemArchetype<SpriteSystem>(atype);
	}

	// Camera Component
	{
		Archetype atype;
		atype.set(gLimeEngine.getComponentType<TransformComponent>());
		atype.set(gLimeEngine.getComponentType<ControllerComponent>());
		atype.set(gLimeEngine.getComponentType<CameraComponent>());
		gLimeEngine.setSystemArchetype<CameraSystem>(atype);
	}
	
	gLimeEngine.setMaxFPS(FPS);
	gLimeEngine.printGraphicsInfo();
	gLimeEngine.resizeGraphicsWindow(SCREEN_WIDTH,SCREEN_HEIGHT);

	// level related stuff here 

	EntityID player1 = gLimeEngine.createEntity();
	gLimeEngine.addComponent(player1, TransformComponent{ glm::vec3(100.0f,100.0f,-0.1f),glm::mat4(1.0f) });
	gLimeEngine.addComponent(player1, ControllerComponent{
		SDL_SCANCODE_W,
		SDL_SCANCODE_S,
		SDL_SCANCODE_A,
		SDL_SCANCODE_D,
		SDL_SCANCODE_T,
		SDL_SCANCODE_Q,
		SDL_SCANCODE_E,
		LMVec3{0.01f,0.01f,0.1f}});
	gLimeEngine.addComponent(player1, SpriteComponent{ "./Lime/res/gear.png",(GLuint)-1,false,0.0f,1,1 });

	EntityID camera = gLimeEngine.createEntity();
	gLimeEngine.addComponent(camera, TransformComponent{ glm::vec3{0.0f,0.0f,2.0f},glm::mat4(1.0f) });
	gLimeEngine.addComponent(camera, ControllerComponent{
	SDL_SCANCODE_T,
	SDL_SCANCODE_G,
	SDL_SCANCODE_F,
	SDL_SCANCODE_H,
	SDL_SCANCODE_T,
	SDL_SCANCODE_R,
	SDL_SCANCODE_Y,
	LMVec3{0.01f,0.01f,0.1f} });
	gLimeEngine.addComponent(camera, CameraComponent({
		glm::vec3{0.0f,0.0f,-1.0f},	// look at [-z]
		glm::vec3{0.0f,1.0f,0.0f},	// camera up [+y]
		glm::vec3{1.0f,0.0f,0.0f},	// camera right [+x]
		glm::vec3{0.0f,1.0f,0.0f},	// world up [+y]
		glm::mat4(1.0f),			// camera projection matrix
		glm::mat4(1.0f),			// camera view matrix
		float {0.1f},				// camera zoom [0,1]
		float {0.1f},				// camera sensitivity
		float {0.0f},				// xrot pitch
		float {0.0f},				// yrot yaw
		float {1.0f},				// movement speed
		int {0},					// viewport x topleft
		int {0},					// viewport y topleft
		int {SCREEN_WIDTH},			// viewport width
		int {SCREEN_HEIGHT},		// viewport height
		bool {false}				// is activated
	}));

	// providing access via global pointer to system
	camSystem = gLimeEngine.mSystemManager->getSystem<CameraSystem>();
	gLimeEngine.mSystemManager->init();

	AudioManager au;
	au.Init();
	au.LoadSound("./Lime/res/martingarrix.mp3");
	au.PlaySounds("./Lime/res/martingarrix.mp3");

	while (gLimeEngine.mIsRunning) {
		sdlPoll();
		gLimeEngine.startFrame();
		gLimeEngine.update();
		gLimeEngine.endFrame();
		fpsCounter();
	}
	au.Shutdown();
	system("pause");
	return 0;
}