/*
 * graphicsCore.cpp
 *
 *  Created on: Oct 29, 2010
 *      Author: rolf
 */

#include "graphicsCore.h"
#include <GL/glfw.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL_extart_functions.h"
using namespace graphics;
bool graphics::started = true;
float graphics::angle = 0;
int graphics::var = 0;
camera * graphics::activeCamera;

void GLFWCALL keycallback(int key, int action) {
	graphics::var = 1;
}

int GLFWCALL windowclosecallback(void) {
	graphics::started = false;
}

void GLFWCALL mouseclickcallback(int button, int action) {
	graphics::started = false;
}

void GLFWCALL mouseposcallback(int x, int y) {

}

void graphics::end(){
glfwSleep(0.02);
		glfwSwapBuffers();
}

bool graphics::init(){
	//Setup glfw window and callbacks
	glfwInit();
	glfwOpenWindow(800, 600, 8, 8, 8, 0, 0, 0, GLFW_WINDOW);
	glfwSetKeyCallback(keycallback);
	glfwSetWindowCloseCallback(windowclosecallback);
	glfwSetMouseButtonCallback(mouseclickcallback);
	glfwSetMousePosCallback(mouseposcallback);

	//Setup extensions (EXT/ARB)
	setupGLSL();

	//Setup viewport
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.5,0.5,0.5,1);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
#include <iostream>
graphicsCore::graphicsCore(){
}
