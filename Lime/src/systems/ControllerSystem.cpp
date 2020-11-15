#include "Pch.hpp"
#include "ControllerSystem.hpp"
#include "core/Lime.hpp"
#include "components/ControllerComponent.hpp"
#include "components/TransformComponent.hpp"

extern Lime gLimeEngine;

using cp = ControllerComponent;
using tf = TransformComponent;

void ControllerSystem::init(){
	gLimeEngine.addEventListener(EventID::E_WINDOW_KEY_PRESSED, [this](Event& e) {this->onEvent(e); });
	LM_INFO("Controller Component init");
}

void ControllerSystem::update(){

}

void ControllerSystem::onEvent(Event& e){
	if (e.getType() == EventID::E_WINDOW_KEY_PRESSED) {
		auto button = e.getParam<SDL_Scancode>(EventID::P_WINDOW_KEY_PRESSED_KEYCODE);
		for (auto e : mEntities) {
			auto& controllerComponent = gLimeEngine.getComponent<cp>(e);
			auto& transformComponent = gLimeEngine.getComponent<tf>(e);
			if (controllerComponent.UP == button) {
				transformComponent.y -= controllerComponent.STEP.y;
				LM_INFO("[Entity ID: {}] Transform position: ({},{},{})", e, transformComponent.x, transformComponent.y, transformComponent.z);
			}
			if (controllerComponent.DOWN == button) {
				transformComponent.y += controllerComponent.STEP.y;
				LM_INFO("[Entity ID: {}] Transform position: ({},{},{})", e, transformComponent.x, transformComponent.y, transformComponent.z);
			}

			if (controllerComponent.LEFT == button) {
				transformComponent.x -= controllerComponent.STEP.x;
				LM_INFO("[Entity ID: {}] Transform position: ({},{},{})", e, transformComponent.x, transformComponent.y, transformComponent.z);
			}

			if (controllerComponent.RIGHT == button) {
				transformComponent.x += controllerComponent.STEP.x;
				LM_INFO("[Entity ID: {}] Transform position: ({},{},{})", e, transformComponent.x, transformComponent.y, transformComponent.z);
			}

		}
	}
}
