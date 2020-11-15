#ifndef INPUT_HPP
#define INPUT_HPP
#include "Pch.hpp"

class Event;
using vecbool = std::vector<bool>;

class Input {
public:
	bool isKeyPressed(SDL_Scancode keycode);
	bool isKeyReleased(SDL_Scancode keycode);
	bool isKeyTriggered(SDL_Scancode keycode);
	void init();
	void update();
	void onEvent(Event& e);
	void mouseButtonDown(SDL_Event event = SDL_Event());
	bool mouseMove(SDL_Event event = SDL_Event());
	void mouseButtonUp(SDL_Event event = SDL_Event());
	bool getMouseButtonState(int buttonNumber);
	LMVec2* getMousePosition();
	float mX();
	float mY();
private:
	// keyboard stuff
	Uint8* mCurrentKeyboardState;
	Uint8* mPrevKeyboardState;
	int mKeyCount;

	// mouse stuff
	vecbool mMouseButtonStates;
	LMVec2* mMousePosition;

	float mMouseDX;
	float mMouseDY;

};
#endif // !INPUT_HPP