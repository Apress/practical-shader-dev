#version 410

layout (location = 0) in vec3 pos;

out vec3 fromCam;
uniform mat4 mvp; 

void main()
{
	fromCam = pos;
	gl_Position =  (mvp * vec4(pos, 1.0)).xyww;

}