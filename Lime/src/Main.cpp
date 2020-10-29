//
//  main.cpp
//  Lime
//
//  Created by Abhikalp Unakal on 11/10/2020
//  Copyright © 2020 Abhikalp Unakal. All rights reserved.
//

#include <Pch.hpp>
#include <glad/glad.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "core/Lime.hpp"
#include "components/TransformComponent.hpp"
#include "systems/Serde.hpp"

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
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle(L"Lime");
	}
}
#endif

Lime gLimeEngine;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

int main(int argc, char** argv) {



#ifdef _WIN64
	console();
#endif


	// ECS DEMO
	std::cout << "ECS DEMO\n-------------\n";
	gLimeEngine.init();
	std::cout << "game engine init done\n";

	gLimeEngine.registerComponent<TransformComponent>();
	std::cout << "TransformCompomnent registered\n";


	// SERDE DEMO
	// PLAIN COMPONENT
	std::cout << "\nSERDE COMPONENT\n-------------\n";
	sdj::exampleloadsave();

	// LEVEL
	std::cout << "\nSERDE LEVEL\n-------------\n";
	EntityID player1 = gLimeEngine.createEntity();
	gLimeEngine.addComponent(player1, TransformComponent{ 1.0f,1.0f,1.0f });
	EntityID player2 = gLimeEngine.createEntity();
	gLimeEngine.addComponent(player2, TransformComponent{ 1.0f,1.0f,1.0f });
	sdj::levelloadsave();
	system("pause");


	return 0;
}