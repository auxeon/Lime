#ifndef BROADCASTSYSTEM_HPP
#define BROADCASTSYSTEM_HPP
#include "Pch.hpp"
#include "core/System.hpp"
class BroadcastSystem : public System{
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
};
#endif // !BROADCASTSYSTEM_HPP
