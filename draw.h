#ifndef DRAW_H
#define DRAW_H

#include <iostream>
#include <GL/glew.h>
#include <SOIL2/SOIL2.h>

using namespace std;

void loadTexture(GLuint texture[], unsigned char* image, int i, int w, int h);

#endif