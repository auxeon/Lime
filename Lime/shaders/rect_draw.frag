#version 460 core
out vec4 color;
  
uniform vec4 vertexColor;

void main()
{
    color = vertexColor;
}