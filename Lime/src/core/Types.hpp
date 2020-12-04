#ifndef TYPES_HPP
#define TYPES_HPP

#include "Pch.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "SDL_scancode.h"
#include "utils/LimeEnums.hpp"



// converters
// rgba(0,0,0,0) - rgba(255,255,255,255)
inline glm::vec4 rgba255(unsigned int r = 0, unsigned int g = 0, unsigned int b = 0, unsigned int a = 255) {
	glm::vec4 colors;
	r = std::min(r, 255U);
	g = std::min(g, 255U);
	b = std::min(b, 255U);
	a = std::min(a, 255U);

	colors.x = (float)r / 255;
	colors.y = (float)g / 255;
	colors.z = (float)b / 255;
	colors.w = (float)a / 255;

	return colors;
}

// colors
#define COLORS_EMERALD rgba255(39, 174, 96, 255)
#define COLORS_WHITE rgba255(255,255,255,255)
#define COLORS_BLACK rgba255(0,0,0,255)


// defines
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define FPS 120
#define MAX_TITLE_LEN 80


// angles 
#define PI 3.14159265359f
#define RAD2DEG(x) 180.0f/PI*(x)
#define DEG2RAD(x) PI/180.0f*(x)

// using 
using ordered_json = nlohmann::ordered_json;
using string = std::string;
using ordered_json = nlohmann::ordered_json;

// ECS
using ResourceID = std::uint32_t;
using EntityID = std::uint32_t;
const EntityID MAX_ENTITIES = 10000;
using ComponentID = std::uint8_t;
const ComponentID MAX_COMPONENTS = 32;
using Archetype = std::bitset<MAX_COMPONENTS>;

enum mouseButtons {
	LB,
	MB,
	RB,
	TOTAL
};

enum EventID {
	// WINDOW
	E_WINDOW_QUIT,
	E_WINDOW_RESIZED,
		P_WINDOW_RESIZED_WIDTH,
		P_WINDOW_RESIZED_HEIGHT,
	// KEYBOARD
	E_WINDOW_KEY_PRESSED,
		P_WINDOW_KEY_PRESSED_KEYCODE,
	E_WINDOW_KEY_RELEASED,
		P_WINDOW_KEY_RELEASED_KEYCODE,
	E_WINDOW_KEY_TRIGGERED,
		P_WINDOW_KEY_TRIGGERED_KEYCODE,
	// MOUSE
	E_WINDOW_MOUSE_MOVE,
		P_WINDOW_MOUSE_MOVE_X,
		P_WINDOW_MOUSE_MOVE_Y,
	E_WINDOW_MOUSE_DOWN,
		P_WINDOW_MOUSE_DOWN_BUTTON,
		P_WINDOW_MOUSE_DOWN_X,
		P_WINDOW_MOUSE_DOWN_Y,
	E_WINDOW_MOUSE_UP,
		P_WINDOW_MOUSE_UP_BUTTON,
		P_WINDOW_MOUSE_UP_X,
		P_WINDOW_MOUSE_UP_Y,
	// GRAPHICS
	E_GRAPHICS_DEBUG_TOGGLE,
	// CAMERA
	E_GRAPHICS_CAMERA_UPDATED,
		P_GRAPHICS_CAMERA_UPDATED_ENTITYID,
	// BROADCAST
	E_BROADCAST_EVENT,
		P_BROADCAST_EVENT_DATA,
	// TIMED EVENTS
	E_TIMED_EVENT,
		P_TIMED_EVENT_TIME_START,
		P_TIMED_EVENT_TIME_EXEC,
		P_TIMED_EVENT_DATA,
	// DIRECTMESSAGE EVENTS
	E_DM_EVENT,
		P_DM_EVENT_ENTITYID,
		P_DM_EVENT_DATA,
	EP_TOTAL
};

enum PlayerStates {
	PS_IDLE,
	PS_RUN,
	PS_JUMP,
	PS_GLIDE,
	PS_GROUND,
	PS_TOTAL
};

enum CameraMovements {
	CM_FORWARD,
	CM_BACKWARD,
	CM_LEFT,
	CM_RIGHT,
	CM_UP,
	CM_DOWN,
	CM_TOTAL
};


enum ShapeID {
	SH_AABB,
	SH_CIRCLE,
	SH_OBB,
	SH_POLYGON,
	SH_TOTAL
};

// define all the different resource container classes here
// including audio
class Image {
public:
	string filename;
	unsigned char* imagedata;
	int w = -1; // width
	int h = -1; // height
	int ch = -1; // channels
};



class Gridnode {
public:
	int data;
};

class Grid {
public:
	string filename;
	int rows;
	int cols;
	int tilesize;
	std::vector<std::vector<Gridnode>> cells;
};


//// SERDE FOR BASIC TYPES
////////////////////////////////// INT
inline void to_json(ordered_json& j, const int& x) {
	j = x ;
}

inline void from_json(const ordered_json& j, int& x) {
	x = j.get<int>();
}
/////////////////////////////////

///////////////////////////////// UNSIGNED INT
inline void to_json(ordered_json& j, const unsigned int& x) {
	j = x ;
}

inline void from_json(const ordered_json& j, unsigned int& x) {
	x = j.get<unsigned int>();
}
/////////////////////////////////

///////////////////////////////// FLOAT
inline void to_json(ordered_json& j, const float& x) {
	j = x;
}

