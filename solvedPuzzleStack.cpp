#include "include.h"

// Step 1

Stack createSolvedPuzzleStack() {

	int* posMatrix = new int[20]{
			0, 1, 1, 2,
			0, 1, 1, 2,
			3, 4, 4, 5,
			3, 6, 7, 5,
			8, -1, -1, 9


	};

	Stack positionStack;

	int exitFlag = 0;

	Vertex vertices[20 * 4];
	Vertex cellVertices[20 * 4];
	initVertexAry(vertices);
	initCellVertexAry(cellVertices);

	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
	GLuint indices[] = {
		// obj 0
		0, 1, 2,
		1, 2, 3,

		// obj 1
		4, 5, 6,
		5, 6, 7,

		// obj 2
		8, 9, 10,
		9, 10, 11,

		// obj 3
		12, 13, 14,
		13, 14, 15,

		// obj 4
		16, 17, 18,
		17, 18, 19,

		// obj 5
		20, 21, 22,
		21, 22, 23,

		// obj 6
		24, 25, 26,
		25, 26, 27,

		// obj 7
		28, 29, 30,
		29, 30, 31,

		// obj 8
		32, 33, 34,
		33, 34, 35,

		// obj 9
		36, 37, 38,
		37, 38, 39,

		// obj 10
		40, 41, 42,
		41, 42, 43,

		// obj 11
		44, 45, 46,
		45, 46, 47,

		// obj 12
		48, 49, 50,
		49, 50, 51,

		// obj 13
		52, 53, 54,
		53, 54, 55,

		// obj 14
		56, 57, 58,
		57, 58, 59,

		// obj 15
		60, 61, 62,
		61, 62, 63,

		// obj 16
		64, 65, 66,
		65, 66, 67,

		// obj 17
		68, 69, 70,
		69, 70, 71,

		// obj 18
		72, 73, 74,
		73, 74, 75,

		// obj 18
		76, 77, 78,
		77, 78, 79,
	};


	//Step 1 - Blue Move Right
	positionStack.push(posMatrix);
	*(posMatrix + 16) = -1;
	*(posMatrix + 16 + 1) = 8;

	//Step 2 - Green Move Down
	positionStack.push(posMatrix);
	*(posMatrix + 12) = -1;
	*(posMatrix + 12 + 8) = 3;

	//Step 3 - Yellow Move Left
	positionStack.push(posMatrix);
	*(posMatrix + 9 + 1) = -1;
	*(posMatrix + 9 - 1) = 4;

	//Step 4 - Blue Move Down
	positionStack.push(posMatrix);
	posMatrix[14] = -1;
	posMatrix[14 + 4] = 7;

	//Step 5 - Green Move Left
	positionStack.push(posMatrix);
	*(posMatrix + 11) = *(posMatrix + 11 + 4) = -1;
	*(posMatrix + 11 - 1) = *(posMatrix + 11 + 3) = 5;

	//Step 6 - Blue Move Up
	positionStack.push(posMatrix);
	posMatrix[19] = -1;
	posMatrix[19 - 4] = 9;

	//Step 7 - Blue Move Right
	positionStack.push(posMatrix);
	*(posMatrix + 18) = -1;
	*(posMatrix + 18 + 1) = 7;

	//Step 8 - Green Move Down
	positionStack.push(posMatrix);
	*(posMatrix + 14) = -1;
	*(posMatrix + 14 + 8) = 5;

	//Step 9 - Yellow Move Right;
	positionStack.push(posMatrix);
	*(posMatrix + 9) = -1;
	*(posMatrix + 9 + 2) = 4;

	//Step 10 - Yellow Move Right;
	positionStack.push(posMatrix);
	*(posMatrix + 10) = -1;
	*(posMatrix + 10 + 2) = 4;

	//Step 11 - Blue Move Up
	positionStack.push(posMatrix);
	posMatrix[13] = -1;
	posMatrix[13 - 4] = 6;

	//Step 12 - Blue Move Left
	positionStack.push(posMatrix);
	posMatrix[9] = -1;
	posMatrix[9 - 1] = 6;

	//Step 13 - Blue Move Up
	positionStack.push(posMatrix);
	posMatrix[17] = -1;
	posMatrix[17 - 4] = 8;

	//Step 14 - Blue Move Up
	positionStack.push(posMatrix);
	posMatrix[13] = -1;
	posMatrix[13 - 4] = 8;

	//Step 15 - Green Move Left
	positionStack.push(posMatrix);
	*(posMatrix + 18) = *(posMatrix + 18 + 4) = -1;
	*(posMatrix + 18 - 1) = *(posMatrix + 18 + 3) = 5;

	//Step 16 - Blue Move Left
	positionStack.push(posMatrix);
	posMatrix[15] = -1;
	posMatrix[15 - 1] = 9;

	//Step 17 - Blue Move Down
	positionStack.push(posMatrix);
	posMatrix[14] = -1;
	posMatrix[14 + 4] = 9;

	return positionStack;
}