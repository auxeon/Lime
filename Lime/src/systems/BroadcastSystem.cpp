/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: BroadcastSystem.cpp
Purpose: Broadcast messages
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

#include "Pch.hpp"
#include "BroadcastSystem.hpp"
#include "core/Lime.hpp"

extern Lime gLimeEngine;


void BroadcastSystem::init(){

	if (!mInit) {
		gLimeEngine.addEventListener(EventID::E_BROADCAST_EVENT, std::bind(&BroadcastSystem::onEvent, this, std::placeholders::_1));
		mInit = true;
	}
}

void BroadcastSystem::update(){

}

void BroadcastSystem::onEvent(Event& e){
	if (e.getType() == EventID::E_BROADCAST_EVENT) {
		for (const auto& entity : mEntities) {
			auto msg = e.getParam<string>(EventID::P_BROADCAST_EVENT_DATA);
			LM_CORE_INFO("[EntityID {}] BROADCAST RECEIVED: {}", entity, msg);
		}
	}
}
