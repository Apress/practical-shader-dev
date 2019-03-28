#pragma once

#include "ofMain.h"

struct CameraData {
	glm::vec3 position;
	float rotation;
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

	ofShader cloudShader;
	ofShader alphaTestShader;
	ofShader spritesheetShader;

	ofMesh charMesh;
	ofMesh backgroundMesh;
	ofMesh cloudMesh;

	ofImage alienImg;
	ofImage backgroundImg;
	ofImage cloudImg;

	bool walkRight;
	glm::vec3 charPos;

	CameraData cam;
};
