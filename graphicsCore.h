/*
 * graphicsCore.h
 *
 *  Created on: Oct 29, 2010
 *      Author: rolf
 */

#ifndef GRAPHICSCORE_H_
#define GRAPHICSCORE_H_
#include <vector>

class camera;
namespace graphics{
	extern bool started;
	extern float angle;
	extern int var;

	bool init();
	void end();
	void setActiveCamera(camera * cam);

	extern camera * activeCamera;

class graphicsCore{
public:

	graphicsCore();

private:
	std::vector <camera * > cameras;

};


}
#endif /* GRAPHICSCORE_H_ */
