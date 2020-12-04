#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP
#include "Pch.hpp"
#include "core/System.hpp"

class PhysicsSystem : public System {
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
};
#endif // !PHYSICSSYSTEM_HPP
