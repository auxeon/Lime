#ifndef RIGIDBODY2DCOMPONENT_HPP
#define RIGIDBODY2DCOMPONENT_HPP
#include "Pch.hpp"

class RigidBody2DComponent {
public:
	EntityID id;
	// replicas of the transformComponent for ease of access
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 size;

	glm::vec3 force;
	float torque;

	glm::vec3 velocity;
	float angularVelocity; // z

	float friction;
	float mass;
	float invMass;
	float I;
	float invI;
};

// RIGIDBODY2D COMPONENT SERDE
inline void to_json(ordered_json& j, const RigidBody2DComponent& x) {

	to_json(j["id"], x.id);
	to_json(j["position"], x.position);
	to_json(j["rotation"], x.rotation);
	to_json(j["size"], x.size);

	to_json(j["force"], x.force);
	to_json(j["torque"], x.torque);

	to_json(j["velocity"], x.velocity);
	to_json(j["angularVelocity"], x.angularVelocity);
	
	to_json(j["friction"], x.friction);
	to_json(j["mass"], x.mass);
	to_json(j["invMass"], x.invMass);
	to_json(j["I"], x.I);
	to_json(j["invI"], x.invI);
}


inline void from_json(const ordered_json& j, RigidBody2DComponent& x) {

	from_json(j["id"], x.id);
	from_json(j["position"], x.position);
	from_json(j["rotation"], x.rotation);
	from_json(j["size"], x.size);

	from_json(j["force"], x.force);
	from_json(j["torque"], x.torque);

	from_json(j["velocity"], x.velocity);
	from_json(j["angularVelocity"], x.angularVelocity);

	from_json(j["friction"], x.friction);
	from_json(j["mass"], x.mass);
	if (x.mass == 0.0f) {
		x.invMass = 0.0f;
	}
	else {
		x.invMass = 1.0f / x.mass;
	}
	from_json(j["I"], x.I);
	if (x.I == 0.0f) {
		x.invI = 0.0f;
	}
	else {
		x.invI = 1.0f / x.I;
	}
}


#endif // !RIGIDBODY2DCOMPONENT_HPP
