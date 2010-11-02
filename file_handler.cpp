/*
 * file_handler.cpp
 *
 *  Created on: May 29, 2010
 *      Author: rolf
 */
#include <iostream>
#include "file_handler.h"
filehandler::filehandler(void) {

}
filehandler::filehandler(std::string filename) {
	this->filename = filename;

	if (!open_read()) {
		std::cout << "Cant open file: " << filename << "\n";
	}
}

void filehandler::goToChar(int linenr) {
	filestream.seekg(linenr);
}

std::string filehandler::readLine() {
	if (!filestream.good()) {
		filestream.close();
		return "";
	}

	char buf[256];
	filestream.getline(buf, 256);
	return std::string(buf) + "\n";
}

bool filehandler::open_read() {

	if (filestream.is_open()) {
		filestream.close();
	}
	filestream.open(filename.c_str(), std::ios_base::in);
	if (filestream.good()) {
		return true;
	}
	return false;
}

std::string filehandler::getFileAsStdString(void) {
		std::string output;
	char line[256];
	std::cout << ".";
	while (filestream.good()) {

		filestream.getline(line, 256);
		output += line;
		output += '\n';
	}
	std::cout << ".";
	//output +='\0';
	filestream.clear();
	filestream.close();
	return output;
}

char * filehandler::getFileAsCharString(void) {
	char * output;

	if (filestream.good()) {
		filestream.seekp(0,std::ios::end);

		int size = filestream.tellg();
		output = new char[size];
		filestream.seekg(0,std::ios::beg);
		filestream.read(output, size);
		filestream.close();
		output[size] = '\0';
		return output;
	} else {
		return NULL;
	}
}
