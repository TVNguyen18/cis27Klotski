/**
* Program Name: KlotSki Game
* Discussion  : klotski.cpp
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#include "include.h"
#include "klotski.h"

using namespace std;


//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
int main()
{
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	const int totalObjs = 21;
	const int totalCells = 20;
	
	int* posMatrix = new int[20]{
		0, 1, 1, 2,
		0, 1, 1, 2,
		3, 4, 4, 5,
		3, 6, 7, 5,
		8, -1, -1, 9
	};

	int* solMatrix;

	Stack positionStack;

	int modeFlag = 0;
	// modeFlag == 0 : Playing mode
	// modeFlag == 1 : Playback mode
	// modeFlag == 2 : Exit game

	Vertex vertices[totalObjs * 4];
	Vertex cellVertices[totalCells * 4];
	GLuint indices[totalObjs * 6];

	const char* vertexCSrc;
	const char* fragmentCSrc;
	string vertexSrc;
	string fragmentSrc;

	int imageWidth = 0;
	int imageHeight = 0;
	int objNumber;
	int endCell;
	int startCell;
	GLuint texture[11];	
	int SolStep = 0;

	initVertexAry(vertices);
	initCellVertexAry(cellVertices);
	initIndices(indices);	
	initSolMatrix(&solMatrix);

	Timer tmr;
	double t = 0;
	SolStep = 0;

	if (init(&window, WIDTH, HEIGHT) == false) {
		return 1;
	}

	displayVersion();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	// read vertex and fragment shader from file
	vertexSrc = readShaderSource("../vertex_shader.shader");
	fragmentSrc = readShaderSource("../fragment_shader.shader");

	// conver string to char* so it compatible with openGL
	vertexCSrc = vertexSrc.c_str();
	fragmentCSrc = fragmentSrc.c_str();

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShaderID, 1, &vertexCSrc, NULL);
	glShaderSource(fragmentShaderID, 1, &fragmentCSrc, NULL);

	compileShader(vertexShaderID);
	compileShader(fragmentShaderID);

	GLuint shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
	glLinkProgram(shaderProgramID);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertices),
		&vertices[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices),
		indices,
		GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
		sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 
		sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 
		sizeof(Vertex), (GLvoid*)offsetof(Vertex, textCoord));
	glEnableVertexAttribArray(2);

	// bind VAO 0
	glBindVertexArray(0);

	// texture 1		

	glGenTextures(11, texture);

	unsigned char* green = 
		SOIL_load_image("../images/0_texture.png",
		&imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture, green, 0, imageWidth, imageHeight);

	unsigned char* red = 
		SOIL_load_image("../images/1_texture.png",
		&imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture, red, 1, imageWidth, imageHeight);

	unsigned char* yellow = 
		SOIL_load_image("../images/2_texture.png", 
		&imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture, yellow, 2, imageWidth, imageHeight);

	unsigned char* blue = 
		SOIL_load_image("../images/3_texture.png", 
		&imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture, blue, 3, imageWidth, imageHeight);

	unsigned char* background = 
		SOIL_load_image("../images/4_texture.png", 
		&imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture, background, 4, imageWidth, imageHeight);

	unsigned char* logo = 
		SOIL_load_image("../images/logo.png", 
		&imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture, logo, 5, imageWidth, imageHeight);

	unsigned char* undoButton = 
		SOIL_load_image("../images/undo_button.png",
		&imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture, undoButton, 6, imageWidth, imageHeight);

	unsigned char* resetButton = 
		SOIL_load_image("../images/reset_button.png",
		&imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture, resetButton, 7, imageWidth, imageHeight);

	unsigned char* exitButton = 
		SOIL_load_image("../images/exit_button.png",
		&imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture, exitButton, 8, imageWidth, imageHeight);

	unsigned char* solButton = 
		SOIL_load_image("../images/sol_button.png",
		&imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture, solButton, 9, imageWidth, imageHeight);

	unsigned char* exitBackground = 
		SOIL_load_image("../images/exit_texture.png", 
		&imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture, exitBackground, 10, 
		imageWidth, imageHeight);
	
	while (!glfwWindowShouldClose(window)) {

		// Update input
		glfwPollEvents();

		glfwSetMouseButtonCallback(window, mouse_button_callback);
	
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == 
			GLFW_RELEASE && initialFlag != -1) {

			startCell = getCellNumber(currentX, currentY);
			endCell = getCellNumber(currentXR, currentYR);
			objNumber = getObjNumber(posMatrix, startCell);

			//reset the flag
			initialFlag = -1;

			if (objNumber == -1) // clicked on the empty cell
			{
				//  put the out of range value for objNumber
				objNumber = 50;
			}			
	
			cout << "\nstartCell = " << startCell;
			cout << "\nendCell = " << endCell;
			cout << "\nObjSelected = " << objNumber;

			// looking for the first cell contains the objSelected
			for (int i = 0; i < 20; i++) {
				if (*(posMatrix + i) == objNumber) {
					startCell = i;
					cout << "\nstartCell updated to = " << startCell;
					i = 20;
				}
			}

			// update posMatrix according to the object moved
			updatePositionMatrix(objNumber, startCell, endCell, 
				modeFlag, posMatrix, &positionStack);

			//update vertices
			updateVertexAray(vertices, cellVertices, posMatrix);

			if (objNumber < 20) {
				cout << "\n\nNew Position of Object " 
					<< objNumber << " is: ";
				printVertexPos(vertices[objNumber * 4].position);
			}
			cout << "\nPosition Matrix updated = ";
			for (int i = 0; i < 5; i++) {
				cout << "\n";
				for (int j = 0; j < 4; j++) {
					cout << *(posMatrix + i * 4 + j) << " ";
				}
			}

			//update vertex buffer
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER,
				sizeof(vertices),
				&vertices[0],
				GL_STATIC_DRAW);	
		}

		// clear
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | 
			GL_STENCIL_BUFFER_BIT);

		// use a program
		glUseProgram(shaderProgramID);

		// bind VAO
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);

		// set up uniform
		glUniform1i(glGetUniformLocation(shaderProgramID, 
			"my_Texture"), 0);

		switch (modeFlag) {
		case 0: // Playing mode
			SolStep = 0;
			bindAndDrawTexture(texture, shaderProgramID);
			break;
		case 1: // Playback mode
			if (SolStep == 117) { 
				//done solution => go back to playing mode
				modeFlag = 0;
				SolStep = 0;
				break;
			}			

			if(SolStep == 0) // looking for soltion step
				SolStep = findStep(posMatrix, solMatrix);

			// if current position does not match solution steps
			// and it is possible to undo then undo

			if (SolStep == 0 && !positionStack.isEmpty()) {
				delete[] posMatrix;
				posMatrix = positionStack.pop();
				//update vertices	
				updateVertexAray(vertices, cellVertices, posMatrix);
				//update vertex buffer
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER,
					sizeof(vertices),
					&vertices[0],
					GL_STATIC_DRAW);

				tmr.reset();
				t = tmr.elapsed();
				while (t < 0.5) {

					bindAndDrawTexture(texture, shaderProgramID);
					t = tmr.elapsed();
				}
			}
			else {  //find a proper step then continue from that step		
				std::cout << "\ntime duration : " << t << std::endl;
				cout << "\nStep " << SolStep;

				// update to new position
				updatePosMatrixTo_nthStep(posMatrix, &positionStack, 
					solMatrix, SolStep);

				cout << "\nPosition Matrix updated = ";
				for (int i = 0; i < 5; i++) {
					cout << "\n";
					for (int j = 0; j < 4; j++) {
						cout << *(posMatrix + i * 4 + j) << " ";
					}
				}

				//update vertices	
				updateVertexAray(vertices, cellVertices, posMatrix);
				//update vertex buffer
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER,
					sizeof(vertices),
					&vertices[0],
					GL_STATIC_DRAW);

				tmr.reset();
				t = tmr.elapsed();
				while (t < 0.5) {

					bindAndDrawTexture(texture, shaderProgramID);
					t = tmr.elapsed();
				}
				SolStep++;
			}			

			break;
		case 2: // exit game
			// activate texture		

			glUniform1i(glGetUniformLocation(shaderProgramID, 
				"my_Texture"), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture[10]);
			
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 
				(const void*)(120 * sizeof(int)));
			break;	
		}		
			   
		//clean up
		glDisableVertexAttribArray(0);

		glUseProgram(0);

		glfwSwapBuffers(window);
		glFlush();
	}

	glfwTerminate();

	// clean up
	positionStack.emptyStack();
	delete[] posMatrix;
	posMatrix = nullptr;
	delete[] solMatrix;
	solMatrix = nullptr;

	return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, 
	int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
	{
		cout << "\nLeft click!";
		glfwGetCursorPos(window, &currentX, &currentY);
		cout << "\n" << currentX << "," << currentY;
		currentX -= 320;
		currentY = -currentY + 240;
		cout << " => " << currentX << "," << currentY;
		initialFlag = 1;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) 
	{
		cout << "\nLeft release!";
		glfwGetCursorPos(window, &currentXR, &currentYR);
		cout << "\n" << currentXR << "," << currentYR;
		currentXR -= 320;
		currentYR = -currentYR + 240;
		cout << " => " << currentXR << "," << currentYR;
	}
}






