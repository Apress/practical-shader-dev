#version 410

struct DirectionalLight {
	vec3 direction;
	vec3 color;
};  

struct PointLight {    
	vec3 position;
	vec3 color;
	float radius;
};  

struct SpotLight{
	vec3 position;
	vec3 direction;
	vec3 color;
	float cutoff;
};

#define NUM_DIR_LIGHTS 1
#define NUM_POINT_LIGHTS 2
#define NUM_SPOT_LIGHTS 2

uniform DirectionalLight directionalLights[NUM_DIR_LIGHTS];
uniform PointLight pointLights[NUM_POINT_LIGHTS];
uniform SpotLight spotLights[NUM_SPOT_LIGHTS];
uniform sampler2D diffuseTex;
uniform sampler2D specTex;
uniform sampler2D normTex;
uniform samplerCube envMap;
uniform vec3 cameraPos;
uniform vec3 ambientCol;

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
	vec3 viewDir = normalize( cameraPos - fragWorldPos); 	

	vec3 envSample = texture(envMap, reflect(-viewDir, nrm)).xyz;
	float specMask = texture(specTex, fragUV).x;
	vec3 finalColor = vec3(0,0,0);

	for (int i = 0; i < NUM_DIR_LIGHTS; ++i) 
	{
		DirectionalLight light = directionalLights[i];

		float diffAmt = diffuse(light.direction, nrm);
		float specAmt = specular(light.direction, viewDir, nrm, 4.0) * specMask;
	
		vec3 specCol = specMask * light.color * specAmt;
		vec3 diffCol = envSample * light.color * diffAmt;

		finalColor += diffCol;
		finalColor += specCol;
	}

	for (int i = 0; i < NUM_POINT_LIGHTS; ++i)
	{
		PointLight light = pointLights[i];

		vec3 toLight = light.position - fragWorldPos; 
		vec3 lightDir = normalize(toLight);
		float distToLight = length(toLight); 
		float falloff = 1.0 - (distToLight / light.radius);

		float diffAmt = diffuse(lightDir, nrm) * falloff;
		float specAmt = specular(lightDir, viewDir, nrm, 4.0) * specMask * falloff;
	
		vec3 specCol = specMask * light.color * specAmt;
		vec3 diffCol = envSample * light.color * diffAmt;

		finalColor += diffCol;
		finalColor += specCol;
	}

	for (int i = 0; i < NUM_SPOT_LIGHTS; ++i)
	{
		SpotLight light = spotLights[i];

		vec3 toLight = light.position - fragWorldPos; 
		vec3 lightDir = normalize(toLight);
		float angle = dot(light.direction, -lightDir);
		float falloff = (angle > light.cutoff) ? 1.0 : 0.0;

		float diffAmt = diffuse(lightDir, nrm) * falloff;
		float specAmt = specular(lightDir, viewDir, nrm, 4.0) * specMask * falloff;

		vec3 specCol = specMask * light.color * specAmt;
		vec3 diffCol = envSample * light.color * diffAmt;

		finalColor += diffCol;
		finalColor += specCol;
	}



	outCol = vec4(finalColor + ambientCol, 1.0);
}