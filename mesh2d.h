/*
 * mesh2d.h
 *
 *  Created on: Oct 3, 2010
 *      Author: rolf
 */

#ifndef MESH2D_H_
#define MESH2D_H_
#include "toolModule.h"
#include <GL/gl.h>
#include "GL_extart_functions.h"
#include "shader.h"
#include <list>
#include "shader.h"
#include "image.h"
#include "camera.h"
#include <armadillo>
#include "material.h"
using namespace std;

class mesh{
public:
	virtual void draw() = 0;

	void setModelMatrix(const arma::Mat<float>& newModelMatrix);
	void setPerspectiveMatrix(const float * newMatrixStore);
	void setMaterial(material * new_mat);

	GLint modelMatrixLoc;
	GLint perspectiveMatrixLoc;
	GLint cameraMatrixLoc;
	GLint colorMatrixLoc;
	GLuint tex0Loc;
	GLuint tex1Loc;
	GLuint tex2Loc;
	GLuint light0Loc;
	GLuint light1Loc;
	GLuint light2Loc;
	const GLfloat * modelMatrixStore;
	const GLfloat * perspectiveMatrixStore;
	const GLfloat * cameraMatrixStore;
	const GLfloat * colorMatrixStore;
	material * mat;
	camera * cam;
};

class mesh2d:public mesh {
	/*mesh2d
	 *Is a 2 dimentional mesh. Add Vertexes and indices respectivly.
	 * */
public:
	mesh2d();

	/*Draw function*/
	void draw();

	/*Vertexes and indices*/
	void addVert(float x, float y, float u, float v);
	void addIndice(unsigned short value);


	/*Textures*/
	void setTexture(int index, GLuint texture); /*Sets a texture. Warning: Doesn't overwritten textures*/
	void loadImage(string imagename); /*Loads a texture from path imagename*/
	void loadImage(image * tex); /*Inserts a texture*/
	void deleteImage(string imagename); /*Deletes a texture with name imagename*/

	/*Build indices as..*/
	void buildTriangleStrip(); /*GL_TRIANGLE_STRIPS*/
	void buildPoints(); /*GL_POINTS*/

	/*Test functions*/
	void loadTest();

	class verticle{
	public:
		float x,y,z,u,v;
		verticle(float x, float y, float z, float u, float v);
		verticle();
		static verticle generate(Vector2D vertex, Vector2D UV);
	};
private:
	void updateVBO();

	vector<Vector2D> vertList;
	vector<Vector2D> UVList;
	vector<unsigned short> indices;
	verticle * meshStore;
	unsigned short * indiceStore;

	int meshStoreSize;
	bool resizeMeshStore;

	int indiceStoreSize;
	bool resizeIndiceStore;


	bool changed;
	int newsize;
	int changed_from, changed_to; //TODO

	bool buffer_generated;
	GLuint VBO;
	shader * shaderProgram;
	vector<image *> textures; //images

	GLint attribVertexPos;
	GLint UVCoord;

	GLenum drawMode;
};

#endif /* MESH2D_H_ */
