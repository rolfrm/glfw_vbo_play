/*
 * material.cpp
 *
 *  Created on: Oct 30, 2010
 *      Author: rolf
 */
#include "material.h"
using namespace std;
#define TEXTUREUNINIT 0
material::material() {
	colorVector.ones(4, 4);
	for (int i = 0; i < SIZE; i++) {
		textures[i].tex = TEXTUREUNINIT;
	}
}

material::material(float red_dif, float green_dif, float blue_dif,
		float alpha_dif, float red_spec, float blue_spec, float green_spec,
		float alpha_spec, float red_emi, float green_emi, float blue_emi,
		float alpha_emi) {

}

void material::setColor(material::COLORTYPE ct, float r, float g, float b,
		float a) {
	colorVector(0, ct) = r;
	colorVector(1, ct) = g;
	colorVector(2, ct) = b;
	colorVector(3, ct) = a;
}

bool material::texActive(TEXTURETYPE tt) {
	if (textures[tt].tex > 0) {
		return true;
	}
	return false;
}

#include <IL/il.h>
bool material::loadTexture(TEXTURETYPE tt, string path) {
	if (textures[tt].tex >= 0) {
		glDeleteTextures(1, &(textures[tt].tex));
	}
	static bool _ILIsInit = false;
	if (!_ILIsInit) {
		ilInit();
		_ILIsInit = true;
	}
	ILuint texid;
	ilGenImages(1, &texid);
	ilBindImage(texid);
	if (ilLoadImage(path.c_str())) {
		ilConvertImage(ilGetInteger(IL_IMAGE_FORMAT), IL_UNSIGNED_BYTE);

	} else {
		std::cout << "Problems converting image: " << path << "\n";
		return false;
	}
	glGenTextures(1, &(textures[tt].tex));
	glBindTexture(GL_TEXTURE_2D, (textures[tt].tex));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), width, height,
			0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
	ilDeleteImages(1, &texid);
	return true;

}

GLuint material::getTexture(TEXTURETYPE tt) {
	return textures[tt].tex;
}

bool material::hasTexture(TEXTURETYPE tt){
	if(textures[tt].tex > 0){
		return true;
	}
	return false;
}
