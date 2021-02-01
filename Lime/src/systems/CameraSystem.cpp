/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: CameraSystem.cpp
Purpose: update cameras
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

#include "Pch.hpp"
#include "CameraSystem.hpp"
#include "core/Lime.hpp"
#include "components/CameraComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/TagComponent.hpp"
#include "math/MathHelpers.hpp"
#include "math.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

extern Lime gLimeEngine;
using tf = TransformComponent;
using cm = CameraComponent;
glm::vec3 campos;

void CameraSystem::init(){

	for (auto& entity : mEntities) {
		auto& txfm = gLimeEngine.getComponent<tf>(entity);
		auto& cam = gLimeEngine.getComponent<cm>(entity);
		orthoInitCamera(cam, (float)0, (float)cam.width, (float)0, (float)cam.height);
	}
	if (!mInit) {
		// register the call backs 
		gLimeEngine.addEventListener(EventID::E_WINDOW_KEY_PRESSED, std::bind(&CameraSystem::onEvent, this, std::placeholders::_1));
		gLimeEngine.addEventListener(EventID::E_WINDOW_MOUSE_MOVE, std::bind(&CameraSystem::onEvent, this, std::placeholders::_1));
		gLimeEngine.addEventListener(EventID::E_WINDOW_RESIZED, std::bind(&CameraSystem::onEvent, this, std::placeholders::_1));
		mInit = true;
	}
}

void CameraSystem::update(){


	//update for all the camera components the current 
	for (auto& entity : mEntities) {

		auto& txfm = gLimeEngine.getComponent<tf>(entity);
		auto& cam = gLimeEngine.getComponent<cm>(entity);
		orthoUpdateView(cam, txfm);

		glViewport(cam.x, cam.y, cam.width, cam.height);
		glScissor(cam.x, cam.y, cam.width, cam.height);
		glEnable(GL_SCISSOR_TEST);

		glm::vec4 color = rgba255((unsigned int)cam.clearcolor.r, (unsigned int)cam.clearcolor.g, (unsigned int)cam.clearcolor.b, (unsigned int)cam.clearcolor.a);
		glClearColor(color.x, color.y, color.z, color.w);
	}
}

void CameraSystem::onEvent(Event& e){
	// add the camera controller actions 
	if (e.getType() == EventID::E_WINDOW_KEY_PRESSED) {
		auto button = e.getParam<SDL_Scancode>(EventID::P_WINDOW_KEY_PRESSED_KEYCODE);

		TagComponent* backtag = NULL;
		TransformComponent* backt = NULL;
		if (gLimeEngine.hasComponent<TransformComponent>(0) && gLimeEngine.hasComponent<TagComponent>(0)) {
			backtag = &gLimeEngine.getComponent<TagComponent>(0);
			backt = &gLimeEngine.getComponent<TransformComponent>(0);
		}
		for (auto entity : mEntities) {
			auto& txfm = gLimeEngine.getComponent<tf>(entity);
			auto& cam = gLimeEngine.getComponent<cm>(entity);
			auto& tag = gLimeEngine.getComponent<TagComponent>(entity);
			
			bool camUpdated = false;
			if (SDL_SCANCODE_T == button) {
				//orthoCamMouseMove(cam, 0, ctrl.STEP.y, true);
				txfm.position.y += cam.speed;
				camUpdated = true;
				if (backtag->tag == "background" && tag.tag == "camera") {
					backt->position.y += -cam.speed;
				}
			}
			if (SDL_SCANCODE_G == button) {
				//orthoCamMouseMove(cam, 0, -ctrl.STEP.y, true);
				txfm.position.y += -cam.speed;
				camUpdated = true;

				if (backtag->tag == "background" && tag.tag == "camera") {
					backt->position.y += cam.speed;
				}
			}
			if (SDL_SCANCODE_H == button) {
				//orthoCamMouseMove(cam, ctrl.STEP.x, 0, true);
				txfm.position.x += -cam.speed;
				camUpdated = true;

				if (backtag->tag == "background" && tag.tag == "camera") {
					backt->position.x += cam.speed;
				}
			}
			if (SDL_SCANCODE_F == button) {
				//orthoCamMouseMove(cam, -ctrl.STEP.x, 0, true);
				txfm.position.x += cam.speed;
				camUpdated = true;

				if (backtag->tag == "background" && tag.tag == "camera") {
					backt->position.x += -cam.speed;
				}
			}

		}
	}

	if (e.getType() == EventID::E_WINDOW_RESIZED) {
		auto w = (int)e.getParam<unsigned int>(EventID::P_WINDOW_RESIZED_WIDTH);
		auto h = (int)e.getParam<unsigned int>(EventID::P_WINDOW_RESIZED_HEIGHT);
		for (auto entity : mEntities) {
			auto& txfm = gLimeEngine.getComponent<tf>(entity);
			auto& cam = gLimeEngine.getComponent<cm>(entity);
			cam.width = w;
			cam.height = h;
			//orthoSetProjection(cam, -w / h * cam.zoom, w / h * cam.zoom, -cam.zoom, cam.zoom);
			orthoSetProjection(cam, (float)0, (float)w, (float)0, (float)h);
		}
	}
}
