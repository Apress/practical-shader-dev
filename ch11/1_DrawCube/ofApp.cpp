#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofEnableDepthTest();

	cubeMesh.load("cube.ply");
	cubemapShader.load("cubemap.vert", "cubemap.frag");

	cubemap.load(	"cube_front.jpg", "cube_back.jpg", 
					"cube_right.jpg", "cube_left.jpg", 
					"cube_top.jpg", "cube_bottom.jpg");

	cam.pos = glm::vec3(0, 0.75f, 1.0f);
	cam.fov = glm::radians(90.0f);

}

void ofApp::drawCube(glm::mat4& proj, glm::mat4& view)
{
	using namespace glm;

	static float rotAngle = 0.0;
	rotAngle += 0.2f;

	mat4 r = rotate(radians(rotAngle), vec3(0, 1, 0));
	mat4 s = scale(vec3(0.4, 0.4, 0.4));
	mat4 model = translate(vec3(0.0, 0.75, 0.0f)) * r *s;
	mat4 mvp = proj * view * model;

	ofShader& shd = cubemapShader;

	shd.begin();
	shd.setUniformMatrix4f("mvp", mvp);
	shd.setUniformTexture("envMap", cubemap.getTexture(), 0);
	shd.setUniform3f("cameraPos", cam.pos);
	cubeMesh.draw();
	shd.end();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
	using namespace glm;

	DirectionalLight dirLight;
	dirLight.direction = glm::normalize(glm::vec3(0.5, -1, -1));
	dirLight.color = glm::vec3(1, 1, 1);
	dirLight.intensity = 1.0f;

	DirectionalLight waterLight;
	waterLight.direction = glm::normalize(glm::vec3(0.5, -1, 1));
	waterLight.color = glm::vec3(1, 1, 1);
	waterLight.intensity = 1.0f;

	mat4 proj = perspective(cam.fov, 1024.0f / 768.0f, 0.01f, 10.0f);

	cam.pos = glm::vec3(0, 0.75f, 1.0);
	
	mat4 rotation = mat4();// rotate(glm::radians(camRot), vec3(0, 1, 0));
	mat4 view = inverse(translate(cam.pos) * rotation);


	drawCube(proj, view);

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
