#version 410

layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;

out vec2 fragUV;

void main()
{
	vec3 translation = vec3(-0.55, 0.0, 0.0);
	vec3 scale = vec3(0.5, 0.75, 1.0);
	gl_Position = vec4( (pos * scale) + translation, 1.0);
	fragUV = vec2(uv.x, 1.0-uv.y);
}
