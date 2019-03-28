#version 410
layout (location = 0) in vec3 pos;
layout (location = 2) in vec3 nrm;

uniform mat4 mvp; 
uniform mat3 normal;

out vec3 fragNrm;

void main(){
	gl_Position = mvp * vec4(pos, 1.0);
	fragNrm = (normal * nrm).xyz;
}
