/*
 * scenegraph.cpp
 *
 *  Created on: Oct 25, 2010
 *      Author: rolf
 */

#include "scenegraph.h"
#include <math.h>
using namespace arma;

void sceneGraph::node::traverse(PASSTYPE pst) {
	this->pst = pst;
	activate();
	if (pst == UPDATE) {
		update();
	}
	if (pst == RENDER) {
		render();
	}

	for (list<node *>::iterator it = children.begin(); it != children.end(); it++) {
		(*it)->traverse(pst);
	}

	deactivate();
}

void sceneGraph::node::update() {

}

void sceneGraph::node::render() {

}
void sceneGraph::node::activate() {

}

void sceneGraph::node::deactivate() {

}

void sceneGraph::node::addChild(node * child) {
	children.push_back(child);
}

void sceneGraph::orderedNode::activate() {
	for (list<node *>::iterator it = orderedChildren.begin(); it
			!= orderedChildren.end(); it++) {
		(*it)->traverse(pst);
	}
}

void sceneGraph::orderedNode::deactivate() {

}

void sceneGraph::orderedNode::addOrderedChild(node * child, POSITION pos) {
	if (pos == BACK) {
		orderedChildren.push_back(child);
	} else if (pos == FRONT) {
		orderedChildren.push_front(child);
	}
}
#include<iostream>
sceneGraph::transformNode::transformNode() {
	translation.zeros(4, 4);
	translation(0, 0) = 1;
	translation(1, 1) = 1;
	translation(2, 2) = 1;
	translation(3, 3) = 1;

	if (totalTranslation.n_elem == 0) {
		totalTranslation = translation;
	}
}

void sceneGraph::transformNode::activate() {
	savedTranslationMatrix = totalTranslation;

	totalTranslation = totalTranslation * translation;

	//printTotalTranslation();
}

void sceneGraph::transformNode::deactivate() {
	totalTranslation = savedTranslationMatrix;
}

Mat<float> sceneGraph::transformNode::getTotalTranslation() {
	return totalTranslation;
}

void sceneGraph::transformNode::rotate(float x, float y, float z) {
	arma::Mat<float> rmat;
	rmat.zeros(4, 4);
	float cosx = cos(x);
	float sinx = sin(x);

	float cosz = cos(z);
	float sinz = sin(z);

	float cosy = cos(y);
	float siny = sin(y);

	rmat(0, 0) = cosx * cosz;
	rmat(1, 0) = cosx * sinz;
	rmat(2, 0) = -sin(x);

	rmat(0, 1) = -cosy * sinz + siny * sinx * cosz;
	rmat(1, 1) = cosy * cosz + siny * sinx * sinz;
	rmat(2, 1) = siny * cosx;

	rmat(0, 2) = siny * sinz + cosy * sinx * cosz;
	rmat(1, 2) = -siny * cosz + cosy * sinx * sinz;
	rmat(2, 2) = cosy * cosx;

	rmat(3, 3) = 1;
	translation = rmat * translation;
}

void sceneGraph::transformNode::translate(float x, float y, float z) {
	arma::Mat<float> tmat;
	tmat.zeros(4, 4);
	tmat(0, 0) = 1;
	tmat(1, 1) = 1;
	tmat(2, 2) = 1;
	tmat(3, 3) = 1;
	tmat(0, 3) = x;
	tmat(1, 3) = y;
	tmat(2, 3) = z;
	translation = tmat * translation;
}

void sceneGraph::transformNode::scale(float x, float y, float z) {
	arma::Mat<float> smat;
	smat.zeros(4, 4);
	smat(0, 0) = x;
	smat(1, 1) = y;
	smat(2, 2) = z;
	smat(3, 3) = 1;
	translation = smat * translation;
	;
}

void sceneGraph::transformNode::print() {
	for (int i = 0; i < translation.n_rows; i++) {
		for (int j = 0; j < translation.n_cols; j++) {
			std::cout << translation(i, j) << " ";
		}
		std::cout << "\n";
	}
}
void sceneGraph::transformNode::printTotalTranslation() {
	for (int i = 0; i < totalTranslation.n_rows; i++) {
		for (int j = 0; j < totalTranslation.n_cols; j++) {
			std::cout << totalTranslation(i, j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

}
sceneGraph::materialNode::materialNode(material * new_mat) {
	mat = new_mat;
}

void sceneGraph::materialNode::activate() {
	//activate new material
	materialstack.push(mat);

}

material * sceneGraph::materialNode::getTopMaterial() {
	return materialstack.top();
}
stack<material*> sceneGraph::materialNode::materialstack;

void sceneGraph::materialNode::deactivate() {
	materialstack.pop();
	//reactivate old material
}

arma::Mat<float> sceneGraph::transformNode::totalTranslation;
sceneGraph::VBOLeaf::VBOLeaf() {
	meshObject = NULL;
}

sceneGraph::VBOLeaf::VBOLeaf(mesh * newmeshobject) {
	meshObject = newmeshobject;
}

void sceneGraph::VBOLeaf::setMesh(mesh * newmeshobject) {
	meshObject = newmeshobject;
}
void sceneGraph::VBOLeaf::activate() {
	if (meshObject != NULL) {
		meshObject->setModelMatrix(sceneGraph::transformNode::getTotalTranslation());
		meshObject->setMaterial(sceneGraph::materialNode::getTopMaterial());
		meshObject->draw();

	}
}

#include "camera.h"

sceneGraph::cameraLeaf::cameraLeaf() {
	cam = NULL;
}

void sceneGraph::cameraLeaf::activate() {

}

void sceneGraph::cameraLeaf::update() {
	if (cam != NULL) {

		cam->calcCamera(sceneGraph::transformNode::getTotalTranslation());
	}
}

void sceneGraph::cameraLeaf::setCam(camera * cam) {
	this->cam = cam;
}

#include "light.h"
sceneGraph::lightLeaf::lightLeaf(light * lt) {
	lightData = lt;
}

void sceneGraph::lightLeaf::activate() {
	if (lightData != NULL) {
		lightData->setTransform(sceneGraph::transformNode::getTotalTranslation());
		lightData->setOutput();

	}
}
