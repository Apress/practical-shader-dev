#version 410

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 tan;
layout (location = 2) in vec3 nrm;
layout (location = 3) in vec2 uv;

uniform mat4 mvp; 
uniform mat4 model;
uniform mat3 normal;


out vec3 fragNrm;
out vec3 fragWorldPos;
out mat3 TBN;

out vec2 fragUV;
out vec2 fragUV2;
uniform float time;

void main()
{
	float t = time * 0.05;
	float t2 = time * 0.02;
	fragUV = uv * 4.0;
//	fragUV = vec2(uv.x+t, uv.y) * 3.0f;
	fragUV2 = vec2(uv.x+t2, uv.y-t2) * 2.0 ;

	fragNrm = normal * nrm;
	fragWorldPos = (model * vec4(pos, 1.0)).xyz;

	vec3 T = normalize(normal * tan.xyz);
	vec3 B = normalize(normal * cross(tan.xyz,nrm.xyz));
	vec3 N = normalize(normal * nrm.xyz);
	TBN = mat3(T, B, N);
	gl_Position = mvp * vec4(pos, 1.0);

}