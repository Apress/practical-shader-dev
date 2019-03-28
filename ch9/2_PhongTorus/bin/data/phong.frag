#version 410

uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 meshCol;
uniform vec3 meshSpecCol;
uniform vec3 cameraPos;
uniform vec3 ambientCol;

in vec3 fragNrm;
in vec3 fragWorldPos; 
out vec4 outCol;

void main(){
	vec3 nrm = normalize(fragNrm);
	vec3 refl = normalize(reflect(-lightDir,nrm));
	vec3 viewDir = normalize( cameraPos - fragWorldPos); 

	float diffAmt = max(0.0, dot(nrm, lightDir));
	vec3 diffCol = meshCol * lightCol * diffAmt;

	float specAmt = max(0.0, dot(refl, viewDir));
	float specBright = pow(specAmt, 16.0);
	vec3 specCol = meshSpecCol * lightCol * specBright;

	vec3 ambient = ambientCol * meshCol;
	outCol = vec4(diffCol + specCol + ambient, 1.0);
}
