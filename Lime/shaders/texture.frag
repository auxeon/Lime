#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture;

uniform int mode;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	if(mode == 0){
		FragColor = texture(texture, TexCoord);
	}
	else{
		FragColor = vec4(ourColor,1.0);
	}
}