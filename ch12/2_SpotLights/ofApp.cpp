#include "ofApp.h"
#include <vector>

#define USE_NIGHT_SKYBOX 1

//--------------------------------------------------------------
void calcTangents(ofMesh& mesh)
{
	using namespace glm;
	std::vector<vec4> tangents;
	tangents.resize(mesh.getNumVertices());

	uint indexCount = mesh.getNumIndices();

	const vec3* vertices = mesh.getVerticesPointer();
	const vec2* uvs = mesh.getTexCoordsPointer();
	const uint* indices = mesh.getIndexPointer();

	for (uint i = 0; i < indexCount - 2; i += 3)
	{
		const vec3& v0 = vertices[indices[i]];
		const vec3& v1 = vertices[indices[i + 1]];
		const vec3& v2 = vertices[indices[i + 2]];
		const vec2& uv0 = uvs[indices[i]];
		const vec2& uv1 = uvs[indices[i + 1]];
		const vec2& uv2 = uvs[indices[i + 2]];

		vec3 edge1 = v1 - v0;
		vec3 edge2 = v2 - v0;
		vec2 dUV1 = uv1 - uv0;
		vec2 dUV2 = uv2 - uv0;

		float f = 1.0f / (dUV1.x * dUV2.y - dUV2.x * dUV1.y);

		vec4 tan;
		tan.x = f * (dUV2.y * edge1.x - dUV1.y * edge2.x);
		tan.y = f * (dUV2.y * edge1.y - dUV1.y * edge2.y);
		tan.z = f * (dUV2.y * edge1.z - dUV1.y * edge2.z);
		tan.w = 0;
		tan = normalize(tan);

		tangents[indices[i]] += (tan);
		tangents[indices[i + 1]] += (tan);
		tangents[indices[i + 2]] += (tan);
	}

	int numColors = mesh.getNumColors();

	for (int i = 0; i < tangents.size(); ++i)
	{
		vec3 t = normalize(tangents[i]);
		if (i >= numColors)
		{
			mesh.addColor(ofFloatColor(t.x, t.y, t.z, 0.0));
		}
		else
		{
			mesh.setColor(i, ofFloatColor(t.x, t.y, t.z, 0.0));
		}
	}
}

void ofApp::setup() {
	ofDisableArbTex();
	ofEnableDepthTest();

	planeMesh.load("plane.ply");
	shieldMesh.load("shield.ply");
	cubeMesh.load("cube.ply");

	blinnPhong.load("mesh.vert", "spotLight.frag");
	waterShader.load("water.vert", "spotLightWater.frag");;

	diffuseTex.load("shield_diffuse.png");
	specTex.load("shield_spec.png");
	nrmTex.load("shield_normal.png");
	waterNrm.load("water_nrm.png");

	waterNrm.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);

#if USE_NIGHT_SKYBOX
	cubemap.load("night_front.jpg", "night_back.jpg",
		"night_right.jpg", "night_left.jpg",
		"night_top.jpg", "night_bottom.jpg");

#else
	cubemap.load("cube_front.jpg", "cube_back.jpg",
		"cube_right.jpg", "cube_left.jpg",
		"cube_top.jpg", "cube_bottom.jpg");
#endif


	cam.pos = glm::vec3(0, 0.75f, 1.0f);
	cam.fov = glm::radians(90.0f);

	calcTangents(shieldMesh);
	calcTangents(planeMesh);


	skyboxShader.load("skybox.vert", "skybox.frag");

}

glm::vec3 getLightColor(SpotLight& l)
{
	return l.color * l.intensity;
}

//--------------------------------------------------------------
void ofApp::update() {

}

