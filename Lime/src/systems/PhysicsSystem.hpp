#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP
#include "Pch.hpp"
#include "core/System.hpp"

#include "components/RigidBody2DComponent.hpp"
#include "physics/MathUtils.hpp"
#include "physics/Arbiter.hpp"


typedef std::map<ArbiterKey, Arbiter>::iterator ArbIter;
typedef std::pair<ArbiterKey, Arbiter> ArbPair;


class PhysicsSystem : public System {
public:

	void init() override;
	void update() override;
	void onEvent(Event& e) override;

	void broadPhase();

	// for the rigidbody 
	void set(RigidBody2DComponent& rb, glm::vec3& size, float m);
	void addForce(EntityID entity, const glm::vec3& f);

	void clear();

	std::map<ArbiterKey, Arbiter> mArbiters;

	glm::vec3 gravity;
	int iterations;

	static bool accumulateImpulses;
	static bool warmStarting;
	static bool positionCorrection;

};
#endif // !PHYSICSSYSTEM_HPP
