#ifndef RENDERBOXCOMPONENT_HPP
#define RENDERBOXCOMPONENT_HPP
#include "Pch.hpp"

class RenderBoxComponent {
public:
	glm::vec3 color;
};
// RENDERBOX COMPONENT SERDE
inline void to_json(ordered_json& j, const RenderBoxComponent& x) {
	to_json(j["color"], x.color);
}

inline void from_json(const ordered_json& j, RenderBoxComponent& x) {
	from_json(j["color"], x.color);
}

#endif // !RENDERCOMPONENT_HPP