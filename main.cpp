/*
 * main.cpp
 *
 *  Created on: Sep 13, 2010
 *      Author: rolf
 */


#include <iostream>
#include <math.h>
#include "shader.h"
#include "material.h"
#include "mesh2d.h"
#include "scenegraph.h"
#include "camera.h"
#include "graphicsCore.h"
#include "OBJLoader.h"
#include "light.h"
int main() {
	graphics::graphicsCore gc;
	graphics::init();
	sceneGraph::node root;

	material m1;
	m1.loadTexture(material::GROUND,"brickwall.jpg");
	//m1.loadTexture(material::MULTI1,"guy.png");
	//m1.loadTexture(material::MULTI2,"im2.png");
	m1.setColor(material::DIFFUSE,0.7,0.5,0.3,1);
	m1.setColor(material::EMISSIVE,0,0,0,0);
	m1.setColor(material::SPECULAR,1,1,1,1);

	light l1;
	l1.setColor(light::AMBIENT,1,1,1,1/10.0);
	l1.setColor(light::SPECULAR,1,1,1,1);
	l1.setColor(light::DIFFUSE,0.5,0.2,0.6,1);
	sceneGraph::lightLeaf ll(&l1);
	sceneGraph::transformNode lt1;

	camera c1;
	mesh2d q2;
	q2.loadTest();
	q2.cam = &c1;
	material m2;
	m2.setColor(material::DIFFUSE,1,1,1,1);
	m2.setColor(material::SPECULAR,1,1,1,1);
	m2.setColor(material::EMISSIVE,1,1,0.5,1);
	sceneGraph::materialNode mn2(&m2);
	sceneGraph::VBOLeaf vb2(&q2);

	lt1.addChild(&mn2);
	lt1.scale(0.1,0.1,1);
	mn2.addChild(&vb2);

	lt1.addChild(&ll);

	root.addChild(&lt1);
	sceneGraph::materialNode mn1(&m1);



	c1.loadProjection(5,5,1,100);



	root.addChild(&mn1);

	sceneGraph::transformNode t1;
	mn1.addChild(&t1);

	sceneGraph::transformNode ct1;
	sceneGraph::transformNode ct2;
	sceneGraph::cameraLeaf cc1;

	cc1.setCam(&c1);
	root.addChild(&ct1);

	ct1.addChild(&ct2);
	ct2.addChild(&cc1);

	sceneGraph::transformNode t2;
	sceneGraph::transformNode t3;

	t1.addChild(&t2);
	root.addChild(&t3);

	//OBJLoader::loadOBJFile("test1.obj");
	mesh2d quadMesh;
	quadMesh.cam = &c1;
	quadMesh.loadTest();

	sceneGraph::VBOLeaf vboleaf(&quadMesh);
	t2.addChild(&vboleaf);
	//t3.addChild(&vboleaf);
	t1.translate(0,0,-20);
	t2.scale(10,10,1);
	lt1.translate(0,-4,-4);
	int i = glGetError();
		if(i != 0){
			std::cout << i << "\n";
			return 0;
	}
		float t = 0;
	while (graphics::started) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		t +=0.1;
		//t2.rotate(0,0,0.1);
		lt1.translate(0,0,-0.1 );
		m1.setColor(material::DIFFUSE,0.5 + sin(t)*0.5,0.5 + cos(t)*0.5,cos(t*3)*0.5,1);
		root.traverse(sceneGraph::UPDATE);
		graphics::end();
		int i = glGetError();
		if(i != 0){
			std::cout << i << "\n";
		}	
			
	}

}
