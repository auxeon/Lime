#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP
#include "Pch.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
class TransformComponent {
public:
	glm::vec3 position;
	glm::vec3 size;
	glm::mat4 matrix;
};


// TRANSFORM COMPONENT SERDE
inline void to_json(ordered_json& j, const TransformComponent& x) {
    to_json(j["position"], x.position);
    to_json(j["size"], x.size);
    to_json(j["matrix"], x.matrix);
}

inline void from_json(const ordered_json& j, TransformComponent& x) {
    from_json(j["position"], x.position);
    from_json(j["size"], x.size);
    from_json(j["matrix"], x.matrix);
    x.matrix = glm::translate(x.matrix, x.position);
}

#endif