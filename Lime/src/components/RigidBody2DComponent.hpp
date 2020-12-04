#ifndef RIGIDBODY2DCOMPONENT_HPP
#define RIGIDBODY2DCOMPONENT_HPP
#include "Pch.hpp"
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "nlohmann/json.hpp"
#include "utils/Shapes.hpp"

class RigidBody2DComponent {
public:
	glm::vec3 force;
	glm::vec3 acceleration;
	glm::vec3 velocity;
	// linear
	float mass;
	float invmass; // not needed to deserialize
	float restitution;
	float density;
	// rotational
	float inertia;
	float invinertia;
};

// RIGIDBODY2D SERDE
inline void to_json(ordered_json& j, RigidBody2DComponent& x) {
	to_json(j["force"], x.force);
	to_json(j["acceleration"], x.acceleration);
	to_json(j["velocity"], x.velocity);
	to_json(j["mass"],x.mass);
	to_json(j["invmass"], x.invmass);
	to_json(j["restitution"], x.restitution);
	to_json(j["density"], x.density);
	to_json(j["inertia"], x.inertia);
	to_json(j["invinertia"], x.invinertia);
}

inline void from_json(ordered_json& j, RigidBody2DComponent& x) {
	from_json(j["force"], x.force);
	from_json(j["acceleration"], x.acceleration);
	from_json(j["velocity"], x.velocity);
	from_json(j["mass"], x.mass);
	if (x.mass == 0.0f) {
		x.invmass = 0.0f;
	}
	else {
		x.invmass = 1.0f / x.mass;
	}
	from_json(j["restitution"], x.restitution);
	from_json(j["density"], x.density);
	from_json(j["inertia"], x.inertia);
	if (x.inertia == 0.0f) {
		x.invinertia = 0.0f;
	}
	else {
		x.invinertia = 1.0f / x.inertia;
	}
}	

#endif // !RIGIDBODY2DCOMPONENT_HPP
