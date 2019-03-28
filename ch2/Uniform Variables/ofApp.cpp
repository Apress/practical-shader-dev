#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	triangle.addVertex(glm::vec3(-1.0f, 1.0f, 0.0f));
	triangle.addVertex(glm::vec3(-1.0f, -1.0f, 0.0f));
	triangle.addVertex(glm::vec3(1.0f, -1.0f, 0.0));


	triangle.addColor(ofFloatColor(1.0f, 0.0f, 0.0f, 1.0f));
	triangle.addColor(ofFloatColor(0.0f, 1.0f, 0.0f, 1.0f)); 
	triangle.addColor(ofFloatColor(0.0f, 0.0f, 1.0f, 1.0f));


	shader.load("uniform_color.vert", "uniform_color.frag");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	shader.begin();
	shader.setUniform4f("fragCol", glm::vec4(0, 1, 1, 1));

	triangle.draw();
	shader.end();
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
