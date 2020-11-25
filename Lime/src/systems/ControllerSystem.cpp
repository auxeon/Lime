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
	LM_INFO("Controller Component init");
}

void ControllerSystem::update(){

}

void ControllerSystem::onEvent(Event& e){
	float dt = gLimeEngine.dt;
	if (e.getType() == EventID::E_WINDOW_KEY_PRESSED) {
		auto button = e.getParam<SDL_Scancode>(EventID::P_WINDOW_KEY_PRESSED_KEYCODE);
		for (auto entity : mEntities) {

			auto& controllerComponent = gLimeEngine.getComponent<cp>(entity);
			auto& transformComponent = gLimeEngine.getComponent<tf>(entity);

			if (controllerComponent.UP == button) {
				transformComponent.matrix = glm::translate(transformComponent.matrix, glm::vec3(0.0f, controllerComponent.STEP.y, 0.0f));
				transformComponent.position = transformComponent.matrix * glm::vec4(transformComponent.position,1.0f);
				LM_INFO("[Entity ID: {}] UP", entity);
			}

			if (controllerComponent.DOWN == button) {
				transformComponent.matrix = glm::translate(transformComponent.matrix, glm::vec3(0.0f, -controllerComponent.STEP.y, 0.0f));
				transformComponent.position = transformComponent.matrix * glm::vec4(transformComponent.position, 1.0f);
				LM_INFO("[Entity ID: {}] DOWN", entity);
			}

			if (controllerComponent.LEFT == button) {
				transformComponent.matrix = glm::translate(transformComponent.matrix, glm::vec3(-controllerComponent.STEP.x, 0.0f, 0.0f));
				transformComponent.position = transformComponent.matrix * glm::vec4(transformComponent.position, 1.0f);
				LM_INFO("[Entity ID: {}] LEFT", entity);
			}

			if (controllerComponent.RIGHT == button) {
				transformComponent.matrix = glm::translate(transformComponent.matrix, glm::vec3(controllerComponent.STEP.x, 0.0f, 0.0f));
				transformComponent.position = transformComponent.matrix * glm::vec4(transformComponent.position, 1.0f);
				LM_INFO("[Entity ID: {}] RIGHT", entity);
			}

			if (controllerComponent.ROTLEFT == button) {
				transformComponent.matrix = glm::rotate(transformComponent.matrix, glm::radians(controllerComponent.STEP.z*5), glm::vec3(0.0f, 0.0f, 1.0f));
				LM_INFO("[Entity ID: {}] Rotate left", entity);
			}

			if (controllerComponent.ROTRIGHT == button) {
				transformComponent.matrix = glm::rotate(transformComponent.matrix, glm::radians(-controllerComponent.STEP.z*5), glm::vec3(0.0f, 0.0f, 1.0f));
				LM_INFO("[Entity ID: {}] Rotate right", entity);
			}
		}
	}
}
