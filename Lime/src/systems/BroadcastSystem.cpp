#include "Pch.hpp"
#include "BroadcastSystem.hpp"
#include "core/Lime.hpp"

extern Lime gLimeEngine;


void BroadcastSystem::init(){

	if (!mInit) {
		gLimeEngine.addEventListener(EventID::E_BROADCAST_EVENT, [this](Event& e) {this->onEvent(e); });
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
