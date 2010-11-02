/*
 * mesh2d.cpp
 *
 *  Created on: Oct 3, 2010
 *      Author: rolf
 */
#include "mesh2d.h"
#include <iostream>
#include <GL/gl.h>
#include "light.h"
mesh2d::mesh2d() {
	VBO = 0;
	meshStore = NULL;
	indiceStore = NULL;
	shaderProgram = NULL;
	attribVertexPos = -2;
	UVCoord = -2;
	tex1Loc = -2;
	tex0Loc = -2;
	tex2Loc = -2;

	light0Loc = -2;
	light1Loc = -2;
	light2Loc = -2;

	modelMatrixLoc = -2;
	cameraMatrixLoc = -2;
	colorMatrixLoc = -2;

}

void mesh2d::draw() {
	/*Update Stores if the VBO has changed*/
	if (changed) {
		updateVBO();
	}
	/*If no shader is present processing in core profile cant be done..*/
	if (shaderProgram == NULL) {
		std::cout << "ERROR: NO SHADER PRESENT\n";
		return;
	}

	/*Get attribute locations*/
	if (attribVertexPos == -2) {
		attribVertexPos = shaderProgram->getAttribLocation("vertexPosition");
	}
	if (UVCoord == -2) {
		UVCoord = shaderProgram->getAttribLocation("UVCoord");
	}

	if (modelMatrixLoc == -2) {
		modelMatrixLoc = shaderProgram->getUniformLocation("modelMatrix");
	}
	if (cameraMatrixLoc == -2) {
		cameraMatrixLoc = shaderProgram->getUniformLocation("cameraMatrix");
	}

	if (colorMatrixLoc == -2) {
		colorMatrixLoc = shaderProgram->getUniformLocation("colorMatrix");
	}
	shaderProgram->activate();

	if (tex1Loc == -2) {
		tex1Loc = shaderProgram->getUniformLocation("tex1");
	}
	if (tex0Loc == -2) {
		tex0Loc = shaderProgram->getUniformLocation("tex0");
	}
	if (tex2Loc == -2) {
		tex2Loc = shaderProgram->getUniformLocation("tex2");
	}

	if (light0Loc == -2) {
		light0Loc = shaderProgram->getUniformLocation("light0");
	}
	if (light1Loc == -2) {
		light0Loc = shaderProgram->getUniformLocation("light0");
	}
	if (light2Loc == -2) {
		light0Loc = shaderProgram->getUniformLocation("light0");
	}

	if (mat != NULL) {
		if (tex0Loc >= 0) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mat->getTexture(material::GROUND));
			glUniform1iARB(tex0Loc, 0);
		}
		if (tex1Loc >= 0) {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, mat->getTexture(material::MULTI1));
			glUniform1iARB(tex1Loc, 1);
		}

		if (tex2Loc >= 0) {
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, mat->getTexture(material::MULTI2));
			glUniform1iARB(tex2Loc, 2);
		}

		if (colorMatrixLoc >= 0) {
			colorMatrixStore = mat->colorVector.mem;
			glUniformMatrix4fvARB(colorMatrixLoc, 1, GL_FALSE, colorMatrixStore);
		}
	}

	if (modelMatrixLoc >= 0) {
		glUniformMatrix4fvARB(modelMatrixLoc, 1, GL_FALSE, modelMatrixStore);
	}
	if (cameraMatrixLoc >= 0) {
		if (cam != NULL) {
			cameraMatrixStore = cam->cameraMatrix.mem;
			glUniformMatrix4fvARB(cameraMatrixLoc, 1, GL_FALSE,
					cameraMatrixStore);
		}

	}

	int nofLights = light::getNumberOfLights();
	if (nofLights >= 1) {
		if (light0Loc >= 0) {
			light * light0 = light::getLight(0);
			const GLfloat * l0store = light0->output.mem;
			glUniformMatrix4fvARB(light0Loc, 1, GL_FALSE, l0store);
		}
		if (nofLights >= 2) {
			if (light1Loc >= 0) {
				light * light1 = light::getLight(1);
				const GLfloat * l1store = light1->lightData.mem;
				glUniformMatrix4fvARB(light1Loc, 1, GL_FALSE, l1store);

			}
			if (nofLights >= 3) {
				if (light2Loc >= 0) {
					light * light2 = light::getLight(2);
					const GLfloat * l2store = light2->lightData.mem;
					glUniformMatrix4fvARB(light2Loc, 1, GL_FALSE, l2store);

				}
			}
		}
	}

	glColor4f(1, 1, 1, 1);

	if (attribVertexPos == -1) {
		return;
	}
	glBindBufferARB(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArrayARB(attribVertexPos);
	glVertexAttribPointerARB(attribVertexPos, 3, GL_FLOAT, GL_FALSE, 5
			* sizeof(float), (GLvoid *) 0);

	if (UVCoord >= 0) {
		glEnableVertexAttribArrayARB(UVCoord);
		glVertexAttribPointerARB(UVCoord, 2, GL_FLOAT, GL_FALSE, 5
				* sizeof(float), (GLvoid *) (3 * 4));
	}
	drawMode = GL_TRIANGLE_STRIP;

	glDrawElements(drawMode, indiceStoreSize, GL_UNSIGNED_SHORT, indiceStore);

	shaderProgram->disable();
}

