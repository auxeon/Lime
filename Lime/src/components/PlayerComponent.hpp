#ifndef PLAYERCOMPONENT_HPP
#define PLAYERCOMPONENT_HPP
#include "Pch.hpp"
#include "glm/glm.hpp"
#include "utils/JsonEnums.hpp"

class PlayerComponent {
public:
	// current state
	PlayerStates state;
	float health;
	float score;
	// energy for attacks 
	float energy;
	glm::vec3 speed;
};


// CONTROLLER COMPONENT SERDE
inline void to_json(ordered_json& j, const PlayerComponent& x) {
	//to_json(j["state"],	string(LIMEENUMS_PLAYERSTATES::gEnumInt2Str[x.state]));
	to_json(j["state"], x.state);
	to_json(j["health"],x.health);
	to_json(j["score"],	x.score);
	to_json(j["energy"],x.energy);
	to_json(j["speed"],	x.speed);
}


inline void from_json(const ordered_json& j, PlayerComponent& x) {
	from_json(j["state"], x.state);
	from_json(j["health"], x.health);
	from_json(j["score"], x.score);
	from_json(j["energy"], x.energy);
	from_json(j["speed"], x.speed);
}
#endif // !PLAYERCOMPONENT_HPP
