#ifndef TAGCOMPONENT_HPP
#define TAGCOMPONENT_HPP
#include "Pch.hpp"
class TagComponent {
public:
	string tag;
};
// TAG COMPONENT SERDE
inline void to_json(ordered_json& j, const TagComponent& x) {
	to_json(j["tag"], x.tag);
}


inline void from_json(const ordered_json& j, TagComponent& x) {
	from_json(j["tag"], x.tag);
}

#endif // !TAGCOMPONENT_HPP