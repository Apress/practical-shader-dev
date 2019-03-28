#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	quad.addVertex(glm::vec3(-1, -1, 0));
	quad.addVertex(glm::vec3(-1, 1, 0));
	quad.addVertex(glm::vec3(1, 1, 0));
	quad.addVertex(glm::vec3(1, -1, 0));

	quad.addColor(ofDefaultColorType(1, 0, 0, 1)); //red
	quad.addColor(ofDefaultColorType(0, 1, 0, 1)); //green
	quad.addColor(ofDefaultColorType(0, 0, 1, 1)); //blue
	quad.addColor(ofDefaultColorType(1, 1, 1, 1)); //white

	quad.addTexCoord(glm::vec2(0, 1));
	quad.addTexCoord(glm::vec2(0, 0));
	quad.addTexCoord(glm::vec2(1, 0));
	quad.addTexCoord(glm::vec2(1, 1));

	ofIndexType indices[6] = { 0,1,2,2,3,0 };
	quad.addIndices(indices, 6);

	shader.load("passthrough.vert", "uv_vis.frag");
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	shader.begin();
	quad.draw();
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
