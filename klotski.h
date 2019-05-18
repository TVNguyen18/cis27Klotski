/**
* Program Name: KlotSki Game
* Discussion  : Declaration File --
*				  klotski.h
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#ifndef KLOTSKI_H
#define KLOTSKI_H

#include "include.h"

const int WIDTH = 640;
const int HEIGHT = 480;
GLFWwindow* window;

double currentX = -1;
double currentY = 0;

double currentXR = 0;
double currentYR = 0;

int initialFlag = -1;

int uniformLocation;

void mouse_button_callback(GLFWwindow* window, int button, 
	int action, int mods);

#endif
