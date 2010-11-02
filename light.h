/*
 * light.h
 *
 *  Created on: Oct 30, 2010
 *      Author: rolf
 */

#ifndef LIGHT_H_
#define LIGHT_H_
#include<armadillo>
#include <vector>

class light{
	/*light
	 *
	 */

public:
	enum LIGHTTYPE{
			AMBIENT = 0,
			DIFFUSE = 1,
			SPECULAR = 2
		};
	light();
	void setTransform(const arma::Mat<float>& transform);
	void setColor(LIGHTTYPE lt, float r, float g, float b,float att);
	void setOutput();
	arma::Mat<float> transform;
	arma::Mat<float> lightData;
	arma::Mat<float> position;
	arma::Mat<float> output;

	static light * getLight(int number);
	static int getNumberOfLights();
	static std::vector<light *> lights;
};

#endif /* LIGHT_H_ */
