#ifndef DMSYSTEM_HPP
#define DMSYSTEM_HPP
#include "Pch.hpp"
#include "core/System.hpp"
class DMSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
};
#endif // !DMSYSTEM_HPP