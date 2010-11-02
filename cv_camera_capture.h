#pragma once
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <GL/gl.h>
#include <vector>

using namespace std;
class CVCameraCapture{
	/* Camera to openGL Texture that implements the OpenCV webcam input functions of highgui.h
	 * Constructor is called with the camera number on linux this corresponds
	 * to /dev/videoX where X is the number
	 *
	 * Generates a GLuint Texture that is updated every time captureImage is called
	 *
	 * Implement filterImage to change the behaviour
	 * */
public:
	CVCameraCapture(unsigned int cam);
	int captureImage();
	GLuint getTexture();
	virtual void filterImage(IplImage * capturedImage);

private:
	int generateTexture();
	CvCapture* capture;
	GLuint image;
};
