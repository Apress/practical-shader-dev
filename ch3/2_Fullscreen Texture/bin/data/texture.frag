#version 410

uniform sampler2D parrotTex;

in vec2 fragUV;
out vec4 outCol;

void main()
{
	outCol = texture(parrotTex, fragUV);
}
