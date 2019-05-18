/**
* Program Name: KlotSki Game
* Discussion  : Declaration File --
*				  draw.h
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#ifndef DRAW_H
#define DRAW_H

#include "include.h"

using namespace std;

void loadTexture(GLuint texture[], unsigned char* image,
	int i, int w, int h);
void bindAndDrawTexture(GLuint texture0[], 
	GLuint shaderProgramID);

#endif