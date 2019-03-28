#version 410

layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec2 size;
uniform vec2 offset;

out vec2 fragUV;

void main()
{
	gl_Position =  proj * view * model * vec4( pos, 1.0);
	fragUV = vec2(uv.x, 1.0-uv.y) * size + (offset*size);
}
