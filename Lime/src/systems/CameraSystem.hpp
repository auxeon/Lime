#ifndef CAMERASYSTEM_HPP
#define CAMERASYSTEM_HPP
#include "Pch.hpp"
#include "core/System.hpp"
#include "core/Event.hpp"
class CameraSystem : public System{
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
};
#endif // !CAMERASYSTEM_HPP
