#version 410

uniform vec3 lightPos; 
uniform float lightRadius;
uniform vec3 lightCol;
uniform vec3 cameraPos;
uniform vec3 ambientCol;
uniform sampler2D normTex;
uniform samplerCube envMap;

in vec3 fragNrm;
in vec3 fragWorldPos;
in vec2 fragUV;
in vec2 fragUV2;
in mat3 TBN;

out vec4 outCol;

float diffuse(vec3 lightDir, vec3 nrm)
{
	float diffAmt = max(0.0, dot(nrm, lightDir));
	return diffAmt;
}

float specular(vec3 lightDir, vec3 viewDir, vec3 nrm, float shininess)
{
	vec3 halfVec = normalize(viewDir + lightDir);
	float specAmt = max(0.0, dot(halfVec, nrm));
	return pow(specAmt, shininess);
}

void main()
{
	vec3 nrm = texture(normTex, fragUV).rgb;
	nrm = (nrm * 2.0 - 1.0);   
	
	vec3 nrm2 = texture(normTex, fragUV2).rgb;
	nrm2 = (nrm2 * 2.0 - 1.0);   
	
	nrm = normalize(TBN * (nrm + nrm2)); 

	//manual light direction calculation
	vec3 toLight = lightPos - fragWorldPos; 
	vec3 lightDir = normalize(toLight);
	float distToLight = length(toLight); 
	float falloff = 1.0 - (distToLight / lightRadius);
	vec3 viewDir = normalize( cameraPos - fragWorldPos); 	

	float diffAmt = diffuse(lightDir, nrm) * falloff; 
	float specAmt = specular(lightDir, viewDir, nrm, 512.0) * falloff; 

	vec3 diffCol = texture(envMap, (reflect(-viewDir, nrm))).xyz * lightCol * diffAmt;
	vec3 specCol = lightCol * specAmt;

	outCol = vec4(diffCol + specCol + ambientCol, 1.0); 
}
