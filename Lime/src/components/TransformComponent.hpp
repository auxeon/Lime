#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP
#include "Pch.hpp"
#include "glm/glm.hpp"
class TransformComponent {
public:
	glm::vec3 position;
	glm::mat4 matrix;
};


//class drawspriteCompoent {
//
//	vertex buffer id
//	texid
//	modelmatrix 
//
//};
#endif