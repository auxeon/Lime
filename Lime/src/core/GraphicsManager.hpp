/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: GraphicsManager
Purpose: platform agnostic graphics manager api exposer
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

#ifndef GRAPHICSMANAGER_HPP
#define GRAPHICSMANAGER_HPP
#include "Pch.hpp"
// if windows
#ifdef _WIN64
#include "platform/windows/Graphics.hpp"
#endif

// if macos
#ifdef __APPLE__
#include "platform/macos/Graphics.hpp"
#endif
class GraphicsManager {
public:
	void init() {
		gfx.init();
	}
	void update() {
		gfx.update();
	}
	void onEvent(Event& e) {
		gfx.onEvent(e);
	}
	void resize(unsigned int w, unsigned int h) {
		gfx.resize(w, h);
	}
	string getWindowTitle() {
		return gfx.getWindowTitle();
	}
	void setWindowTitle(string s) {
		gfx.setWindowTitle(s);
	}
	void printInfo() {
		gfx.printInfo();
	}
	
//private:
public:
	Graphics gfx;
};

#endif GRAPHICSMANAGER_HPP