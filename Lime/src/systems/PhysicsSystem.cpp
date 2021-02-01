/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: PhysicsUpdates.cpp
Purpose: Physics messages
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

#include "Pch.hpp"
#include "PhysicsSystem.hpp"
#include "core/Lime.hpp"
#include "glad/glad.h"
#include "systems/CameraSystem.hpp"
#include "components/TagComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "components/CameraComponent.hpp"
#include "components/RenderBoxComponent.hpp"
#include "glm/gtx/transform.hpp"


extern Lime gLimeEngine;
EntityID phyBullet = 0;

bool PhysicsSystem::accumulateImpulses = false;
bool PhysicsSystem::warmStarting = true;
bool PhysicsSystem::positionCorrection = true;



void PhysicsSystem::init(){

	if (!mInit) {
		gravity = glm::vec3{ 0.0f,-150.0f,0.0f };
		iterations = 10;
		//gLimeEngine.addEventListener(EventID::E_WINDOW_KEY_PRESSED, std::bind(&PhysicsSystem::onEvent, this, std::placeholders::_1));
		gLimeEngine.addEventListener(EventID::E_BULLET_FIRED, std::bind(&PhysicsSystem::onEvent, this, std::placeholders::_1));
		mInit = true;
	}

}

void PhysicsSystem::update(){
	// remember to also set the rigidbody position whereever transform component gets updated


	// do actual physics step
	float dt = (float)gLimeEngine.dt;
	float inv_dt = dt > 0.0f ? 1.0f / dt : 0.0f;

	// Determine overlapping bodies and update contact points.
	broadPhase();

	// Integrate forces.
	for (auto& entity : mEntities) {
		RigidBody2DComponent* b = &gLimeEngine.getComponent<RigidBody2DComponent>(entity);
		if (b->invMass == 0.0f)
			continue;

		b->velocity.x += dt * (gravity.x + b->invMass * b->force.x);
		b->velocity.y += dt * (gravity.y + b->invMass * b->force.y);
		b->angularVelocity += dt * b->invI * b->torque;
	}

	// Perform pre-steps.
	for (ArbIter arb = mArbiters.begin(); arb != mArbiters.end(); ++arb){
		arb->second.PreStep(inv_dt);
	}

	// Perform iterations
	for (int i = 0; i < iterations; ++i){
		for (ArbIter arb = mArbiters.begin(); arb != mArbiters.end(); ++arb){
			arb->second.ApplyImpulse();
		}
	}

	// Integrate Velocities
	for (auto& entity : mEntities) {
		RigidBody2DComponent* b = &gLimeEngine.getComponent<RigidBody2DComponent>(entity);

		b->position += dt * b->velocity;
		b->rotation.z += dt * b->angularVelocity;

		b->force = glm::vec3{ 0.0f, 0.0f, 0.0f };
		b->torque = 0.0f;
	}


	// after the end of physics updates copy the values into the transform component 
	for (auto& entity : mEntities) {
		TransformComponent& tf = gLimeEngine.getComponent<TransformComponent>(entity);
		RigidBody2DComponent& rb = gLimeEngine.getComponent<RigidBody2DComponent>(entity);

		tf.position = rb.position;
		tf.rotation = rb.rotation;
		//tf.size = rb.size;

	}

	for (auto& a : mArbiters) {
		if (a.second.numContacts > 0) {
			if (gLimeEngine.hasComponent<TagComponent>(a.second.body1->id) && gLimeEngine.hasComponent<TagComponent>(a.second.body2->id)) {
				string tag1 = gLimeEngine.getComponent<TagComponent>(a.second.body1->id).tag;
				string tag2 = gLimeEngine.getComponent<TagComponent>(a.second.body2->id).tag;
				//LM_CORE_INFO("Physics System : collision : ({},{})", tag1, tag2);

				if((tag1 == "player" && tag2 == "collider_water") || (tag1 == "collider_water" && tag2 == "player")) {
					LM_CORE_INFO("DEAD");
					Event event(EventID::E_GS_LEVEL);
					event.setParam<string>(EventID::P_GS_LEVEL_NAME, "Lime/lost.json");
					gLimeEngine.sendEvent(event);
					gLimeEngine.mCurrentState = "Lime/lost.json";
				}

				if ((tag1 == "player" && tag2 == "collider_lime") || (tag1 == "collider_lime" && tag2 == "player")) {
					LM_CORE_INFO("WON");
					Event event(EventID::E_GS_LEVEL);
					event.setParam<string>(EventID::P_GS_LEVEL_NAME, "Lime/won.json");
					gLimeEngine.sendEvent(event);
					gLimeEngine.mCurrentState = "Lime/won.json";
				}


			}
		}
	}

	for (auto& m : mEntities) {
		auto tc = gLimeEngine.getComponent<TagComponent>(m);
		auto rb = gLimeEngine.getComponent<RigidBody2DComponent>(m);
		if (tc.tag == "rasengan") {
			LM_CORE_INFO("rasengan position  : ({},{})", rb.position.x,rb.position.y);
		}
	}


}

