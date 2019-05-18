/**
* Program Name: KlotSki Game
* Discussion  : Declaration File --
*				  init.h
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#ifndef INIT_H
#define INIT_H

#include "include.h"

bool init(GLFWwindow** window, int WIDTH, int HEIGHT);
void displayVersion(void);
void initSolMatrix(int** solMatrix);

#endif