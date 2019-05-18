/**
* Program Name: KlotSki Game
* Discussion  : Declaration File --
*				  utilities.h
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#ifndef UTILITIES_H
#define UTILITIES_H

#include "include.h"

void printVertexPos(glm::vec3 src);
int getObjNumber(int* posMatrix, int cellNumber);
int getMovingDirection(int startCell, int endCell);
int getCellNumber(double xpos, double ypos);
void updatePositionMatrix(int objNumber, int startCell, 
	int endCell, int& exitFlag, int* posMatrix, 
	Stack* positionStack);
void updatePosMatrixTo_nthStep(int * posMatrix, 
	Stack * positionStack, int * solMatrix, int step);
int findStep(int *posMatrix, int* solMatrix);

#endif