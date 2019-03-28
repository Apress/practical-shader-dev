#pragma once

#include "ofMain.h"
#include "ofxEasyCubemap.h"

struct CameraData
{
	glm::vec3 pos;
	float fov;
};

struct SpotLight
{
	glm::vec3 position;
	glm::vec3 direction;
	float cutoff;

	glm::vec3 color;
	float intensity;
};



class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void drawWater(SpotLight& pointLight, glm::mat4& proj, glm::mat4& view);
	void drawShield(SpotLight& pointLight, glm::mat4& proj, glm::mat4& view);
	void drawSkybox(SpotLight& pointLight, glm::mat4& proj, glm::mat4& view);

	ofMesh shieldMesh;
	ofMesh planeMesh;
	ofMesh cubeMesh;

	ofImage waterNrm;
	ofImage diffuseTex;
	ofImage nrmTex;
	ofImage specTex;
	ofShader blinnPhong;
	ofShader waterShader;
	ofShader skyboxShader;
	CameraData cam;
	ofxEasyCubemap cubemap;

};
