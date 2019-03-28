#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofEnableDepthTest();

	cam.pos = glm::vec3(0, 0.85f, 1.0f);
	cam.fov = glm::radians(90.0f);

	blinnphongShader.load("lit_mesh.vert", "blinnPhongTextures.frag");
	shieldMesh.load("shield.ply");
	diffuseTex.load("shield_diffuse.png");
	specTex.load("shield_spec.png");
}

glm::vec3 getLightDirection(DirectionalLight& l)
{
	return glm::normalize(l.direction * -1.0f);
}

glm::vec3 getLightColor(DirectionalLight& l)
{
	return l.color * l.intensity;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
	using namespace glm;

	DirectionalLight dirLight;
	dirLight.direction = glm::normalize(glm::vec3(0.5, -1, -0.5));
	dirLight.color = glm::vec3(1, 1, 1);
	dirLight.intensity = 1.0f;

	mat4 proj = perspective(cam.fov, 1024.0f / 768.0f, 0.01f, 10.0f);

	//building the view matrix - camera rotated to look down at mesh
	float cAngle = radians(-45.0f);
	vec3 right = vec3(1, 0, 0);
	mat4 view = inverse(translate(cam.pos) *  rotate(cAngle, right));

	//building model matrix - rotating to point mesh upwards, and scaling larger
	static float rotAngle = 0.0f;
	rotAngle += 0.01f;
	vec3 up = vec3(0, 1, 0);
	mat4 rotation = rotate(radians(-45.0f), right) * rotate(rotAngle, up);
	mat4 model = rotation * scale(vec3(1.5, 1.5, 1.5));

	mat4 mvp = proj * view * model;
	mat3 normalMatrix = mat3(transpose(inverse(model)));

	blinnphongShader.begin();
	blinnphongShader.setUniformMatrix4f("mvp", mvp);
	blinnphongShader.setUniformMatrix4f("model", model);
	blinnphongShader.setUniformMatrix3f("normal", normalMatrix);
	blinnphongShader.setUniform3f("meshCol", glm::vec3(1, 0, 0));
	blinnphongShader.setUniform3f("meshSpecCol", glm::vec3(1, 1, 1));
	blinnphongShader.setUniformTexture("diffuseTex", diffuseTex, 0);
	blinnphongShader.setUniformTexture("specTex", specTex, 1);
	blinnphongShader.setUniform3f("ambientCol", glm::vec3(0.2, 0.2, 0.2));
	blinnphongShader.setUniform3f("lightDir", getLightDirection(dirLight));
	blinnphongShader.setUniform3f("lightCol", getLightColor(dirLight));
	blinnphongShader.setUniform3f("cameraPos", cam.pos);
	shieldMesh.draw();
	blinnphongShader.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