void PhysicsSystem::onEvent(Event& e){
	bool right = false;

	//if (e.getType() == EventID::E_WINDOW_KEY_PRESSED) {
	//	
	//}

	if (e.getType() == EventID::E_BULLET_FIRED) {

		if (mEntities.find(phyBullet) != mEntities.end()) {
			gLimeEngine.destroyEntity(phyBullet);
		}

		EntityID id = e.getParam<EntityID>(EventID::P_BULLET_FIRED_ORIGIN_ID);
		TransformComponent* tx = &gLimeEngine.getComponent<TransformComponent>(id);

		if (tx->size.x < 0) {
			right = false;
		}
		else {
			right = true;
		}

		//if (right) {
			phyBullet = gLimeEngine.createEntity();
			//EntityID phyBox = gLimeEngine.createEntity();
			// upper phyBox
			RigidBody2DComponent phyBullet_rb;
			TransformComponent phyBullet_tf;
			RenderBoxComponent phyBullet_render;
			SpriteComponent phyBullet_sprite;
			
			phyBullet_rb.id = phyBullet;
			set(phyBullet_rb, glm::vec3{ 20.0f,20.0f,0.0f }, 2.0f);
			if(right){
				phyBullet_rb.size.x = fabs(phyBullet_rb.size.x);
				phyBullet_rb.velocity.x = 500.0f;
				phyBullet_rb.position.x = tx->position.x + tx->size.x;
			}
			else {
				phyBullet_rb.size.x = -fabs(phyBullet_rb.size.x);
				phyBullet_rb.velocity.x = -500.0f;
				phyBullet_rb.position.x = tx->position.x + tx->size.x;
			}

			phyBullet_rb.position.y = tx->position.y;
			phyBullet_rb.rotation.x = phyBullet_rb.rotation.y = phyBullet_rb.rotation.z = 0.0f;

			phyBullet_rb.angularVelocity = 0.0f;
			phyBullet_render.color = glm::vec3{ 1.0f,1.0f,0.0f };
			
			phyBullet_tf.size.x = phyBullet_rb.size.x;
			phyBullet_tf.size.y = phyBullet_rb.size.y;
			phyBullet_tf.size.z = 0.0f;
			phyBullet_tf.position.x = phyBullet_rb.position.x;
			phyBullet_tf.position.y = phyBullet_rb.position.y;
			phyBullet_tf.rotation = phyBullet_rb.rotation;
			phyBullet_tf.position.z = 0.0f;
			
			gLimeEngine.addComponent<TagComponent>(phyBullet, TagComponent{
			"rasengan"
			});
			gLimeEngine.addComponent<TransformComponent>(phyBullet, phyBullet_tf);
			gLimeEngine.addComponent(phyBullet, SpriteComponent{
				"Lime/res/rasengan.png",
				(GLuint)0,
				false,
				0.0f,
				1,
				1
				});
			gLimeEngine.addComponent<RigidBody2DComponent>(phyBullet, phyBullet_rb);
			gLimeEngine.addComponent<RenderBoxComponent>(phyBullet, phyBullet_render);



		//}
	}
}

void PhysicsSystem::broadPhase(){

	std::set<EntityID>::iterator i;
	std::set<EntityID>::iterator j;

	for (i = mEntities.begin(); i != mEntities.end();++i) {
		RigidBody2DComponent* bi = &gLimeEngine.getComponent<RigidBody2DComponent>(*i);

		for (j = std::next(i); j != mEntities.end(); ++j) {
			RigidBody2DComponent* bj = &gLimeEngine.getComponent<RigidBody2DComponent>(*j);

			if (bi->invMass == 0.0f && bj->invMass == 0.0f)
				continue;

			Arbiter newArb(bi, bj);
			ArbiterKey key(bi, bj);

			if (newArb.numContacts > 0){
				ArbIter iter = mArbiters.find(key);
				if (iter == mArbiters.end()){
					mArbiters.insert(ArbPair(key, newArb));
				}
				else{
					iter->second.Update(newArb.contacts, newArb.numContacts);
				}
			}
			else{
				mArbiters.erase(key);
			}
		}
	}
}

void PhysicsSystem::set(RigidBody2DComponent&rb, glm::vec3& size, float m) {
		rb.position = glm::vec3{ 0.0f,0.0f,0.0f };
		rb.rotation = glm::vec3{0.0f,0.0f,0.0f};
		rb.size = size;
		rb.velocity = glm::vec3{ 0.0f,0.0f,0.0f };
		rb.angularVelocity = 0.0f;
		rb.force = glm::vec3{ 0.0f,0.0f,0.0f };
		rb.torque = 0.0f;
		rb.friction = 0.2f;
		rb.mass = m;
		if (rb.mass < FLT_MAX)
		{
			rb.invMass = 1.0f / rb.mass;
			rb.I = rb.mass * (rb.size.x * rb.size.x + rb.size.y * rb.size.y) / 12.0f;
			rb.invI = 1.0f / rb.I;
		}
		else
		{
			rb.invMass = 0.0f;
			rb.I = FLT_MAX;
			rb.invI = 0.0f;
		}


}

void PhysicsSystem::addForce(EntityID entity, const glm::vec3& f) {
	// if the entity exists in the physics system
	if (mEntities.count(entity) == 1) {
		RigidBody2DComponent& rb = gLimeEngine.getComponent<RigidBody2DComponent>(entity);
		rb.force += f;
	}
}

void PhysicsSystem::clear() {
	mArbiters.clear();
}