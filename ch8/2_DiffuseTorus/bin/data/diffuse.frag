#version 410

uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 meshCol;

in vec3 fragNrm;
out vec4 outCol;

void main(){
	vec3 normal = normalize(fragNrm);
	float lightAmt = dot(normal, lightDir);
	vec3 fragLight = lightCol * lightAmt; 

	outCol = vec4(meshCol * fragLight, 1.0);
}
