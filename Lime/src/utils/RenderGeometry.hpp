#ifndef GEOMETRY_RENDERER_HPP
#define GEOMETRY_RENDERER_HPP

#include "Pch.hpp"
#include "utils/Shader.hpp"
#include "glm/glm.hpp"
#include "VertexArray.hpp"

// A renderer class able to draw OpenGL rectangles.
// It uses a specialized shader.
class GeometryRenderer
{
public:
	GeometryRenderer(const Shader& shader);
	~GeometryRenderer();

	void drawRect(glm::vec2 position,
		glm::vec2 size = glm::vec2{ 10, 10 },
		GLfloat rotate = 0.0f,
		glm::vec4 color = glm::vec4{});

private:
	Shader shader;
	std::unique_ptr<VertexArray> vertexArray;
};

#endif