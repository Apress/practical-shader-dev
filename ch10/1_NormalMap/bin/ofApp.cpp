#include "ofApp.h"
#include <vector>

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

	shieldMesh.load("shield.ply");
	calcTangents(shieldMesh);

	blinnPhongShader.load("mesh.vert", "blinnPhong.frag");

	diffuseTex.load("shield_diffuse.png");
	specTex.load("shield_spec.png");
	nrmTex.load("shield_normal.png");

	cam.pos = glm::vec3(0, 0.75f, 1.0);
	cam.fov = glm::radians(90.0f);

}

glm::vec3 getLightDirection(DirectionalLight& l)
{
	return glm::normalize(l.direction * -1.0f);
}

glm::vec3 getLightColor(DirectionalLight& l)
{
	return l.color * l.intensity;
}

//--------------------------------------------------------------
void ofApp::update() {

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
	mat4 view = inverse(translate(cam.pos));

	mat4 model = translate(vec3(0.0, 0.75, 0.0f));
	mat4 mvp = proj * view * model;
	mat3 normalMatrix = mat3(transpose(inverse(model)));

	blinnPhongShader.begin();
	blinnPhongShader.setUniformMatrix4f("mvp", mvp);
	blinnPhongShader.setUniformMatrix4f("model", model);
	blinnPhongShader.setUniformMatrix3f("normal", normalMatrix);
	blinnPhongShader.setUniform3f("meshSpecCol", glm::vec3(1, 1, 1));
	blinnPhongShader.setUniformTexture("diffuseTex", diffuseTex, 0);;
	blinnPhongShader.setUniformTexture("specTex", specTex, 1);
	blinnPhongShader.setUniformTexture("normTex", nrmTex, 2);
	blinnPhongShader.setUniform3f("ambientCol", glm::vec3(0.1, 0.1, 0.1));
	blinnPhongShader.setUniform3f("lightDir", getLightDirection(dirLight));
	blinnPhongShader.setUniform3f("lightCol", getLightColor(dirLight));
	blinnPhongShader.setUniform3f("cameraPos", cam.pos);
	shieldMesh.draw();
	blinnPhongShader.end();
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
