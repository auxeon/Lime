#ifndef CONTROLLERCOMPONENT_HPP
#define CONTROLLERCOMPONENT_HPP
#include "Pch.hpp"
class ControllerComponent {
public:
	SDL_Scancode UP;
	SDL_Scancode DOWN;
	SDL_Scancode LEFT;
	SDL_Scancode RIGHT;
	SDL_Scancode ACTION01;
	SDL_Scancode ROTLEFT;
	SDL_Scancode ROTRIGHT;
	LMVec3 STEP;
};
#endif // !CONTROLLERCOMPONENT_HPP
