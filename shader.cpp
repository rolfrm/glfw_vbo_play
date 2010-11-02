/*
 * shader.cpp
 *
 *  Created on: Oct 5, 2010
 *      Author: rolf
 */
#include "shader.h"
#include "file_handler.h"
#include "GL_extart_functions.h"
shader * shader::active_shader;

shader::shader(string vert_path, string frag_path){
	shaderready = false;

	filehandler fragtext(frag_path);
	filehandler verttext(vert_path);
	shaderprogram = glCreateProgramObjectARB();
	vertShader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	fragShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

	const char * fs = (const char*) fragtext.getFileAsCharString();
	const char * vs = (const char*) verttext.getFileAsCharString();

	glShaderSourceARB(fragShader,1,&fs,NULL);
	glShaderSourceARB(vertShader,1,&vs,NULL);
	glBindAttribLocationARB(getShaderProgram(),3, "Position");
	glBindAttribLocationARB(getShaderProgram(),1, "Normal");
	glBindAttribLocationARB(getShaderProgram(),2,"TexCoords");
	glCompileShaderARB(vertShader);
	glCompileShaderARB(fragShader);

	glAttachObjectARB(shaderprogram,vertShader);
	glAttachObjectARB(shaderprogram,fragShader);

	glLinkProgramARB(shaderprogram);
	int len;
	char log[1000];
	glGetInfoLogARB(shaderprogram,999,&len,log);
	std::cout << log;
	shaderready = true;

 }

bool shader::shader_ready(){
	return shaderready;
}

void shader::activate(){
		if(active_shader == NULL){
			glUseProgramObjectARB(shaderprogram);
			active_shader = this;
		}else{
			std::cout << "Cannot activate: A shaderprogram is active\n";
		}
	}
void shader::disable(){
		if(active_shader == this){
			glUseProgramObjectARB(0);
			active_shader = NULL;
		}else{
			std::cout << "Cannot disable: This shader is not active!\n";
		}
	}

GLuint shader::getShaderProgram(){
		return shaderprogram;
	}

GLint shader::getAttribLocation(string attribName){
	return glGetAttribLocationARB(shaderprogram, attribName.c_str());

}

GLint shader::getUniformLocation(string uniformName){
	return glGetUniformLocationARB(shaderprogram, uniformName.c_str());
}
