/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: ControllerSystem.cpp
Purpose: Controller components system
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

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
	if (!mInit) {
		gLimeEngine.addEventListener(EventID::E_WINDOW_KEY_PRESSED, [this](Event& e) {this->onEvent(e); });
		mInit = true;
	}
}

void ControllerSystem::update(){
	for (auto& entity : mEntities) {
		
	}
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
					if (gLimeEngine.hasComponent<RigidBody2DComponent>(entity)) {
						auto& rb = gLimeEngine.getComponent<RigidBody2DComponent>(entity);
						//rb.velocity.y = controllerComponent.STEP.y;
						rb.force.y = controllerComponent.STEP.y;
					}
					else {
						transformComponent.position += glm::vec3(0.0f, controllerComponent.STEP.y, 0.0f);
					}

					LM_INFO("[Entity ID: {}] UP", entity);
				}

				if (controllerComponent.DOWN == button) {

					if (gLimeEngine.hasComponent<RigidBody2DComponent>(entity)) {
						//auto& rb = gLimeEngine.getComponent<RigidBody2DComponent>(entity);
						//rb.velocity.y = -controllerComponent.STEP.y;
					}
					else {
						transformComponent.position += glm::vec3(0.0f, -controllerComponent.STEP.y, 0.0f);
					}
					LM_INFO("[Entity ID: {}] DOWN", entity);
				}

				if (controllerComponent.LEFT == button) {
					if (gLimeEngine.hasComponent<RigidBody2DComponent>(entity)) {
						auto& rb = gLimeEngine.getComponent<RigidBody2DComponent>(entity);
						rb.velocity.x = -controllerComponent.STEP.x;
						transformComponent.size.x = -1*fabs(transformComponent.size.x);
					}
					else {
						transformComponent.position += glm::vec3(-controllerComponent.STEP.x, 0.0f, 0.0f);
					}
					LM_INFO("[Entity ID: {}] LEFT", entity);
				}

				if (controllerComponent.RIGHT == button) {
					if (gLimeEngine.hasComponent<RigidBody2DComponent>(entity)) {
						auto& rb = gLimeEngine.getComponent<RigidBody2DComponent>(entity);
						rb.velocity.x = controllerComponent.STEP.x;
						transformComponent.size.x = fabs(transformComponent.size.x);
					}
					else {
						transformComponent.position += glm::vec3(controllerComponent.STEP.x, 0.0f, 0.0f);
					}
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
					Event ebullet(EventID::E_BULLET_FIRED);
					ebullet.setParam<EntityID>(EventID::P_BULLET_FIRED_ORIGIN_ID, entity);
					gLimeEngine.sendEvent(ebullet);
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
