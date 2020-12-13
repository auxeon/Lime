#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Pch.hpp"
//forward declare 
class Event;

class System{
public:
	virtual void init() {

	}
	virtual void update() {

	}
	virtual void onEvent(Event& e) {

	}
public:
	std::set<EntityID> mEntities;
	bool mInit = false;
};

#endif
