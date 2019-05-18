/**
* Program Name: KlotSki Game
* Discussion  : utilities.cpp
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#include "utilities.h"

void printVertexPos(glm::vec3 src) {
	cout << src.s << " , " << src.t;
}

int getObjNumber(int* posMatrix, int cellNumber) {
	if (cellNumber < 20)
		return *(posMatrix + cellNumber);
	else
		return cellNumber;
}

int getMovingDirection(int startCell, int endCell) {
	if (endCell == startCell + 1)
		return 6; //moving to the right
	if (endCell == startCell - 1)
		return 4; //moving to the left
	if (endCell == startCell - 4)
		return 8; //moving up
	if (endCell == startCell + 4)
		return 2; //moving down
	return 0; //moving out of range
}

int getCellNumber(double xpos, double ypos) {

	if (xpos > -42 && xpos < 38 && ypos> 122 && ypos < 202)
		return 0;

	if (xpos > 40 && xpos < 120 && ypos> 120 && ypos < 200)
		return 1;

	if (xpos > 120 && xpos < 200 && ypos> 122 && ypos < 202)
		return 2;

	if (xpos > 202 && xpos < 282 && ypos> 122 && ypos < 202)
		return 3;

	if (xpos > -42 && xpos < 38 && ypos> 42 && ypos < 122)
		return 4;

	if (xpos > 40 && xpos < 120 && ypos> 42 && ypos < 122)
		return 5;

	if (xpos > 122 && xpos < 202 && ypos> 42 && ypos < 122)
		return 6;

	if (xpos > 202 && xpos < 282 && ypos> 42 && ypos < 122)
		return 7;

	if (xpos > -42 && xpos < 38 && ypos> -40 && ypos < 40)
		return 8;

	if (xpos > 40 && xpos < 120 && ypos> -40 && ypos < 40)
		return 9;

	if (xpos > 122 && xpos < 202 && ypos> -40 && ypos < 40)
		return 10;

	if (xpos > 202 && xpos < 282 && ypos> -40 && ypos < 40)
		return 11;

	if (xpos > -41 && xpos < 37 && ypos> -120 && ypos < -42)
		return 12;

	if (xpos > 41 && xpos < 119 && ypos> -120 && ypos < -42)
		return 13;

	if (xpos > 122 && xpos < 202 && ypos > -122 && ypos < -42)
		return 14;

	if (xpos > 203 && xpos < 281 && ypos > -120 && ypos < -42)
		return 15;

	if (xpos > -41 && xpos < 37 && ypos> -201 && ypos < -123)
		return 16;

	if (xpos > 41 && xpos < 119 && ypos > -201 && ypos < -123)
		return 17;

	if (xpos > 121 && xpos < 199 && ypos > -201 && ypos < -123)
		return 18;

	if (xpos > 203 && xpos < 281 && ypos > -201 && ypos < -123)
		return 19;

	if (xpos > -261 && xpos < -101 && ypos > -65 && ypos < -5) 
		//undo
		return 20;

	if (xpos > -261 && xpos < -101 && ypos > -135 && ypos < -75) 
		//reset
		return 21;

	if (xpos > -261 && xpos < -101 && ypos > -205 && ypos < -145) 
		//exit
		return 22;

	if (xpos > -261 && xpos < -101 && ypos > 9 && ypos < 69) 
		//solution
		return 23;

	return 50;  // out of range

}

void updatePositionMatrix(int objNumber, int startCell, 
	int endCell, 	int& modeFlag, int * posMatrix, 
	Stack * positionStack)
{
	switch (objNumber) // which kind of object selected
	{
	case 1: //the red
		cout << "\nRed object Selected!";
		if (endCell == startCell + 2 || 
			endCell == startCell + 6) //moving right
		{
			if (startCell % 4 == 2) break; // last column
			if (*(posMatrix + startCell + 2) != -1 || 
				*(posMatrix + startCell + 6) != -1) 
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = 
				*(posMatrix + startCell + 4) = -1;
			*(posMatrix + startCell + 2) = 
				*(posMatrix + startCell + 6) = objNumber;
			break;
		}
		if (endCell == startCell - 1 || 
			endCell == startCell + 3) //moving left
		{
			cout << "\nMoving left!";
			if (startCell % 4 == 0) break; // first column
			if (*(posMatrix + startCell - 1) != -1 || 
				*(posMatrix + startCell + 3) != -1) 
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell + 1) = 
				*(posMatrix + startCell + 5) = -1;
			*(posMatrix + startCell - 1) = 
				*(posMatrix + startCell + 3) = objNumber;
			break;
		}
		if ((endCell == startCell - 4) || 
			(endCell == startCell - 3)) //moving up
		{
			cout << "\nMoving up!";
			if (startCell < 4) break; // first row
			if (*(posMatrix + startCell - 4) != -1 || 
				*(posMatrix + startCell - 3) != -1) 
				//destination cells are not empty									
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell + 4) = 
				*(posMatrix + startCell + 5) = -1;
			*(posMatrix + startCell - 4) = 
				*(posMatrix + startCell - 3) = objNumber;
			break;
		}
		if ((endCell == startCell + 8) || 
			(endCell == startCell + 9)) //moving down
		{
			cout << "\nMoving down!";

			if (*(posMatrix + startCell + 8) != -1 || 
				*(posMatrix + startCell + 9) != -1) 
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = 
				*(posMatrix + startCell + 1) = -1;
			*(posMatrix + startCell + 8) = 
				*(posMatrix + startCell + 9) = objNumber;
			break;
		}
		// if being in playback mode, return to playing mode
		if (modeFlag == 1)
			modeFlag = 0;
		break;
	case 4: //the yellow
		cout << "\nYellow object Selected!";
		if (endCell == startCell + 2) //moving right
		{
			if (startCell % 4 == 2) break; // last column
			if ((*(posMatrix + startCell + 2) != -1)) 
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = -1;
			*(posMatrix + startCell + 2) = objNumber;

			break;
		}
		if (endCell == startCell - 1) //moving left
		{
			cout << "\nMoving left!";
			if (startCell % 4 == 0) break; // first column
			if (*(posMatrix + startCell - 1) != -1) 
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell + 1) = -1;
			*(posMatrix + startCell - 1) = objNumber;

			break;
		}
		if ((endCell == startCell - 4) || 
			(endCell == startCell - 3)) //moving up
		{
			cout << "\nMoving up!";
			if (startCell < 4) break; // first row
			if (*(posMatrix + startCell - 4) != -1 || 
				*(posMatrix + startCell - 3) != -1) 
				//destination cells are not empty									
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = 
				*(posMatrix + startCell + 1) = -1;
			*(posMatrix + startCell - 4) = 
				*(posMatrix + startCell - 3) = objNumber;
			break;
		}
		if ((endCell == startCell + 4) || 
			(endCell == startCell + 5)) //moving down
		{
			cout << "\nMoving down!";

			if (*(posMatrix + startCell + 4) != -1 || 
				*(posMatrix + startCell + 5) != -1) 
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = 
				*(posMatrix + startCell + 1) = -1;
			*(posMatrix + startCell + 4) = 
				*(posMatrix + startCell + 5) = objNumber;
			break;
		}
		// if being in playback mode, return to playing mode
		if (modeFlag == 1)
			modeFlag = 0;
		break;
	case 0:
	case 2:
	case 3:
	case 5: //the green obj
		cout << "\nGreen object Selected!";
		if ((endCell == startCell + 1) || 
			(endCell == startCell + 5)) //moving right
		{
			if (startCell % 4 == 3) break; // last column
			if ((*(posMatrix + startCell + 1) != -1) || 
				(*(posMatrix + startCell + 5) != -1)) 
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = 
				*(posMatrix + startCell + 4) = -1;
			*(posMatrix + startCell + 1) = 
				*(posMatrix + startCell + 5) = objNumber;

			break;
		}
		if ((endCell == startCell - 1) || 
			(endCell == startCell + 3)) 
			//moving left
		{
			cout << "\nMoving left!";
			if (startCell % 4 == 0) break; // first column
			if (*(posMatrix + startCell - 1) != -1 || 
				*(posMatrix + startCell + 3) != -1) 
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = 
				*(posMatrix + startCell + 4) = -1;
			*(posMatrix + startCell - 1) = 
				*(posMatrix + startCell + 3) = objNumber;
			break;
		}
		if (endCell == startCell - 4) //moving up
		{
			cout << "\nMoving up!";
			if (startCell < 4) break; // first row
			if (*(posMatrix + startCell - 4) != -1) 
				//destination cells are not empty									
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell + 4) = -1;
			*(posMatrix + startCell - 4) = objNumber;
			break;
		}
		if (endCell == startCell + 8) //moving down
		{
			cout << "\nMoving down!";
			if (startCell > 15) break; // last row					
			if (*(posMatrix + startCell + 8) != -1) 
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = -1;
			*(posMatrix + startCell + 8) = objNumber;

			break;
		}
		// if being in playback mode, return to playing mode
		if (modeFlag == 1)
			modeFlag = 0;
		break;

	case 6: // blue obj
	case 7:
	case 8:
	case 9:
		cout << "\nBlue object Selected!";
		if (endCell == startCell + 1) //moving right
		{
			cout << "\nMoving right!";
			if (startCell % 4 == 3) break; // last column

			if (*(posMatrix + startCell + 1) != -1) 
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = -1;
			*(posMatrix + startCell + 1) = objNumber;

			break;
		}
		if (endCell == startCell - 1) //moving left
		{
			cout << "\nMoving left!";
			if (startCell % 4 == 0) break; // first column
			if (*(posMatrix + startCell - 1) != -1)  
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			posMatrix[startCell] = -1;
			posMatrix[startCell - 1] = objNumber;
			break;
		}
		if (endCell == startCell - 4)  //moving up
		{
			cout << "\nMoving up!";
			if (startCell < 4) break; // first row
			if (*(posMatrix + startCell - 4) != -1)  
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			posMatrix[startCell] = -1;
			posMatrix[startCell - 4] = objNumber;
			break;
		}
		if (endCell == startCell + 4) //moving down
		{
			cout << "\nMoving down!";
			if (startCell > 15) break; // last row
			if (*(posMatrix + startCell + 4) != -1)  
				//destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			posMatrix[startCell] = -1;
			posMatrix[startCell + 4] = objNumber;
			break;
		}
		// if being in playback mode, return to playing mode
		if (modeFlag == 1)
			modeFlag = 0;
		break;
	case 20: //Undo
		// if being in playback mode, return to playing mode
		if (modeFlag == 1)
			modeFlag = 0;

		if (!positionStack->isEmpty()) {
			delete[] posMatrix;
			posMatrix = positionStack->pop();
		}		
		break;
	case 21: //reset
		// if being in playback mode, return to playing mode
		if (modeFlag == 1)
			modeFlag = 0;
		while (!positionStack->isEmpty()) {
			delete[] posMatrix;
			posMatrix = positionStack->pop();
		}
		break;
	case 22: //exit
		modeFlag = 2; // exit mode
		break;
	case 23: //show Solution
		if(modeFlag != 2)
			modeFlag = 1; // Playback mode
		break;
	default:
		// out of range
		break;
	}
}

void updatePosMatrixTo_nthStep(int * posMatrix, 
	Stack * positionStack, int * solMatrix, int step)
{
	positionStack->push(posMatrix);
	for (int i = 0; i < 20; i++)
		*(posMatrix + i) = *(solMatrix + step * 20 + i);
}

int findStep(int * posMatrix, int * solMatrix)
{	
	int isOK = 1;
	// need to be updated to 116 step rather than 5
	for (int i = 0; i < 117; i++) {
		isOK = 1;
		for (int j = 0; j < 20; j++) {
			// if there is any value doesnot match,
			// assign the wrong flag and stop the loop
			if (*(posMatrix + j) != *(solMatrix + i * 20 + j)) {
				isOK = 0;
				j = 20;
			}			
		}
		// if after 20 loops, all values are match
		// return this step
		if (isOK)
			return i;
	}
	return 0;
}

