#version 410

uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 cameraPos;
uniform vec3 ambientCol;
uniform sampler2D diffuseTex;
uniform sampler2D specTex;
uniform sampler2D normTex;
uniform samplerCube envMap;
in vec3 fragNrm;
in vec3 fragWorldPos;
in vec2 fragUV;
in mat3 TBN;

out vec4 outCol;

void main()
{
	//vec3 nrm = normalize(fragNrm);


	vec3 nrm = texture(normTex, fragUV).rgb;
	nrm = normalize(nrm * 2.0 - 1.0);   
	nrm = normalize(TBN * nrm); 


	vec3 viewDir = normalize( cameraPos - fragWorldPos); 	
	vec3 halfVec = normalize(viewDir + lightDir);

	float diffAmt = max(0.0, dot(nrm, lightDir));
	vec3 diffCol = texture(diffuseTex, fragUV).xyz * lightCol * diffAmt;

	float specAmt = max(0.0, dot(halfVec, nrm));
	float specBright = pow(specAmt, 4.0);
	vec3 specCol = texture(specTex, fragUV).x * lightCol * specBright;

	outCol = vec4(diffCol + specCol + ambientCol, 1.0);
}
