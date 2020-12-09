#include "Pch.hpp"
#include "ControllerSystem.hpp"
#include "core/Lime.hpp"
#include "components/ControllerComponent.hpp"
#include "components/TransformComponent.hpp"
#include "glm/gtx/transform.hpp"

extern Lime gLimeEngine;

using cp = ControllerComponent;
using tf = TransformComponent;

void ControllerSystem::init(){
	gLimeEngine.addEventListener(EventID::E_WINDOW_KEY_PRESSED, [this](Event& e) {this->onEvent(e); });
}

void ControllerSystem::update(){


}

void ControllerSystem::onEvent(Event& e){
	double dt = gLimeEngine.dt;
	if (e.getType() == EventID::E_WINDOW_KEY_PRESSED) {
		auto button = e.getParam<SDL_Scancode>(EventID::P_WINDOW_KEY_PRESSED_KEYCODE);
		for (auto entity : mEntities) {


			auto& controllerComponent = gLimeEngine.getComponent<cp>(entity);
			auto& transformComponent = gLimeEngine.getComponent<tf>(entity);

			if (e.getType() == EventID::E_WINDOW_KEY_PRESSED) {


				if (controllerComponent.UP == button) {
					transformComponent.position += glm::vec3(0.0f, controllerComponent.STEP.y, 0.0f);
					LM_INFO("[Entity ID: {}] UP", entity);
				}

				if (controllerComponent.DOWN == button) {

					transformComponent.position += glm::vec3(0.0f, -controllerComponent.STEP.y, 0.0f);
					LM_INFO("[Entity ID: {}] DOWN", entity);
				}

				if (controllerComponent.LEFT == button) {
					transformComponent.position += glm::vec3(-controllerComponent.STEP.x, 0.0f, 0.0f);
					LM_INFO("[Entity ID: {}] LEFT", entity);
				}

				if (controllerComponent.RIGHT == button) {
					transformComponent.position += glm::vec3(controllerComponent.STEP.x, 0.0f, 0.0f);
					LM_INFO("[Entity ID: {}] RIGHT", entity);
				}

				if (controllerComponent.ROTLEFT == button) {
					transformComponent.rotation.z += controllerComponent.STEP.z;
					LM_INFO("[Entity ID: {}] ROTATE LEFT", entity);
				}

				if (controllerComponent.ROTRIGHT == button) {
					transformComponent.rotation.z += -controllerComponent.STEP.z;
					LM_INFO("[Entity ID: {}] ROTATE RIGHT", entity);
				}

				if (controllerComponent.ACTION01 == button) {
					Event edebug(EventID::E_GRAPHICS_DEBUG_TOGGLE);
					gLimeEngine.sendEvent(edebug);
				}

				if (controllerComponent.ACTION02 == button) {
					Event espeak(EventID::E_DM_EVENT);
					espeak.setParam<EntityID>(EventID::P_DM_EVENT_ENTITYID, entity);
					espeak.setParam<string>(EventID::P_DM_EVENT_DATA, controllerComponent.SPEAK);
					gLimeEngine.sendEvent(espeak);
				}


			}
		}
	}
}