inline void from_json(const ordered_json& j, float& x) {
	x = j.get<float>();
}
/////////////////////////////////

///////////////////////////////// STRING
inline void to_json(ordered_json& j, const string& x) {
	j = x.c_str();
}

inline void from_json(const ordered_json& j, string& x) {
	x = j.get<string>();
}
/////////////////////////////////

///////////////////////////////// BOOL
inline void to_json(ordered_json& j, const bool& x) {
	j = x;
}

inline void from_json(const ordered_json& j, bool& x) {
	x = j.get<bool>();
}
/////////////////////////////////

///////////////////////////////// VEC2
inline void to_json(ordered_json& j, const glm::vec2& x) {
	j = {
		{"x",x.x},
		{"y",x.y},
	};
}

inline void from_json(const ordered_json& j, glm::vec2& x) {
	j.at("x").get_to(x.x);
	j.at("y").get_to(x.y);
}

///////////////////////////////// VEC3
inline void to_json(ordered_json& j, const glm::vec3& x) {
	j = {
		{"x",x.x},
		{"y",x.y},
		{"z",x.z},
	};
}

inline void from_json(const ordered_json& j, glm::vec3& x) {
	j.at("x").get_to(x.x);
	j.at("y").get_to(x.y);
	j.at("z").get_to(x.z);
}

///////////////////////////////// VEC4
inline void to_json(ordered_json& j, const glm::vec4& x) {
	j = {
		{"x",x.x},
		{"y",x.y},
		{"z",x.z},
		{"w",x.w},
	};
}

inline void from_json(const ordered_json& j, glm::vec4& x) {
	j.at("x").get_to(x.x);
	j.at("y").get_to(x.y);
	j.at("z").get_to(x.z);
	j.at("w").get_to(x.w);
}

///////////////////////////////// MAT4
inline void to_json(ordered_json& j, const glm::mat4& x) {
	j = {
		{x[0][0],x[1][0],x[2][0],x[3][0]},
		{x[0][1],x[1][1],x[2][1],x[3][1]},
		{x[0][2],x[1][2],x[2][2],x[3][2]},
		{x[0][3],x[1][3],x[2][3],x[3][3]}
	};
}

inline void from_json(const ordered_json& j, glm::mat4& x) {
	for (int k = 0; k < 4; ++k) {
		for (int l = 0; l < 4; ++l) {
			j.at(k).at(l).get_to(x[k][l]);
		}
	}
}



// EXTRAS TRIALS

/////////////////////////////////// GLUINT NOT NEEDED AS TYPDEF OF UNSIGNED INT
//inline void to_json(ordered_json& j, const GLuint& x) {
//	j = ordered_json{ x };
//}
//
//inline void from_json(const ordered_json& j, GLuint& x) {
//	j.at(0).get_to(x);
//}
///////////////////////////////////

/////////////////////////////////// SDL_SCANCODE ENUMS NOT NEEDED AS JSONSERIALIZE ENUM MACRO IS THERE 
//inline void to_json(ordered_json& j, const SDL_Scancode& x) {
//	j = LIMEENUMS_SDL_SCANCODES::gEnumInt2Str[x];
//}
//
//inline void from_json(const ordered_json& j, SDL_Scancode& x) {
//	auto str = j.get<string>();
//	x = (SDL_Scancode)LIMEENUMS_SDL_SCANCODES::gEnumStr2Int[str.c_str()];
//}
/////////////////////////////////// PLAYERSTATES ENUMS NOT NEEDED AS JSONSERIALIZE ENUM MACRO IS THERE 
//inline void to_json(ordered_json& j, const PlayerStates& x) {
//	j = LIMEENUMS_PLAYERSTATES::gEnumInt2Str[x];
//}
//
//inline void from_json(const ordered_json& j, PlayerStates& x) {
//	auto str = j.get<string>();
//	x = (PlayerStates)LIMEENUMS_PLAYERSTATES::gEnumStr2Int[str.c_str()];
//}
///////////////////////////////////


//// INT
//inline void to_json(ordered_json& j, const) {
//
//}
//
//inline void from_json(const ordered_json& j, ) {
//
//}
//
//// INT
//inline void to_json(ordered_json& j, const) {
//
//}
//
//inline void from_json(const ordered_json& j, ) {
//
//}
//
//// INT
//inline void to_json(ordered_json& j, const) {
//
//}
//
//inline void from_json(const ordered_json& j, ) {
//
//}
//
//// INT
//inline void to_json(ordered_json& j, const) {
//
//}
//
//inline void from_json(const ordered_json& j, ) {
//
//}
//
//// INT
//inline void to_json(ordered_json& j, const) {
//
//}
//
//inline void from_json(const ordered_json& j, ) {
//
//}
//
//// INT
//inline void to_json(ordered_json& j, const) {
//
//}
//
//inline void from_json(const ordered_json& j, ) {
//
//}
//
//// INT
//inline void to_json(ordered_json& j, const) {
//
//}
//
//inline void from_json(const ordered_json& j, ) {
//
//}
//
//// INT
//inline void to_json(ordered_json& j, const) {
//
//}
//
//inline void from_json(const ordered_json& j, ) {
//
//}
//
//// INT
//inline void to_json(ordered_json& j, const) {
//
//}
//
//inline void from_json(const ordered_json& j, ) {
//
//}
//
//// INT
//inline void to_json(ordered_json& j, const) {
//
//}
//
//inline void from_json(const ordered_json& j, ) {
//
//}


#endif