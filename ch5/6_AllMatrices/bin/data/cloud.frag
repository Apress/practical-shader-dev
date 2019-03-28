#version 410
uniform sampler2D tex;
in vec2 fragUV;

out vec4 outCol;

void main()
{
	outCol = texture(tex, fragUV);
	outCol.a = min(outCol.a, 0.8);
}
