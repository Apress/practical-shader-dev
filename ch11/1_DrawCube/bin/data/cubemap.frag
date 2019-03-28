#version 410

uniform samplerCube envMap;

in vec3 fromCam;
out vec4 outCol;

void main()
{
	outCol = texture(envMap, fromCam);
}