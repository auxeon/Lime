#ifndef CONTROLLERCOMPONENT_HPP
#define CONTROLLERCOMPONENT_HPP
#include "Pch.hpp"
#include "SDL_scancode.h"
#include "utils/JsonEnums.hpp"

class ControllerComponent {
public:
	SDL_Scancode UP;
	SDL_Scancode DOWN;
	SDL_Scancode LEFT;
	SDL_Scancode RIGHT;
	SDL_Scancode ACTION01;
	SDL_Scancode ACTION02;
	SDL_Scancode ROTLEFT;
	SDL_Scancode ROTRIGHT;
	glm::vec3 STEP;
	string SPEAK;
};
// CONTROLLER COMPONENT SERDE
inline void to_json(ordered_json& j, const ControllerComponent& x) {
	to_json(j["UP"], x.UP);
	to_json(j["DOWN"], x.DOWN);
	to_json(j["LEFT"], x.LEFT);
	to_json(j["RIGHT"], x.RIGHT);
	to_json(j["ACTION01"], x.ACTION01);
	to_json(j["ACTION02"], x.ACTION02);
	to_json(j["ROTLEFT"], x.ROTLEFT);
	to_json(j["ROTRIGHT"], x.ROTRIGHT);
	to_json(j["STEP"], x.STEP);
	to_json(j["SPEAK"], x.SPEAK);
}


inline void from_json(const ordered_json& j, ControllerComponent& x) {
	from_json(j["UP"], x.UP);
	from_json(j["DOWN"], x.DOWN);
	from_json(j["LEFT"], x.LEFT);
	from_json(j["RIGHT"], x.RIGHT);
	from_json(j["ACTION01"], x.ACTION01);
	from_json(j["ACTION02"], x.ACTION02);
	from_json(j["ROTLEFT"], x.ROTLEFT);
	from_json(j["ROTRIGHT"], x.ROTRIGHT);
	from_json(j["STEP"], x.STEP);
	from_json(j["SPEAK"], x.SPEAK);
}
#endif // !CONTROLLERCOMPONENT_HPP
