/*
 * light.cpp
 *
 *  Created on: Oct 30, 2010
 *      Author: rolf
 */

#include "light.h"

light::light(){
	lightData.zeros(4,4);
	position.zeros(4,1);
	position(3,0) = 1; //homogenus position
	transform.zeros(4,4);
	transform(0,0) = 1;
	transform(1,1) = 1;
	transform(2,2) = 1;
	transform(3,3) = 1;
	lights.push_back(this);
	output.zeros(4,4);
}

void light::setTransform(const arma::Mat<float>& transform){
	this->transform = transform;
}

void light::setColor(light::LIGHTTYPE lt, float r, float g, float b,float att){
	lightData(0,lt) = r;
	lightData(1,lt) = g;
	lightData(2,lt) = b;
	lightData(3,lt) = att;
}

light * light::getLight(int number){
	return lights[number];
}

int light::getNumberOfLights(){
	return lights.size();
}

void light::setOutput(){
	output = lightData;
	arma::Mat<float> tpos;
	tpos.zeros(4,1);
	tpos = transform*position;
	output(0,3) = tpos(0,0);
	output(1,3) = tpos(1,0);
	output(2,3) = tpos(2,0);
	output(3,3) = 1;
	/*for(int i = 0;i < 4;i++){
		for(int j = 0; j < 4;j++){
			std::cout << output(i,j) << " ";
		}
		std::cout << "\n";
	}*/
}

std::vector<light *> light::lights;
