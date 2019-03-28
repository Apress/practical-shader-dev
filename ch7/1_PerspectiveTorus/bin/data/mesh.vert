#version 410

layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;

uniform mat4 mvp; 

out vec2 fragUV;

void main()
{
	fragUV = uv;
	gl_Position = mvp * vec4(pos, 1.0);
}