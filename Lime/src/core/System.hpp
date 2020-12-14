/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: System.hpp
Purpose: BAse System class
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

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
