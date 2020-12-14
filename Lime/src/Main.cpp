/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Main.cpp
Purpose: Main
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

#include "Pch.hpp"
#include "core/Lime.hpp"
#include "core/AudioManager.hpp"
#include "cstdlib"

// force the usage of NVIDIA graphics
// telling optimus to switch to nvidia graphics card instead of internal 
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

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


int main(int argc, char** argv) {

	console();
	Log::init();
	gLimeEngine.init();
	gLimeEngine.printGraphicsInfo();

	//// level related stuff here 
	gLimeEngine.load("Lime/menu.json");
	gLimeEngine.mCurrentState = "Lime/menu.json";
	gLimeEngine.systemInit();
	au.Init();
	au.LoadSound("Lime/res/naruto_battle.mp3");
	au.LoadSound("Lime/res/kamehameha_goku.mp3");
	au.LoadSound("Lime/res/youredead_kakashi.mp3");
	au.LoadSound("Lime/res/naruto_battle.mp3");

	while (gLimeEngine.mIsRunning) {
		sdlPoll();
		gLimeEngine.startFrame();
		gLimeEngine.update();
		gLimeEngine.endFrame();
		fpsCounter();
	}
	au.Shutdown();
	//gLimeEngine.save("Lime/level1.json");
	system("pause");

	return 0;
}
