#ifndef TYPES_HPP
#define TYPES_HPP

#include "Pch.hpp"

// using 
using json = nlohmann::json;
using string = std::string;

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
	EP_TOTAL
};

typedef struct LMVec2 {
	float x;
	float y;
}LMVec2;

typedef struct LMVec3 {
	float x;
	float y;
	float z;
}LMVec3;

typedef struct LMVec4 {
	float x;
	float y;
	float z;
	float w;
}LMVec4;



#endif