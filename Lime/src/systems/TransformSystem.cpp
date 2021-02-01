/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: TransformSystem.cpp
Purpose: update Transforms
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

#include "Pch.hpp"
#include "TransformSystem.hpp"
#include "core/Lime.hpp"
#include "components/TransformComponent.hpp"
#include "glm/gtx/transform.hpp"

extern Lime gLimeEngine;

void TransformSystem::init() {

	if (!mInit) {
		gLimeEngine.addEventListener(EventID::E_BROADCAST_EVENT, std::bind(&TransformSystem::onEvent, this, std::placeholders::_1));
		mInit = true;
	}
}

void TransformSystem::update() {
	for (auto& entity : mEntities) {
		auto& transformComponent = gLimeEngine.getComponent<TransformComponent>(entity);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transformComponent.position);

		model = glm::translate(model, glm::vec3(0.5f * transformComponent.size.x, 0.5f * transformComponent.size.y, 0.0f));
		model = glm::rotate(model, glm::radians(transformComponent.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * transformComponent.size.x, -0.5f * transformComponent.size.y, 0.0f));

		model = glm::scale(model, transformComponent.size);

		transformComponent.model = model;
	}
}

void TransformSystem::onEvent(Event& e) {

}
