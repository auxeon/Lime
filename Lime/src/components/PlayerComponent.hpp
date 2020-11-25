#ifndef PLAYERCOMPONENT_HPP
#define PLAYERCOMPONENT_HPP
#include "Pch.hpp"
#include "glm/glm.hpp"
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
#endif // !PLAYERCOMPONENT_HPP
