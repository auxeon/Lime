#ifndef TYPES_HPP
#define TYPES_HPP

#include "Pch.hpp"

// using 
using json = nlohmann::json;
using string = std::string;

// ECS
using EntityID = std::uint32_t;
const EntityID MAX_ENTITIES = 10000;
using ComponentID = std::uint8_t;
const ComponentID MAX_COMPONENTS = 32;
using Archetype = std::bitset<MAX_COMPONENTS>;

// Event
using EventID = std::uint32_t;
using ParamID = std::uint32_t;

enum EventType {
	// Main Window 
	WINDOOW_QUIT,
	WINDOW_RESIZED,
	WINDOW_INPUT,
	TOTAL_EVENTS
};

#endif