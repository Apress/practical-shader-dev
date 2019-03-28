#include "ofxEasyCubemap.h"
#include "ofGLUtils.h"

ofxEasyCubemap::ofxEasyCubemap()
{
	glEnable(GL_TEXTURE_CUBE_MAP);
	textureData.texData.bAllocated = false;
	textureData.texData.glInternalFormat = GL_RGB;
	textureData.texData.textureID = 0;
	textureData.texData.textureTarget = GL_TEXTURE_CUBE_MAP;

}

ofxEasyCubemap::~ofxEasyCubemap()
{
	glDeleteTextures(1, &glTexId);
}

bool ofxEasyCubemap::load(const std::filesystem::path& front,
							const std::filesystem::path& back,
							const std::filesystem::path& right,
							const std::filesystem::path& left,
							const std::filesystem::path& top,
							const std::filesystem::path& bottom)
{
	
	bool success = images[0].load(right);
	success |= images[1].load(left);
	success |= images[2].load(top);
	success |= images[3].load(bottom);
	success |= images[4].load(front);
	success |= images[5].load(back);

	if (!success)
	{
		fprintf(stderr, "ERROR: EasyCubemap failed to load an image");
		return false;
	}

	unsigned int faceWidth = images[0].getWidth();
	unsigned int faceHeight = images[0].getHeight();

	glGenTextures(1, &glTexId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, glTexId);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	unsigned char* faceData[6];

	for (int i = 0; i < 6; ++i)
	{
		if (images[i].getWidth() != faceWidth || images[i].getHeight() != faceHeight)
		{
			fprintf(stderr, "ERROR: EasyCubemap couldn't load because not all source textures are the same size\n");
			return false;
		}

		faceData[i] = images[i].getPixels().getData();

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, images[i].getTexture().texData.glInternalFormat, faceWidth, faceHeight, 0, ofGetGLFormat(images[i].getPixels()), GL_UNSIGNED_BYTE, faceData[i]);
	}
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	textureData.texData.textureID = glTexId;
	textureData.texData.bAllocated = true;

	return true;
}

const ofTexture& ofxEasyCubemap::getTexture() const
{
	return textureData;
}

ofTexture& ofxEasyCubemap::getTexture()
{
	return textureData;
}
