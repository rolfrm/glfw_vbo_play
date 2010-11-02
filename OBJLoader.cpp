/*
 * OBJLoader.cpp
 *
 *  Created on: Oct 11, 2010
 *      Author: rolf
 */
#include "OBJLoader.h"
OBJLoader::OBJLoader(){

}

#include "file_handler.h"
#include<iostream>
int OBJLoader::loadOBJFile(string path){
	if(instance == NULL){
		instance = new OBJLoader();
	}
	filehandler file(path);
	string line;
	while( (line = file.readLine() ) != ""){
		std::cout << line;

	}
}

OBJLoader * OBJLoader::instance = NULL;