void mesh2d::loadTest() {
	addVert(-2, -2, 0, 1);
	addVert(2, -2, 1, 1);
	addVert(2, 2, 1, 0);
	addVert(-2, 2, 0, 0);
	addVert(-2, -2, 0, 1);
	buildTriangleStrip();
	shaderProgram = new shader("mesh_shader.vp", "mesh_shader.fp");
	loadImage("guy2.png");

}

void mesh2d::buildTriangleStrip() {
	int vertlistsize = vertList.size();
	for (int i = 0; i < vertlistsize; i++) {
		indices.push_back(i);
	}
}

void mesh2d::addIndice(unsigned short value) {
	indices.push_back(value);
	changed = true;
}
/*addVert x, y, u, v
 * Adds vertexes with UV-coordinates, Still needs indices though
 */
void mesh2d::addVert(float x, float y, float u, float v) {

	int oldsize = vertList.size();
	changed_from &= oldsize;

	vertList.push_back(Vector2D(x, y));
	UVList.push_back(Vector2D(u, v));

	changed_to = oldsize + 1;
	changed = true;
	newsize = changed_to;
}

void mesh2d::updateVBO() {

	//Size changed since last time?
	if (meshStoreSize != vertList.size()) {
		resizeMeshStore = true;
		meshStoreSize = vertList.size();
	}
	if (indiceStoreSize != indices.size()) {
		resizeIndiceStore = true;
		indiceStoreSize = indices.size();
	}

	if (resizeMeshStore) {
		if (meshStore != NULL) {
			delete meshStore;
		}
		meshStore = new verticle[meshStoreSize];
	}

	if (resizeIndiceStore) {
		if (indiceStore != NULL) {
			delete indiceStore;
		}
		indiceStore = new unsigned short[indiceStoreSize];
	}

	//Copy data to arrays
	for (int it = 0; it < meshStoreSize; it++) {
		meshStore[it] = verticle::generate(vertList[it], UVList[it]);
	}

	for (int it = 0; it < indiceStoreSize; it++) {
		indiceStore[it] = indices[it];
	}

	//Copy arrays to vertex buffer
	if (resizeMeshStore) {

		glDeleteBuffersARB(1, &VBO);
		glGenBuffersARB(1, &VBO);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, VBO);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, meshStoreSize * 5 * sizeof(float),
				meshStore, GL_STATIC_DRAW_ARB);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	}

	changed = false;

}

void mesh2d::loadImage(string path) {
	image * newimg = new image(path);
	textures.push_back(newimg);
}

void mesh2d::loadImage(image * tex) {
	textures.push_back(tex);
}

void mesh2d::deleteImage(string name) {
	for (int i = 0; i < textures.size(); i++) {
		image * deletethis;
		deletethis = textures[i];
		if (deletethis->getName() == name) {
			textures.erase(textures.begin() + i);
			delete deletethis;
			return;
		}
	}
}

void mesh2d::setTexture(int index, GLuint texture) {
	textures[index]->setTexture(texture);
}

mesh2d::verticle::verticle() {
	x = 0;
	y = 0;
	z = 0;
	u = 0;
	v = 0;
}

mesh2d::verticle::verticle(float x, float y, float z, float u, float v) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->u = u;
	this->v = v;
}

mesh2d::verticle mesh2d::verticle::generate(Vector2D vertex, Vector2D UV) {
	return verticle(vertex.x, vertex.y, 0, UV.x, UV.y);
}

void mesh::setModelMatrix(const arma::Mat<float>& newModelMatrix) {
	modelMatrixStore = newModelMatrix.mem;
	/*
	 long int * loc =(long int *) modelMatrixStore;
	 for(int i = 0; i < 8; i++){
	 loc[i] = matptr[i];
	 }*/
}

void mesh::setPerspectiveMatrix(const float * newMatrixStore) {
	perspectiveMatrixStore = newMatrixStore;
}

void mesh::setMaterial(material * nmat) {
	mat = nmat;
}
