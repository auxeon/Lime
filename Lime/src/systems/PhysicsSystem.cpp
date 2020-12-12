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
#include "glm/gtx/transform.hpp"


extern Lime gLimeEngine;

bool PhysicsSystem::accumulateImpulses = false;
bool PhysicsSystem::warmStarting = true;
bool PhysicsSystem::positionCorrection = true;



void PhysicsSystem::init(){


	gravity = glm::vec3{ 0.0f,-150.0f,0.0f };
	iterations = 10;

	//EntityID phyGround = gLimeEngine.createEntity();
	//// phyGround 
	//RigidBody2DComponent phyGround_rb;
	//TransformComponent phyGround_tf;
	//RenderBoxComponent phyGround_render;

	//set(phyGround_rb, glm::vec3{ 600.0f,20.0f,0.0f }, FLT_MAX);
	//phyGround_rb.position.x = 300.0f;
	//phyGround_rb.position.y = 200.0f;
	//phyGround_rb.rotation.x = phyGround_rb.rotation.y = phyGround_rb.rotation.z = 0.0f;
	//phyGround_render.color = glm::vec3{ 1.0f,1.0f,0.0f };

	//
	//phyGround_tf.size.x = phyGround_rb.size.x;
	//phyGround_tf.size.y = phyGround_rb.size.y;
	//phyGround_tf.size.z = 0.0f;
	//phyGround_tf.position.x = phyGround_rb.position.x;
	//phyGround_tf.position.y = phyGround_rb.position.y;
	//phyGround_tf.rotation = phyGround_rb.rotation;
	//phyGround_tf.position.z = 0.0f;

	//gLimeEngine.addComponent<TagComponent>(phyGround, TagComponent{
	//	"ground"
	//});
	//gLimeEngine.addComponent<TransformComponent>(phyGround, phyGround_tf);
	//gLimeEngine.addComponent<RigidBody2DComponent>(phyGround, phyGround_rb);
	//gLimeEngine.addComponent<RenderBoxComponent>(phyGround, phyGround_render);


	////EntityID phyGround = gLimeEngine.createEntity();
	////// phyGround 
	////RigidBody2DComponent phyGround_rb;
	////TransformComponent phyGround_tf;
	////RenderBoxComponent phyGround_render;

	////set(phyGround_rb, glm::vec3{ 100.0f,20.0f,0.0f }, FLT_MAX);
	////phyGround_rb.position.x = 300.0f;
	////phyGround_rb.position.y = 200.0f;
	////phyGround_render.color = glm::vec3{ 1.0f,1.0f,0.0f };


	//////phyGround_tf.size.x = phyGround_rb.size.x;
	//////phyGround_tf.size.y = phyGround_rb.size.y;
	//////phyGround_tf.size.z = 0.0f;
	//////phyGround_tf.position.x = phyGround_rb.position.x;
	//////phyGround_tf.position.y = phyGround_rb.position.y;
	//////phyGround_tf.position.z = 0.0f;

	////gLimeEngine.addComponent<TransformComponent>(phyGround, phyGround_tf);
	////gLimeEngine.addComponent<RigidBody2DComponent>(phyGround, phyGround_rb);
	////gLimeEngine.addComponent<RenderBoxComponent>(phyGround, phyGround_render);


	//EntityID phyBox = gLimeEngine.createEntity();
	//// upper phyBox
	//RigidBody2DComponent phyBox_rb;
	//TransformComponent phyBox_tf;
	//RenderBoxComponent phyBox_render;

	//set(phyBox_rb, glm::vec3{ 20.0f,20.0f,0.0f }, 200.0f);
	//phyBox_rb.position.x = 250.0f;
	//phyBox_rb.position.y = 600.0f;
	//phyBox_rb.rotation.x = phyBox_rb.rotation.y = phyBox_rb.rotation.z = 0.0f;
	//phyBox_rb.angularVelocity = 0.0f;
	//phyBox_render.color = glm::vec3{ 1.0f,1.0f,0.0f };

	//phyBox_tf.size.x = phyBox_rb.size.x;
	//phyBox_tf.size.y = phyBox_rb.size.y;
	//phyBox_tf.size.z = 0.0f;
	//phyBox_tf.position.x = phyBox_rb.position.x;
	//phyBox_tf.position.y = phyBox_rb.position.y;
	//phyBox_tf.rotation = phyBox_rb.rotation;
	//phyBox_tf.position.z = 0.0f;

	//gLimeEngine.addComponent<TagComponent>(phyBox, TagComponent{
	//"box"
	//});
	//gLimeEngine.addComponent<TransformComponent>(phyBox, phyBox_tf);
	//gLimeEngine.addComponent<RigidBody2DComponent>(phyBox, phyBox_rb);
	//gLimeEngine.addComponent<RenderBoxComponent>(phyBox, phyBox_render);

	gLimeEngine.addEventListener(EventID::E_WINDOW_KEY_PRESSED, [this](Event& e) {this->onEvent(e); });

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

	for (int i = 0; i < (int)mJoints.size(); ++i){
		mJoints[i]->PreStep(inv_dt);
	}

	// Perform iterations
	for (int i = 0; i < iterations; ++i){
		for (ArbIter arb = mArbiters.begin(); arb != mArbiters.end(); ++arb){
			arb->second.ApplyImpulse();
		}

		for (int j = 0; j < (int)mJoints.size(); ++j){
			mJoints[j]->ApplyImpulse();
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

	//// show contacts
	//glPointSize(4.0f);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glBegin(GL_POINTS);
	//std::map<ArbiterKey, Arbiter>::const_iterator iter;
	//for (iter = mArbiters.begin(); iter != mArbiters.end(); ++iter)
	//{
	//	const Arbiter& arbiter = iter->second;
	//	for (int i = 0; i < arbiter.numContacts; ++i)
	//	{
	//		Vec2 p = arbiter.contacts[i].position;
	//		glVertex2f(p.x, p.y);
	//	}
	//}
	//glEnd();
	//glPointSize(1.0f);


	// after the end of physics updates copy the values into the transform component 
	for (auto& entity : mEntities) {
		TransformComponent& tf = gLimeEngine.getComponent<TransformComponent>(entity);
		RigidBody2DComponent& rb = gLimeEngine.getComponent<RigidBody2DComponent>(entity);

		tf.position = rb.position;
		tf.rotation = rb.rotation;
		//tf.size = rb.size;

	}


}

void PhysicsSystem::onEvent(Event& e){
	if (e.getType() == EventID::E_WINDOW_KEY_PRESSED) {
		//std::cout << "physics onEvent";
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

void PhysicsSystem::add(Joint* joint){
	mJoints.push_back(joint);
}

void PhysicsSystem::clear() {
	mJoints.clear();
	mArbiters.clear();
}