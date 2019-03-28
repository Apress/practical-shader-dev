#version 410

uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 meshCol;
uniform vec3 meshSpecCol;
uniform vec3 cameraPos;

in vec3 fragNrm;
in vec3 fragWorldPos; 
out vec4 outCol;

void main(){
	vec3 nrm = normalize(fragNrm);
	vec3 refl = reflect(-lightDir,nrm);
	vec3 viewDir = normalize( cameraPos - fragWorldPos); 

	float specAmt = max(0.0, dot(refl, viewDir));
	float specBright = pow(specAmt, 16.0);

	outCol = vec4(lightCol * meshSpecCol * specBright, 1.0);
}
