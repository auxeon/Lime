#include "Pch.hpp"
#include "RenderGeometry.hpp"
#include "glm/gtx/transform.hpp"

static std::array<GLfloat, 18> vertexBuffer = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,

    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

static std::array<GLfloat, 12> texBuffer = {
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f
};

GeometryRenderer::GeometryRenderer(const Shader& shader) : shader(shader)
{
    vertexArray = std::make_unique<VertexArray>(vertexBuffer, texBuffer);
}

GeometryRenderer::~GeometryRenderer()
{
}

void GeometryRenderer::drawRect(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec4 color)
{
    shader.use();

    glm::mat4 mWorldTransform = glm::scale(glm::mat4(1.0f), glm::vec3{ size.x, size.y, 1 });
    mWorldTransform *= glm::rotate(glm::radians(rotate),glm::vec3(0.0f,0.0f,1.0f));
    mWorldTransform *= glm::translate(glm::mat4(1.0f), glm::vec3(position.x + size.x / 2, position.y, 0.0f));

    glm::mat4 model = mWorldTransform;
    shader.setMat4("model", model);
    shader.setVec4("vertexColor", color);

    vertexArray->setActive();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}