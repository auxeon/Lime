#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include "Pch.hpp"
// if windows
#ifdef _WIN64
#include "platform/windows/Input.hpp"
#endif

// if macos
#ifdef __APPLE__
#include "platform/macos/Input.hpp"
#endif

class InputManager {
public:
	bool isKeyPressed(SDL_Scancode keycode) {
		return io.isKeyPressed(keycode);
	}
	bool isKeyReleased(SDL_Scancode keycode) {
		return io.isKeyReleased(keycode);
	}
	bool isKeyTriggered(SDL_Scancode keycode) {
		return io.isKeyTriggered(keycode);
	}

	void init() {
		io.init();
	}
	void update() {
		io.update();
	}
	void onEvent(Event& e) {
		io.onEvent(e);
	}
	void mouseButtonDown(SDL_Event event = SDL_Event()) {
		io.mouseButtonDown(event);
	}
	bool mouseMove(SDL_Event event = SDL_Event()) {
		return io.mouseMove(event);
	}
	void mouseButtonUp(SDL_Event event = SDL_Event()) {
		io.mouseButtonUp(event);
	}
	bool getMouseButtonState(int buttonnumber) {
		return io.getMouseButtonState(buttonnumber);
	}
	glm::vec2* getMousePosition() {
		return io.getMousePosition();
	}
	float mX() {
		return io.mX();
	}
	float mY() {
		return io.mY();
	}

private:
	Input io;
	
};
#endif // !INPUTMANAGER_HPP

