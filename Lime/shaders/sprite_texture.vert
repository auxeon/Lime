#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 FlatColor;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;


void main()
{
	gl_Position = projection * view * transform * vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	FlatColor = aColor;
}