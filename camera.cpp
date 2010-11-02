/*
 * camera.cpp
 *
 *  Created on: Oct 28, 2010
 *      Author: rolf
 */
#include "camera.h"
camera::camera(){

	top = 5;;
	right = 5;
	near = 5;
	far = 1000;

	perspectiveMatrix.zeros(4,4);
	perspectiveMatrix(0,0) = 1;
	perspectiveMatrix(1,1) = 1;
	perspectiveMatrix(2,2) = 1;
	perspectiveMatrix(3,3) = 1;

	cameraMatrix.zeros(4,4);
	cameraMatrix(0,0) = 1;
	cameraMatrix(1,1) = 1;
	cameraMatrix(2,2) = 1;
	cameraMatrix(3,3) = 1;
}

void camera::loadProjection(float top, float right, float near, float far){
	this->top = top;
	this->right = right;
	this->near = near;
	this->far = far;
	perspectiveMatrix(0,0) = near/right;
	perspectiveMatrix(1,1) = near/top;
	perspectiveMatrix(2,2) = -(far + near)/(far-near);
	perspectiveMatrix(3,2) = -1;
	perspectiveMatrix(2,3) = -2*far*near/(far-near);
}

void camera::loadOrthogonal(float top, float right, float near, float far){
	this->top = top;
	this->right = right;
	this->near = near;
	this->far = far;
	perspectiveMatrix.zeros(4,4);
	perspectiveMatrix(0,0) = 1/right;
	perspectiveMatrix(1,1) = 1/top;
	perspectiveMatrix(2,2) = -2/(far - near);
	perspectiveMatrix(2,3) =-(far + near)/(far - near);
	perspectiveMatrix(3,3) = 1;

}

void camera::calcCamera(const arma::Mat<float>& transformMatrix){
	cameraMatrix = perspectiveMatrix*transformMatrix;
	//printCameraMatrix();
}
#include <iostream>

void camera::printCameraMatrix(){
	for(int i = 0; i < 4;i++){
		for(int j = 0; j < 4;j++){
			std::cout << cameraMatrix(i,j) << " ";
		}
		std::cout << "\n";
	}
}
