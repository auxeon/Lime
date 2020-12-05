#include "Pch.hpp"
#include "CameraSystem.hpp"
#include "core/Lime.hpp"
#include "components/CameraComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "components/TransformComponent.hpp"
#include "math/MathHelpers.hpp"
#include "math.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

extern Lime gLimeEngine;
using cp = ControllerComponent;
using tf = TransformComponent;
using cm = CameraComponent;



void CameraSystem::init(){

	for (auto& entity : mEntities) {
		auto& ctrl = gLimeEngine.getComponent<cp>(entity);
		auto& txfm = gLimeEngine.getComponent<tf>(entity);
		auto& cam = gLimeEngine.getComponent<cm>(entity);
		orthoInitCamera(cam, 0, cam.width, cam.height, 0);
	}
	// register the call backs 
	gLimeEngine.addEventListener(EventID::E_WINDOW_KEY_PRESSED, [this](Event& e) {this->onEvent(e); });
	gLimeEngine.addEventListener(EventID::E_WINDOW_MOUSE_MOVE, [this](Event& e) {this->onEvent(e); });
	gLimeEngine.addEventListener(EventID::E_WINDOW_RESIZED, [this](Event& e) {this->onEvent(e); });
}

void CameraSystem::update(){
	//update for all the camera components the current 
	for (auto& entity : mEntities) {
		auto& ctrl = gLimeEngine.getComponent<cp>(entity);
		auto& txfm = gLimeEngine.getComponent<tf>(entity);
		auto& cam = gLimeEngine.getComponent<cm>(entity);
		orthoUpdateView(cam, txfm);
	}
}

void CameraSystem::onEvent(Event& e){
	// add the camera controller actions 
	if (e.getType() == EventID::E_WINDOW_KEY_PRESSED) {
		auto button = e.getParam<SDL_Scancode>(EventID::P_WINDOW_KEY_PRESSED_KEYCODE);
		for (auto entity : mEntities) {
			auto& ctrl = gLimeEngine.getComponent<cp>(entity);
			auto& txfm = gLimeEngine.getComponent<tf>(entity);
			auto& cam = gLimeEngine.getComponent<cm>(entity);
			bool camUpdated = false;
			if (ctrl.UP == button) {
				orthoCamMouseMove(cam, 0, 5.0f, true);
				camUpdated = true;
				// [replace with keyboard functions]
			}
			if (ctrl.DOWN == button) {
				orthoCamMouseMove(cam, 0, -5.0f, true);
				camUpdated = true;
			}
			if (ctrl.RIGHT == button) {
				orthoCamMouseMove(cam, 5.0f, 0, true);
				camUpdated = true;
			}
			if (ctrl.LEFT == button) {
				orthoCamMouseMove(cam, -5.0f, 0, true);
				camUpdated = true;
			}

		}
	}

	if (e.getType() == EventID::E_WINDOW_RESIZED) {
		auto w = (int)e.getParam<unsigned int>(EventID::P_WINDOW_RESIZED_WIDTH);
		auto h = (int)e.getParam<unsigned int>(EventID::P_WINDOW_RESIZED_HEIGHT);
		for (auto entity : mEntities) {
			auto& ctrl = gLimeEngine.getComponent<cp>(entity);
			auto& txfm = gLimeEngine.getComponent<tf>(entity);
			auto& cam = gLimeEngine.getComponent<cm>(entity);
			cam.width = w;
			cam.height = h;
			orthoSetProjection(cam, -w / h * cam.zoom, w / h * cam.zoom, -cam.zoom, cam.zoom);
		}
	}
}
