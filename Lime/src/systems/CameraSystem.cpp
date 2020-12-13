#include "Pch.hpp"
#include "CameraSystem.hpp"
#include "core/Lime.hpp"
#include "components/CameraComponent.hpp"
#include "components/TransformComponent.hpp"
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
		gLimeEngine.addEventListener(EventID::E_WINDOW_KEY_PRESSED, [this](Event& e) {this->onEvent(e); });
		gLimeEngine.addEventListener(EventID::E_WINDOW_MOUSE_MOVE, [this](Event& e) {this->onEvent(e); });
		gLimeEngine.addEventListener(EventID::E_WINDOW_RESIZED, [this](Event& e) {this->onEvent(e); });
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

		//auto camtx = &gLimeEngine.getComponent<TransformComponent>(0);
		//auto tag = &gLimeEngine.getComponent<TagComponent>(0);

		//if (tag->tag == "background") {
		//	LM_CORE_INFO(tag->tag);
		//}

		for (auto entity : mEntities) {
			auto& txfm = gLimeEngine.getComponent<tf>(entity);
			auto& cam = gLimeEngine.getComponent<cm>(entity);
			bool camUpdated = false;
			if (SDL_SCANCODE_T == button) {
				//orthoCamMouseMove(cam, 0, ctrl.STEP.y, true);
				txfm.position.y += cam.speed;
				camUpdated = true;
				// [replace with keyboard functions]
				campos = txfm.position;
			}
			if (SDL_SCANCODE_G == button) {
				//orthoCamMouseMove(cam, 0, -ctrl.STEP.y, true);
				txfm.position.y += -cam.speed;
				camUpdated = true;
			}
			if (SDL_SCANCODE_H == button) {
				//orthoCamMouseMove(cam, ctrl.STEP.x, 0, true);
				txfm.position.x += cam.speed;
				camUpdated = true;
			}
			if (SDL_SCANCODE_F == button) {
				//orthoCamMouseMove(cam, -ctrl.STEP.x, 0, true);
				txfm.position.x += -cam.speed;
				camUpdated = true;
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
