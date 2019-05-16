#ifndef MOUSE_H
#define MOUSE_H

#include "include.h"

class Mouse {
private:
	double currentX;
	double currentY;
	double currentXR;
	double currentYR;
	int initialFlag;
public:
	Mouse();
	~Mouse();
	int getinitialFlag(void);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	
};
#endif