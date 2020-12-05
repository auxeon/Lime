#ifndef MATHHELPERS_HPP
#define MATHHELPERS_HPP
#include "Pch.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "components/CameraComponent.hpp"
#include "components/TransformComponent.hpp"

void orthoCamUpdateVectors(CameraComponent& cam) {
	glm::vec3 dir;
	dir.x = cos(DEG2RAD(cam.yrot)) * cos(DEG2RAD(cam.xrot));
	dir.y = sin(DEG2RAD(cam.xrot));
	dir.z = sin(DEG2RAD(cam.yrot)) * cos(DEG2RAD(cam.xrot));
	cam.lookat = dir;
	cam.right = glm::normalize(glm::cross(cam.lookat, cam.wup));
	cam.up = glm::normalize(glm::cross(cam.right, cam.lookat));
}

void orthoCamMouseMove(CameraComponent& cam, float xoffset, float yoffset, bool limitpitch) {
	xoffset = xoffset * cam.sensitivity;
	yoffset = yoffset * cam.sensitivity;
	cam.yrot += xoffset;
	cam.xrot += yoffset;
	if (limitpitch) {
		cam.xrot = cam.xrot > 89.0f ? 89.0f : cam.xrot;
		cam.xrot = cam.xrot < -89.0f ? -89.0f : cam.xrot;
	}
	orthoCamUpdateVectors(cam);
}
void orthoCamKeyboard(CameraComponent& cam, TransformComponent& txfm, CameraMovements dir, float dt)
{
	float velocity = cam.speed * dt;
	if (dir == CameraMovements::CM_FORWARD)
		txfm.position += cam.lookat * velocity;
	if (dir == CameraMovements::CM_BACKWARD)
		txfm.position -= cam.lookat * velocity;
	if (dir == CameraMovements::CM_LEFT)
		txfm.position -= cam.right * velocity;
	if (dir == CameraMovements::CM_RIGHT)
		txfm.position += cam.right * velocity;
}

void orthoInitCamera(CameraComponent& cam, float left, float right, float bottom, float top) {
	cam.projmat = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	cam.viewmat = glm::mat4(1.0f);
	cam.x = 0;
	cam.y = 0;
	cam.height = SCREEN_HEIGHT;
	cam.width = SCREEN_WIDTH;
}

void orthoSetProjection(CameraComponent& cam, float left, float right, float bottom, float top) {
	cam.projmat = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}

void orthoUpdateView(CameraComponent& cam, TransformComponent& txfm) {
	cam.viewmat = glm::lookAt(txfm.position, txfm.position + cam.lookat, cam.up);
	//glm::lookAt()
}

#endif // !MATHHELPERS_HPP
