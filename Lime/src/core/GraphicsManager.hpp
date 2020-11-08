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
		renderer.init();
	}
	void update() {
		renderer.update();
	}
	void resize(unsigned int w, unsigned int h) {
		renderer.resize(w, h);
	}
	string getWindowTitle() {
		return renderer.getWindowTitle();
	}
	void setWindowTitle(string s) {
		renderer.setWindowTitle(s);
	}
	void printInfo() {
		renderer.printInfo();
	}
	
private:
	Graphics renderer;
};

#endif GRAPHICSMANAGER_HPP