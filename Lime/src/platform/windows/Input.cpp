#include "Pch.hpp"
#include "Input.hpp"
#include "core/Lime.hpp"

extern Lime gLimeEngine;

void Input::init() {
	// keyboard stuff
	const Uint8* temp = SDL_GetKeyboardState(&mKeyCount);
	mCurrentKeyboardState = new Uint8[mKeyCount];
	mPrevKeyboardState = new Uint8[mKeyCount];

	memset(mCurrentKeyboardState, 0, mKeyCount * sizeof(Uint8));
	memset(mPrevKeyboardState, 0, mKeyCount * sizeof(Uint8));

	// mouse stuff
	mMousePosition = new glm::vec2{ 0.0f, 0.0f };

	//reset all states
	for (int i = 0; i < (int)mouseButtons::TOTAL; i++) {
		mMouseButtonStates.push_back(false);
	}

	// register callbacks
	gLimeEngine.addEventListener(EventID::E_WINDOW_KEY_PRESSED, std::bind(&Input::onEvent, this, std::placeholders::_1));
	gLimeEngine.addEventListener(EventID::E_WINDOW_KEY_RELEASED, std::bind(&Input::onEvent, this, std::placeholders::_1));
	gLimeEngine.addEventListener(EventID::E_WINDOW_KEY_TRIGGERED, std::bind(&Input::onEvent, this, std::placeholders::_1));
	gLimeEngine.addEventListener(EventID::E_WINDOW_MOUSE_DOWN, std::bind(&Input::onEvent, this, std::placeholders::_1));
	gLimeEngine.addEventListener(EventID::E_WINDOW_MOUSE_UP, std::bind(&Input::onEvent, this, std::placeholders::_1));
	gLimeEngine.addEventListener(EventID::E_WINDOW_MOUSE_MOVE, std::bind(&Input::onEvent, this, std::placeholders::_1));
}
void Input::update() {
	// keyboard stuff
	const Uint8* temp = SDL_GetKeyboardState(&mKeyCount);
	memcpy(mPrevKeyboardState, mCurrentKeyboardState, mKeyCount * sizeof(Uint8));
	memcpy(mCurrentKeyboardState, temp, mKeyCount * sizeof(Uint8));
}
void Input::onEvent(Event& e) {
	if (e.getType() == EventID::E_WINDOW_KEY_PRESSED) {
		LM_CORE_TRACE("[EVENT ID: {}] Key Pressed scancode: {}",e.getType(),e.getParam<SDL_Scancode>(EventID::P_WINDOW_KEY_PRESSED_KEYCODE));
	}
	else if (e.getType() == EventID::E_WINDOW_KEY_RELEASED) {
		LM_CORE_TRACE("[EVENT ID: {}] Key Released scancode: {}", e.getType(), e.getParam<SDL_Scancode>(EventID::P_WINDOW_KEY_RELEASED_KEYCODE));
	}
	else if (e.getType() == EventID::E_WINDOW_KEY_TRIGGERED) {
		LM_CORE_TRACE("[EVENT ID: {}] Key Triggered scancode: {}", e.getType(), e.getParam<SDL_Scancode>(EventID::P_WINDOW_KEY_TRIGGERED_KEYCODE));
	}
	else if (e.getType() == EventID::E_WINDOW_MOUSE_DOWN) {
		auto button = e.getParam<int>(EventID::P_WINDOW_MOUSE_DOWN_BUTTON);
		auto x = e.getParam<float>(EventID::P_WINDOW_MOUSE_DOWN_X);
		auto y = e.getParam<float>(EventID::P_WINDOW_MOUSE_DOWN_Y);
		LM_CORE_TRACE("[EVENT ID: {}] Mouse down button: {} position: ({},{})", e.getType(), button, x, y);
	}
	else if (e.getType() == EventID::E_WINDOW_MOUSE_UP) {
		auto button = e.getParam<int>(EventID::P_WINDOW_MOUSE_UP_BUTTON);
		auto x = e.getParam<float>(EventID::P_WINDOW_MOUSE_UP_X);
		auto y = e.getParam<float>(EventID::P_WINDOW_MOUSE_UP_Y);
		LM_CORE_TRACE("[EVENT ID: {}] Mouse up button: {} position: ({},{})", e.getType(), button, x, y);
	}
	else if (e.getType() == EventID::E_WINDOW_MOUSE_MOVE) {
		auto x = e.getParam<float>(EventID::P_WINDOW_MOUSE_MOVE_X);
		auto y = e.getParam<float>(EventID::P_WINDOW_MOUSE_MOVE_Y);
		LM_CORE_TRACE("[EVENT ID: {}] Mouse move position: ({},{})", e.getType(), x, y);
	}
	
}
bool Input::isKeyPressed(SDL_Scancode keycode) {
	return(mCurrentKeyboardState[keycode]);
}
bool Input::isKeyReleased(SDL_Scancode keycode) {
	return(!(mCurrentKeyboardState[keycode]) && (mPrevKeyboardState[keycode]));
}
bool Input::isKeyTriggered(SDL_Scancode keycode) {
	return ((mCurrentKeyboardState[keycode]) && !(mPrevKeyboardState[keycode]));
}
void Input::mouseButtonDown(SDL_Event event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		mMouseButtonStates[mouseButtons::LB] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE) {
		mMouseButtonStates[mouseButtons::MB] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT) {
		mMouseButtonStates[mouseButtons::RB] = true;
	}
}

void Input::mouseButtonUp(SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT) {
		mMouseButtonStates[mouseButtons::LB] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE) {
		mMouseButtonStates[mouseButtons::MB] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT) {
		mMouseButtonStates[mouseButtons::RB] = false;
	}
}

bool Input::mouseMove(SDL_Event event) {

	if (event.type == SDL_MOUSEMOTION) {
		mMouseDX = event.motion.x - mMousePosition->x;
		mMouseDY = event.motion.y - mMousePosition->y;

		mMousePosition->x = float(event.motion.x);
		mMousePosition->y = float(event.motion.y);

		if (mMouseDX != 0.0f || mMouseDY != 0.0f) {
			return true;
		}
	}
	return false;
}

bool Input::getMouseButtonState(int buttonNumber) {
	return mMouseButtonStates[buttonNumber];
}

glm::vec2* Input::getMousePosition() {
	return mMousePosition;
}

float Input::mX() {
	return mMousePosition->x;
}

float Input::mY() {
	return mMousePosition->y;
}

