/*
 * material.h
 *
 *  Created on: Oct 25, 2010
 *      Author: rolf
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_
#include <stack>
#include <armadillo>
#include <string>
#include <GL/gl.h>
using namespace std;

class material{
	/*Material:
	 * Defines shader, texture, color, shinyness,..?
	 * Required:
	 * color(rgba)
	 *
	 * Optionals:
	 * Ground texture; overrides color where alpha = 1
	 * Multitexture
	 * Glow texture
	 * bump texture
	 * */

public:
	struct texture{
		GLuint tex;

	};

	enum TEXTURETYPE{
		GROUND = 0,
		MULTI1,
		MULTI2,
		MULTI3,
		GLOW,
		BUMP,
		SIZE

	};

	enum COLORTYPE{
			DIFFUSE = 0,
			SPECULAR = 1,
			EMISSIVE = 2
	};
	material();
	material(float red_dif, float green_dif, float blue_dif, float alpha_dif,float red_spec, float blue_spec, float green_spec, float alpha_spec,float red_emi, float green_emi, float blue_emi, float alpha_emi);
	void setColor(COLORTYPE ct, float r, float g, float b, float a);
	bool texActive(TEXTURETYPE tt);
	bool loadTexture(TEXTURETYPE tt,std::string);
	GLuint getTexture(TEXTURETYPE tt);
	bool hasTexture(TEXTURETYPE tt);
	arma::Mat<float> colorVector;
	texture textures[SIZE];


};

#endif /* MATERIAL_H_ */
