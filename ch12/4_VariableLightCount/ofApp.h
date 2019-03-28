#pragma once

#include "ofMain.h"
#include "ofxEasyCubemap.h"
#include <vector>

struct CameraData
{
	glm::vec3 pos;
	float fov;
};

struct Light
{
	virtual bool isPointLight() { return false; }
	virtual void apply(ofShader& shd) {};
};

struct DirectionalLight : public Light
{
	glm::vec3 direction;
	glm::vec3 color;
	float intensity;

	virtual void apply(ofShader& shd) override
	{
		shd.setUniform3f("lightDir", -direction);
		shd.setUniform3f("lightCol", color * intensity);
	}
};

struct PointLight : public Light
{
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	float radius;

	virtual bool isPointLight() override { return true; }
	virtual void apply(ofShader& shd) override
	{
		shd.setUniform3f("lightPos", position);
		shd.setUniform3f("lightCol", color * intensity);
		shd.setUniform1f("lightRadius", radius);
	}
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

	void drawWater(Light& light, glm::mat4& proj, glm::mat4& view);
	void drawShield(Light& light, glm::mat4& proj, glm::mat4& view);
	void drawSkybox(glm::mat4& proj, glm::mat4& view);
	void beginRenderingPointLights();
	void endRenderingPointLights();

	void onFrameStart(ofEventArgs& arg);
	void onFrameEnd(ofEventArgs& args);

	ofMesh shieldMesh;
	ofMesh planeMesh;
	ofMesh cubeMesh;

	ofImage waterNrm;
	ofImage diffuseTex;
	ofImage nrmTex;
	ofImage specTex;

	ofShader skyboxShader;

	CameraData cam;
	ofxEasyCubemap cubemap;

	ofShader dirLightShaders[2];
	ofShader pointLightShaders[2];

	DirectionalLight dirLight;
	std::vector<PointLight> pointLights;

};
