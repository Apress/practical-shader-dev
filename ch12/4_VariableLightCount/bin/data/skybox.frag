#version 410
uniform samplerCube envMap;
in vec3 fromCam;
out vec4 outCol;

void main(){
	outCol = texture(envMap, fromCam);


	//float f = 0.0;
	//if (outCol.b > outCol.r)
//	{
	//	for (int i = 0; i < 10; ++i)
		//{
			//float ff = texture(envMap, outCol.xyz).r;
			//vec3 offset = vec3(pow(ff,ff), sin(ff), atan(ff));
			//vec3 r = texture(envMap, outCol.xyz + offset).xyz;
			//f += pow(sqrt(r.x) + sqrt(r.y) + sqrt(r.z),256);
		//}
//	}
	
	
	//outCol.r = f;
}