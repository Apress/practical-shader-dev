#version 410

uniform sampler2D parrotTex;
uniform sampler2D checkerboardTex;

in vec2 fragUV;
out vec4 outCol;

void main()
{
	vec4 parrot = texture(parrotTex, fragUV);
	vec4 checker = texture(checkerboardTex, fragUV);

	outCol = mix(checker, parrot, checker.r);
}  
