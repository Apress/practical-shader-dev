#version 410

uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 cameraPos;
uniform vec3 ambientCol;
uniform sampler2D diffuseTex;
uniform sampler2D specTex;

in vec3 fragNrm;
in vec3 fragWorldPos;
in vec2 fragUV;

out vec4 outCol;

void main()
{
	vec3 nrm = normalize(fragNrm);
	vec3 viewDir = normalize( cameraPos - fragWorldPos); 	
	vec3 halfVec = normalize(viewDir + lightDir);

	float diffAmt = max(0.0, dot(nrm, lightDir));
	vec3 meshCol = texture(diffuseTex, fragUV).xyz;
	vec3 diffCol = meshCol * lightCol * diffAmt;

	float specAmt = max(0.0, dot(halfVec, nrm));
	float specBright = pow(specAmt, 4.0);
	vec3 specCol = texture(specTex, fragUV).x * lightCol * specBright;
	vec3 ambient = ambientCol * meshCol;

	outCol = vec4(diffCol + specCol + ambient, 1.0);
}
