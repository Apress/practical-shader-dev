#version 410

uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 cameraPos;
uniform vec3 ambientCol;
uniform sampler2D normTex;
uniform samplerCube envMap;
in vec3 fragNrm;
in vec3 fragWorldPos;
in vec2 fragUV;

in mat3 TBN;

out vec4 outCol;

in vec2 fragUV2;
void main()
{
	vec3 nrm = texture(normTex, fragUV).rgb;
	nrm = (nrm * 2.0 - 1.0);   
	
	vec3 nrm2 = texture(normTex, fragUV2).rgb;
	nrm2 = (nrm2 * 2.0 - 1.0);   
	
	nrm = normalize(TBN * (nrm + nrm2)); 

	vec3 viewDir = normalize( cameraPos - fragWorldPos); 	
	vec3 halfVec = normalize(viewDir + lightDir);

	vec3 envSample = texture(envMap, reflect(-viewDir, nrm)).xyz;
	vec3 sceneLight = mix(lightCol, envSample + lightCol * 0.5, 0.5);


	float diffAmt = max(0.0, dot(nrm, lightDir));
	vec3 diffCol = sceneLight * diffAmt;

	float specAmt = max(0.0, dot(halfVec, nrm));
	float specBright = pow(specAmt, 512.0);
	vec3 specCol = sceneLight * specBright;

	outCol = vec4(diffCol + specCol + ambientCol, 1.0); 
}
