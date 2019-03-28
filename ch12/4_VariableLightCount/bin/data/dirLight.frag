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
	vec3 nrm = texture(normTex, fragUV).rgb;
	nrm = normalize(nrm * 2.0 - 1.0);   
	nrm = normalize(TBN * nrm); 
	vec3 diffCol = vec3(0,0,0);
	vec3 specCol = vec3(0,0,0);
	vec3 viewDir = normalize( cameraPos - fragWorldPos); 	
	vec3 halfVec = normalize(viewDir + lightDir);
	
	vec3 envSample = texture(envMap, reflect(-viewDir, nrm)).xyz;
	vec3 sceneLight = mix(lightCol, envSample + lightCol * 0.5, 0.5);

	float diffAmt = max(0.0, dot(nrm, lightDir));
	diffCol += texture(diffuseTex, fragUV + nrm.xy).xyz * sceneLight * diffAmt;

	float specAmt = max(0.0, dot(halfVec, nrm));
	float specBright = pow(specAmt, 4.0);
	specCol += texture(specTex, fragUV + nrm.xy).x * sceneLight * specBright;

	outCol = vec4(diffCol + specCol + ambientCol, 1.0);

}
