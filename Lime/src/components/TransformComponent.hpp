#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP
#include "Pch.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
class TransformComponent {
public:
	glm::vec3 position;
    glm::vec3 rotation;
	glm::vec3 size;
    glm::mat4 model;
};


// TRANSFORM COMPONENT SERDE
inline void to_json(ordered_json& j, const TransformComponent& x) {
    to_json(j["position"], x.position);
    to_json(j["rotatition"], x.rotation);
    to_json(j["size"], x.size);
}

inline void from_json(const ordered_json& j, TransformComponent& x) {
    from_json(j["position"], x.position);
    from_json(j["rotation"], x.rotation);
    from_json(j["size"], x.size);
    x.model = glm::mat4(1.0);
}

#endif