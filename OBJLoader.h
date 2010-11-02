/*
 * OBJLoader.h
 *
 *  Created on: Oct 11, 2010
 *      Author: rolf
 */

#ifndef OBJLOADER_H_
#define OBJLOADER_H_
#include <string>
using namespace std;
class OBJLoader{
	OBJLoader();
	static OBJLoader * instance;
public:
	static int loadOBJFile(string path);

};

#endif /* OBJLOADER_H_ */
