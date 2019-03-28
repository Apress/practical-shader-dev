#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex();
	ofEnableDepthTest();

	torusMesh.load("torus.ply");
	uvShader.load("mesh.vert", "normal_vis.frag");

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw()
{
	using namespace glm;
	cam.pos = vec3(0, 0, 1);
	cam.fov = radians(90.0f);
	float aspect = 1024.0f / 768.0f;

	mat4 model = rotate(1.0f, vec3(1, 1, 1)) * scale(vec3(0.5, 0.5, 0.5));
	mat4 view = inverse(translate(cam.pos));
	mat4 proj = perspective(cam.fov, aspect, 0.01f, 10.0f);

	mat4 mvp = proj * view * model;

	uvShader.begin();
	uvShader.setUniformMatrix4f("mvp", mvp);
	uvShader.setUniformMatrix4f("model", model);

	torusMesh.draw();
	uvShader.end();
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
