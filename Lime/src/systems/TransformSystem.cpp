#include "Pch.hpp"
#include "TransformSystem.hpp"
#include "core/Lime.hpp"
#include "components/TransformComponent.hpp"
#include "glm/gtx/transform.hpp"

extern Lime gLimeEngine;

void TransformSystem::init() {

	gLimeEngine.addEventListener(EventID::E_BROADCAST_EVENT, [this](Event& e) {this->onEvent(e); });
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
