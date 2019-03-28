#version 410

layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;

uniform vec3 translation;
uniform float rotation;
uniform vec3 scale;

out vec2 fragUV;

void main()
{
	vec3 scaled = pos * scale; 

	vec3 rotated;
	rotated.x = (cos(rotation)*scaled.x)-(sin(rotation)*scaled.y);
	rotated.y = (cos(rotation)*scaled.y)+(sin(rotation)*scaled.x);

	gl_Position = vec4( rotated + translation , 1.0);

	fragUV = vec2(uv.x, 1.0-uv.y);
}
