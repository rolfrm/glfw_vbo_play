#pragma once
#include <GL/gl.h>
#include <string>
using namespace std;
class shaderStart;
class shaderStop;


class shader{
	/*
	 * Needs the path to the vertex and fragment shader files.
	 * Also needs opengl shaderfunctions to be inited. Depends on GL_exart_functions
	 *
	 * Activate shader to use while drawing
	 *
	 * Deactivate shader when done drawing with shader*/

public:
 	shader(string vert_path, string frag_path);

	bool shader_ready();

	void activate();

	void disable();
	GLint getAttribLocation(string attribName);
	GLint getUniformLocation(string uniformName);
	GLuint getShaderProgram();

private:
	bool shaderready;
	GLuint shaderprogram;
	GLuint vertShader;
	GLuint fragShader;
	static shader * active_shader;
};
