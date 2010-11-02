/*
 * cv_camera_capture.cpp
 *
 *  Created on: Oct 6, 2010
 *      Author: rolf
 */

#include "cv_camera_capture.h"
#include <iostream>
CVCameraCapture::CVCameraCapture(unsigned int camera) {
	capture = cvCaptureFromCAM(camera);
	image = NULL;
	generateTexture();
	captureImage();
}

int CVCameraCapture::generateTexture() {
	glGenTextures(1, &image);
	glBindTexture(GL_TEXTURE_2D, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

int CVCameraCapture::captureImage() {
	IplImage* capt_image = cvQueryFrame(capture);

	filterImage(capt_image);

	glBindTexture(GL_TEXTURE_2D, image);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, capt_image->width,
			capt_image->height, 0, GL_BGR, GL_UNSIGNED_BYTE,
			capt_image->imageData);
}

GLuint CVCameraCapture::getTexture() {
	return image;
}

void CVCameraCapture::filterImage(IplImage * capt_image){

}
