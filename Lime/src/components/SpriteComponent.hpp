#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP
#include "Pch.hpp"
class SpriteComponent {
public:
	string sprite;
	GLuint texid;
	bool animated;
	float duration;
	unsigned int rows;
	unsigned int cols;
};
#endif // !SPRITECOMPONENT_HPP