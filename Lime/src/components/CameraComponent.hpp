#ifndef CAMERACOMPONENT_HPP
#define CAMERACOMPONENT_HPP
#include "Pch.hpp"
#include "glm/glm.hpp"
class CameraComponent {
public:
	// orientation vectors
	glm::vec3 lookat;			// camera lookat orientation vector 
	glm::vec3 up;				// camera up orientation vector 
	glm::vec3 right;			// camera right orientation vector 
	glm::vec3 wup;				// world up orientation vector 
	glm::mat4 projmat;			// projection matrix
	glm::mat4 viewmat;			// view matrix
	float zoom;					// zoom factor [0,1]
	float sensitivity;			// movement responsiveness [0,1]
	float xrot;					// pitch
	float yrot;					// yaw
	float speed;				// speed
	int x;						// top left x 
	int y;						// top left y
	int width;					// viewport width
	int height;					// viewport height
	bool activated;				// is camera currently active
	glm::vec4 clearcolor;		// camera clear color 
};

// CAMERA COMPONENT SERDE
inline void to_json(ordered_json& j, const CameraComponent& x) {
	to_json(j["lookat"], x.lookat);
	to_json(j["up"], x.up);
	to_json(j["right"], x.right);
	to_json(j["wup"], x.wup);
	to_json(j["projmat"], x.projmat);
	to_json(j["viewmat"], x.viewmat);
	to_json(j["zoom"], x.zoom);
	to_json(j["sensitivity"], x.sensitivity);
	to_json(j["xrot"], x.xrot);
	to_json(j["yrot"], x.yrot);
	to_json(j["speed"], x.speed);
	to_json(j["x"], x.x);
	to_json(j["y"], x.y);
	to_json(j["width"], x.width);
	to_json(j["height"], x.height);
	to_json(j["activated"], x.activated);
	to_json(j["clearcolor"], x.clearcolor);
}

inline void from_json(const ordered_json& j, CameraComponent& x) {
	from_json(j["lookat"], x.lookat);
	from_json(j["up"], x.up);
	from_json(j["right"], x.right);
	from_json(j["wup"], x.wup);
	from_json(j["projmat"], x.projmat);
	from_json(j["viewmat"], x.viewmat);
	from_json(j["zoom"], x.zoom);
	from_json(j["sensitivity"], x.sensitivity);
	from_json(j["xrot"], x.xrot);
	from_json(j["yrot"], x.yrot);
	from_json(j["speed"], x.speed);
	from_json(j["x"], x.x);
	from_json(j["y"], x.y);
	from_json(j["width"], x.width);
	from_json(j["height"], x.height);
	from_json(j["activated"], x.activated);
	from_json(j["clearcolor"], x.clearcolor);
}


#endif // !CAMERACOMPONENT_HPP
