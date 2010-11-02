/*
 * camera.h
 *
 *  Created on: Oct 28, 2010
 *      Author: rolf
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include <armadillo>
class camera{
public:
	camera();
	arma::Mat<float> cameraMatrix;
	arma::Mat<float> perspectiveMatrix;
	void calcCamera(const arma::Mat<float>& transformMatrix);
	void loadProjection(float top, float right, float near, float far);
	void loadOrthogonal(float top, float right, float near, float far);
	void printCameraMatrix();
	float top ;
	float left;
	float right ;
	float button;
	float near;
	float far ;
};

#endif /* CAMERA_H_ */
