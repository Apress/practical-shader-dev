#version 410

layout (location = 0) in vec3 pos;
layout (location = 2) in vec3 nrm;
layout (location = 3) in vec2 uv;

uniform mat4 mvp; 
uniform mat4 model;
uniform mat3 normal;

out vec3 fragNrm;
out vec3 fragWorldPos;
out vec2 fragUV;

void main()	
{

	fragUV = vec2(uv.x, 1.0-uv.y);

	gl_Position = mvp * vec4(pos, 1.0);
		fragNrm = normal * nrm;
	fragWorldPos = (model * vec4(pos, 1.0)).xyz;

}