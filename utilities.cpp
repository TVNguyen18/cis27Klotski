#include "utilities.h"

void updatePositionMatrix(int objNumber, int startCell, int endCell, int& exitFlag, int * posMatrix, Stack * positionStack)
{
	switch (objNumber) // which kind of object selected
	{
	case 1: //the red
		cout << "\nRed object Selected!";
		if (endCell == startCell + 2 || endCell == startCell + 6) //moving right
		{
			if (startCell % 4 == 2) break; // last column
			if (*(posMatrix + startCell + 2) != -1 || *(posMatrix + startCell + 6) != -1) //destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = *(posMatrix + startCell + 4) = -1;
			*(posMatrix + startCell + 2) = *(posMatrix + startCell + 6) = objNumber;
			break;
		}
		if (endCell == startCell - 1 || endCell == startCell + 3) //moving left
		{
			cout << "\nMoving left!";
			if (startCell % 4 == 0) break; // first column
			if (*(posMatrix + startCell - 1) != -1 || *(posMatrix + startCell + 3) != -1) //destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell + 1) = *(posMatrix + startCell + 5) = -1;
			*(posMatrix + startCell - 1) = *(posMatrix + startCell + 3) = objNumber;
			break;
		}
		if ((endCell == startCell - 4) || (endCell == startCell - 3)) //moving up
		{
			cout << "\nMoving up!";
			if (startCell < 4) break; // first row
			if (*(posMatrix + startCell - 4) != -1 || *(posMatrix + startCell - 3) != -1) //destination cells are not empty									
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell + 4) = *(posMatrix + startCell + 5) = -1;
			*(posMatrix + startCell - 4) = *(posMatrix + startCell - 3) = objNumber;
			break;
		}
		if ((endCell == startCell + 8) || (endCell == startCell + 9)) //moving down
		{
			cout << "\nMoving down!";

			if (*(posMatrix + startCell + 8) != -1 || *(posMatrix + startCell + 9) != -1) //destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = *(posMatrix + startCell + 1) = -1;
			*(posMatrix + startCell + 8) = *(posMatrix + startCell + 9) = objNumber;
			break;
		}
		break;
	case 4: //the yellow
		cout << "\nYellow object Selected!";
		if (endCell == startCell + 2) //moving right
		{
			if (startCell % 4 == 2) break; // last column
			if ((*(posMatrix + startCell + 2) != -1)) //destination cells are not empty
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
			if (*(posMatrix + startCell - 1) != -1) //destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell + 1) = -1;
			*(posMatrix + startCell - 1) = objNumber;

			break;
		}
		if ((endCell == startCell - 4) || (endCell == startCell - 3)) //moving up
		{
			cout << "\nMoving up!";
			if (startCell < 4) break; // first row
			if (*(posMatrix + startCell - 4) != -1 || *(posMatrix + startCell - 3) != -1) //destination cells are not empty									
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = *(posMatrix + startCell + 1) = -1;
			*(posMatrix + startCell - 4) = *(posMatrix + startCell - 3) = objNumber;
			break;
		}
		if ((endCell == startCell + 4) || (endCell == startCell + 5)) //moving down
		{
			cout << "\nMoving down!";

			if (*(posMatrix + startCell + 4) != -1 || *(posMatrix + startCell + 5) != -1) //destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = *(posMatrix + startCell + 1) = -1;
			*(posMatrix + startCell + 4) = *(posMatrix + startCell + 5) = objNumber;
			break;
		}
		break;
	case 0:
	case 2:
	case 3:
	case 5: //the green obj
		cout << "\nGreen object Selected!";
		if ((endCell == startCell + 1) || (endCell == startCell + 5)) //moving right
		{
			if (startCell % 4 == 3) break; // last column
			if ((*(posMatrix + startCell + 1) != -1) || (*(posMatrix + startCell + 5) != -1)) //destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = *(posMatrix + startCell + 4) = -1;
			*(posMatrix + startCell + 1) = *(posMatrix + startCell + 5) = objNumber;

			break;
		}
		if ((endCell == startCell - 1) || (endCell == startCell + 3)) //moving left
		{
			cout << "\nMoving left!";
			if (startCell % 4 == 0) break; // first column
			if (*(posMatrix + startCell - 1) != -1 || *(posMatrix + startCell + 3) != -1) //destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = *(posMatrix + startCell + 4) = -1;
			*(posMatrix + startCell - 1) = *(posMatrix + startCell + 3) = objNumber;
			break;
		}
		if (endCell == startCell - 4) //moving up
		{
			cout << "\nMoving up!";
			if (startCell < 4) break; // first row
			if (*(posMatrix + startCell - 4) != -1) //destination cells are not empty									
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
			if (*(posMatrix + startCell + 8) != -1) //destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			*(posMatrix + startCell) = -1;
			*(posMatrix + startCell + 8) = objNumber;

			break;
		}
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

			if (*(posMatrix + startCell + 1) != -1) //destination cells are not empty
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
			if (*(posMatrix + startCell - 1) != -1)  //destination cells are not empty
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
			if (*(posMatrix + startCell - 4) != -1)  //destination cells are not empty
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
			if (*(posMatrix + startCell + 4) != -1)  //destination cells are not empty
				break;

			//update posMatrix
			positionStack->push(posMatrix);
			posMatrix[startCell] = -1;
			posMatrix[startCell + 4] = objNumber;
			break;
		}
		break;
	case 20: //Undo
		if (!positionStack->isEmpty()) {
			delete[] posMatrix;
			posMatrix = positionStack->pop();
		}
		break;
	case 21: //reset
		while (!positionStack->isEmpty()) {
			delete[] posMatrix;
			posMatrix = positionStack->pop();
		}
		break;
	case 22:
		exitFlag = 1;
		break;
	default:
		// out of range
		break;
	}
}