void ofApp::drawWater(SpotLight& pointLight, glm::mat4& proj, glm::mat4& view)
{
	using namespace glm;

	static float t = 0.0f;
	t += ofGetLastFrameTime();

	vec3 right = vec3(1, 0, 0);
	mat4 rotation = rotate(radians(-90.0f), right);
	mat4 model = rotation * scale(vec3(10.0, 10.0, 10.0));
	mat4 mvp = proj * view * model;
	mat3 normalMatrix = mat3(transpose(inverse(model)));

	ofShader& shd = waterShader;;
	shd.begin();
	shd.setUniformMatrix4f("mvp", mvp);
	shd.setUniformMatrix4f("model", model);
	shd.setUniformMatrix3f("normal", normalMatrix);
	shd.setUniform3f("meshSpecCol", glm::vec3(1, 1, 1));
	shd.setUniformTexture("normTex", waterNrm, 0);;
	shd.setUniformTexture("envMap", cubemap.getTexture(), 1);
	shd.setUniform1f("time", t);

	shd.setUniform3f("ambientCol", glm::vec3(0.0, 0.0, 0.0));
	shd.setUniform3f("lightPos", pointLight.position);
	shd.setUniform1f("lightCutoff", pointLight.cutoff);
	shd.setUniform3f("lightConeDir", pointLight.direction);
	shd.setUniform3f("lightCol", getLightColor(pointLight));
	shd.setUniform3f("cameraPos", cam.pos);
	planeMesh.draw();
	shd.end();
}


void ofApp::drawSkybox(SpotLight& pointLight, glm::mat4& proj, glm::mat4& view)
{
	using namespace glm;

	mat4 model = translate(cam.pos);
	mat4 mvp = proj * view * model;

	ofShader& shd = skyboxShader;
	glDepthFunc(GL_LEQUAL);
	shd.begin();
	shd.setUniformMatrix4f("mvp", mvp);
	shd.setUniformTexture("envMap", cubemap.getTexture(), 0);
	cubeMesh.draw();
	shd.end();
	glDepthFunc(GL_LESS);
}

void ofApp::drawShield(SpotLight& pointLight, glm::mat4& proj, glm::mat4& view)
{
	using namespace glm;

	mat4 model = translate(vec3(0.0, 0.75, 0.0f));
	mat4 mvp = proj * view * model;
	mat3 normalMatrix = mat3(transpose(inverse(model)));

	ofShader& shd = blinnPhong;

	shd.begin();
	shd.setUniformMatrix4f("mvp", mvp);
	shd.setUniformMatrix4f("model", model);
	shd.setUniformMatrix3f("normal", normalMatrix);
	shd.setUniform3f("meshSpecCol", glm::vec3(1, 1, 1));
	shd.setUniformTexture("diffuseTex", diffuseTex, 0);;
	shd.setUniformTexture("specTex", specTex, 1);
	shd.setUniformTexture("normTex", nrmTex, 2);
	shd.setUniformTexture("envMap", cubemap.getTexture(), 3);

	shd.setUniform3f("ambientCol", glm::vec3(0.0, 0.0, 0.0));
	shd.setUniform3f("lightPos", pointLight.position);
	shd.setUniform1f("lightCutoff", pointLight.cutoff);
	shd.setUniform3f("lightConeDir", pointLight.direction);
	shd.setUniform3f("lightCol", getLightColor(pointLight));
	shd.setUniform3f("cameraPos", cam.pos);
	shieldMesh.draw();
	shd.end();
}

//--------------------------------------------------------------
void ofApp::draw() {
	using namespace glm;

	static float t = 0.0f;
	t += ofGetLastFrameTime();

	SpotLight spotLight;
	spotLight.color = vec3(1, 1, 1);
	spotLight.position = cam.pos + vec3(sin(t), 0, 0);
	spotLight.intensity = 1.0;
	spotLight.direction = vec3(0, 0, -1);
	spotLight.cutoff = glm::cos(glm::radians(15.0f));

	mat4 proj = perspective(cam.fov, 1024.0f / 768.0f, 0.01f, 10.0f);

	mat4 view = inverse(translate(cam.pos));

	drawShield(spotLight, proj, view);
	drawWater(spotLight, proj, view);
	drawSkybox(spotLight, proj, view);

}

void createCubemap()
{

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
