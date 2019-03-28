#version 410
uniform sampler2D greenMan;
in vec2 fragUV;

out vec4 outCol;

void main()
{
	outCol = texture(greenMan, fragUV);
	if (outCol.a < 1.0) discard;
}
