#ifndef SHAPES_HPP
#define SHAPES_HPP
#include "Pch.hpp"
#include "glm/glm.hpp"

class Shape {
public:
	ShapeID shapeid;

};


class AABB : public Shape{
public:
	AABB() {
		shapeid = ShapeID::SH_AABB;
		min = glm::vec2{ 0.0f,0.0f };
		max = glm::vec2{ 1.0f,1.0f };
	}
	glm::vec2 min; // bottom left
	glm::vec2 max; // top right
};

class OBB : public Shape {
public:
	OBB() {
		shapeid = ShapeID::SH_OBB;
		min = glm::vec2{ 0.0f,0.0f };
		max = glm::vec2{ 1.0f,1.0f };
		zrot = 0.0f;
	}
	glm::vec2 min; // bottom left
	glm::vec2 max; // top right
	float zrot;
};

class Circle : public Shape{
public:
	Circle() {
		shapeid = ShapeID::SH_CIRCLE;
		center = glm::vec2{ 0.0f,0.0f };
		radius = 1.0f;
	}
	glm::vec2 center;
	float radius;
};

class Polygon : public Shape {
public:
	Polygon() {
		shapeid = ShapeID::SH_POLYGON;
	}
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> normals;
};

#endif // !SHAPES_HPP
