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
};
#endif // !CAMERACOMPONENT_HPP
