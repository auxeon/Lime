#version 460 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FlatColor;

// texture samplers
uniform sampler2D texture1;

uniform int mode;

void main()
{
	if(mode == 0){
		FragColor = texture(texture1, TexCoord);
	}
	if(mode == 1){
		FragColor = vec4(FlatColor,1.0);
	}
}