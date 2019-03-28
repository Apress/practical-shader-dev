#version 410

uniform sampler2D parrotTex; 
uniform float brightness; 

in vec2 fragUV;
out vec4 outCol;

void main()
{
	outCol = texture(parrotTex, fragUV) * brightness;
}
