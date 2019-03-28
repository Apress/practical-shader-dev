#version 410

uniform vec3 lightCol;
uniform vec3 lightConeDir;
uniform vec3 lightPos;
uniform float lightCutoff; 
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

void main(){	
	vec3 nrm = texture(normTex, fragUV).rgb;
	nrm = normalize(nrm * 2.0 - 1.0);   
	nrm = normalize(TBN * nrm); 
	vec3 viewDir = normalize( cameraPos - fragWorldPos); 

	vec3 envSample = texture(envMap, reflect(-viewDir, nrm)).xyz;
	vec3 sceneLight = mix(lightCol, envSample + lightCol * 0.5, 0.5);	

	vec3 toLight = lightPos - fragWorldPos; 
	vec3 lightDir = normalize(toLight);
	float angle = dot(lightConeDir, -lightDir);
	float falloff = 0.0;
	if (angle > lightCutoff)
	{
		falloff = 1.0;
	}

	float diffAmt = diffuse(lightDir, nrm) * falloff;
	float specAmt = specular(lightDir, viewDir, nrm, 4.0) * falloff;

	vec3 diffCol = texture(diffuseTex, fragUV).xyz * sceneLight * diffAmt;

	float specMask = texture(specTex, fragUV).x;
	vec3 specCol = specMask * sceneLight * specAmt;
	
	outCol = vec4(diffCol + specCol + ambientCol, 1.0);

}
