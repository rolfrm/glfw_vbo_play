/*
 * file_handler.h
 *
 *  Created on: May 29, 2010
 *      Author: rolf
 */

#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <string>
#include <iostream>
#include <fstream>

class filehandler{
	/* Filehandler
	 * Can handle a files..
	 * Not very well implemented.
	 *
	 * Call constructor with the path to the file as argument
	 * */
public:
	filehandler(void);
	filehandler(std::string);

	std::string getFileAsStdString(void);
	char * getFileAsCharString(void);

	void goToChar(int pos);
	std::string readLine(void);
	void writeLine(std::string line);
	bool open_read();

private:
	std::fstream filestream;
	std::string filename;
};

#endif /* FILE_HANDLER_H_ */
