#ifndef CAMERASYSTEM_HPP
#define CAMERASYSTEM_HPP
#include "Pch.hpp"
#include "core/System.hpp"
#include "core/Event.hpp"
class CameraSystem : public System{
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
	EntityID activeCamera;
};
#endif // !CAMERASYSTEM_HPP
