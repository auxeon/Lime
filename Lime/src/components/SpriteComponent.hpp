#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP
#include "Pch.hpp"
#include "glad/glad.h"
class SpriteComponent {
public:
	string sprite;
	GLuint texid;
	bool animated;
	float duration;
	unsigned int rows;
	unsigned int cols;
};
// SPRITE COMPONENT SERDE
inline void to_json(ordered_json& j, const SpriteComponent& x) {
	to_json(j["sprite"],x.sprite);
	to_json(j["texid"],x.texid);
	to_json(j["animated"],x.animated);
	to_json(j["duration"], x.duration);
	to_json(j["rows"], x.rows);
	to_json(j["cols"], x.cols);
}


inline void from_json(const ordered_json& j, SpriteComponent& x) {
	from_json(j["sprite"], x.sprite);
	from_json(j["texid"], x.texid);
	from_json(j["animated"], x.animated);
	from_json(j["duration"], x.duration);
	from_json(j["rows"], x.rows);
	from_json(j["cols"], x.cols);
}

#endif // !SPRITECOMPONENT_HPP