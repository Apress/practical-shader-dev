#include "ofApp.h"

glm::vec3 getLightDirection(DirectionalLight& l) {
	return glm::normalize(l.direction * -1.0f);
}

glm::vec3 getLightColor(DirectionalLight& l) {
	return l.color * l.intensity;
}


//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex();
	ofEnableDepthTest();

	torusMesh.load("torus.ply");
	phongShader.load("lit_mesh.vert", "blinnphong.frag");

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	using namespace glm;
	DirectionalLight dirLight;

	cam.pos = vec3(0, 0.75f, 1.0f);
	cam.fov = radians(90.0f);

	float cAngle = radians(-45.0f);
	vec3 right = vec3(1, 0, 0);
	mat4 view = inverse(translate(cam.pos) * rotate(cAngle, right));
	mat4 model = rotate(radians(90.0f), right) * scale(vec3(0.5, 0.5, 0.5));
	mat3 normalMatrix = (transpose(inverse(mat3(model))));

	float aspect = 1024.0f / 768.0f;
	mat4 proj = perspective(cam.fov, aspect, 0.01f, 10.0f);
	mat4 mvp = proj * view * model;

	dirLight.direction = normalize(vec3(1, -1, 0));
	dirLight.color = vec3(1, 1, 1);
	dirLight.intensity = 1.0f;

	phongShader.begin();
	phongShader.setUniformMatrix4f("mvp", mvp);
	phongShader.setUniformMatrix4f("model", model);
	phongShader.setUniform3f("cameraPos", cam.pos);
	phongShader.setUniform3f("meshSpecCol", glm::vec3(1, 1, 1));
	phongShader.setUniform3f("meshCol", glm::vec3(1.0, 0.0, 0.0));
	phongShader.setUniform3f("lightDir", getLightDirection(dirLight));
	phongShader.setUniform3f("lightCol", getLightColor(dirLight));
	phongShader.setUniformMatrix3f("normal", normalMatrix);
	phongShader.setUniform3f("ambientCol", glm::vec3(0.0, 0.0, 0.0));
	torusMesh.draw();
	phongShader.end();
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
