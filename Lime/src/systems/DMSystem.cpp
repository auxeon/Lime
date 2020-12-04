#include "Pch.hpp"
#include "DMSystem.hpp"
#include "core/Lime.hpp"
#include "core/AudioManager.hpp"

extern Lime gLimeEngine;
extern AudioManager au;

void handleEventFunc(EntityID& entity, Event& e) {
	// write code here
	LM_CORE_INFO("[EntityID : {}]  SPEAK : {}", entity, e.getParam<string>(EventID::P_DM_EVENT_DATA));
	au.PlaySounds(e.getParam<string>(EventID::P_DM_EVENT_DATA));
}

void DMSystem::init(){
	gLimeEngine.addEventListener(EventID::E_DM_EVENT, [this](Event& e) {this->onEvent(e); });
}

void DMSystem::update(){

}

void DMSystem::onEvent(Event& e){
	if (e.getType() == EventID::E_DM_EVENT) {
		for (const auto& entity : mEntities) {
			auto recipient = e.getParam<EntityID>(EventID::P_DM_EVENT_ENTITYID);
			auto msg = e.getParam<string>(EventID::P_DM_EVENT_DATA);
			if(entity == recipient){
				handleEventFunc(recipient, e);
			}
		}
	}
}