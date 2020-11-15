#ifndef CONTROLLERSYSTEM_HPP
#define CONTROLLERSYSTEM_HPP
#include "Pch.hpp"
#include "core/System.hpp"
class Event;
class ControllerSystem : public System{
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
};
#endif // !CONTROLLERSYSTEM_HPP
