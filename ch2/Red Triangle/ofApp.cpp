#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	triangle.addVertex(glm::vec3(-1.0f, 1.0f, 0.0f));
	triangle.addVertex(glm::vec3(-1.0f, -1.0f, 0.0f));
	triangle.addVertex(glm::vec3(1.0f, -1.0f, 0.0));

	shader.load("first_vertex.vert", "first_fragment.frag");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	shader.begin();
	triangle.draw();
	shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	glm::vec3 curPos = triangle.getVertex(2);
	triangle.setVertex(2, curPos + glm::vec3(0, 0.1, 0));

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
