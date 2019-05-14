#include "include.h"

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;
GLFWwindow* window;

double currentX = -1;
double currentY = 0;

double currentXR = 0;
double currentYR = 0;

int initialFlag = -1;

int getCellNumber(int xpos, int ypos) {

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

	if (xpos > -260 && xpos < -100 && ypos > -5 && ypos < 75) //undo
		return 20;

	if (xpos > -260 && xpos < -100 && ypos > -100 && ypos < -20) //reset
		return 21;

	if (xpos > -260 && xpos < -100 && ypos > -195 && ypos < -115) //exit
		return 22;

	return 50;  // out of range

}

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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		cout << "\nLeft click!";
		glfwGetCursorPos(window, &currentX, &currentY);
		cout << "\n" << currentX << "," << currentY;
		currentX -= 320;
		currentY = -currentY + 240;
		cout << " => " << currentX << "," << currentY;
		initialFlag = 1;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		cout << "\nLeft release!";
		glfwGetCursorPos(window, &currentXR, &currentYR);
		cout << "\n" << currentXR << "," << currentYR;
		currentXR -= 320;
		currentYR = -currentYR + 240;
		cout << " => " << currentXR << "," << currentYR;
	}
}

bool init();
void displayVersion();

string readShaderSource(string);
bool compileShader(GLuint);


int uniformLocation;

glm::vec3 translate(glm::vec3, GLfloat, GLfloat, GLfloat);
glm::vec3 scale(glm::vec3, GLfloat, GLfloat, GLfloat);
glm::vec3 rotate(glm::vec3, GLfloat, GLfloat, GLfloat, GLfloat);

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
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

	if (init() == false) {
		return 1;
	}

	displayVersion();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	string vertexSrc = readShaderSource("../vertex_shader.shader");
	string fragmentSrc = readShaderSource("../fragment_shader.shader");

	const char* vertexCSrc = vertexSrc.c_str();
	const char* fragmentCSrc = fragmentSrc.c_str();

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textCoord));
	glEnableVertexAttribArray(2);

	// bind VAO 0
	glBindVertexArray(0);




	// texture 1	

	int imageWidth = 0;
	int imageHeight = 0;
	int objNumber;
	GLuint texture0[10];
	int i;

	glGenTextures(10, texture0);

	unsigned char* green = SOIL_load_image("../images/0_texture.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture0, green, 0, imageWidth, imageHeight);

	unsigned char* red = SOIL_load_image("../images/1_texture.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture0, red, 1, imageWidth, imageHeight);

	unsigned char* yellow = SOIL_load_image("../images/2_texture.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture0, yellow, 2, imageWidth, imageHeight);

	unsigned char* blue = SOIL_load_image("../images/3_texture.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture0, blue, 3, imageWidth, imageHeight);

	unsigned char* background = SOIL_load_image("../images/4_texture.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture0, background, 4, imageWidth, imageHeight);

	unsigned char* logo = SOIL_load_image("../images/logo.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture0, logo, 5, imageWidth, imageHeight);

	unsigned char* undoButton = SOIL_load_image("../images/undo_button.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture0, undoButton, 6, imageWidth, imageHeight);

	unsigned char* resetButton = SOIL_load_image("../images/reset_button.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture0, resetButton, 7, imageWidth, imageHeight);

	unsigned char* exitButton = SOIL_load_image("../images/exit_button.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture0, exitButton, 8, imageWidth, imageHeight);

	unsigned char* exit = SOIL_load_image("../images/exit_texture.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	loadTexture(texture0, exit, 9, imageWidth, imageHeight);


	while (!glfwWindowShouldClose(window)) {

		// Update input
		glfwPollEvents();

		glfwSetMouseButtonCallback(window, mouse_button_callback);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && initialFlag != -1) {

			int startCell = getCellNumber(currentX, currentY);
			int endCell = getCellNumber(currentXR, currentYR);
			int objNumber = getObjNumber(posMatrix, startCell);

			//reset the flag
			initialFlag = -1;

			if (objNumber == -1) // clicked on the empty cell
			{
				//  put the out of range value for objNumber
				objNumber = 50;
			}

			if (*(posMatrix + endCell) != -1) //endCell is not empty => do nothing
			{
				// do something
			}

			//start testing			

			cout << "\nstartCell = " << startCell;
			cout << "\nendCell = " << endCell;
			cout << "\nObjSelected = " << objNumber;

			// looking for the first cell which contains the objSelected
			for (int i = 0; i < 20; i++) {
				if (*(posMatrix + i) == objNumber) {
					startCell = i;
					cout << "\nstartCell updated to = " << startCell;
					i = 20;
				}
			}

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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
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
					positionStack.push(posMatrix);
					posMatrix[startCell] = -1;
					posMatrix[startCell + 4] = objNumber;
					break;
				}
				break;
			case 20: //Undo
				if (!positionStack.isEmpty()) {
					delete[] posMatrix;
					posMatrix = positionStack.pop();
				}
				break;
			case 21: //reset
				while (!positionStack.isEmpty()) {
					delete[] posMatrix;
					posMatrix = positionStack.pop();
				}
				break;
			case 22:
				exitFlag = 1;
				break;
			default:
				// out of range
				break;
			}

			//update vertices
			updateVertexAray(vertices, cellVertices, posMatrix);

			if (objNumber < 20) {
				cout << "\n\nNew Position of Object " << objNumber << " is: ";
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


			//end testing

		}


		// clear
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// use a program
		glUseProgram(shaderProgramID);

		// bind VAO
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);

		// set up uniform
		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		if (exitFlag) {
			// activate texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture0[9]);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(114 * sizeof(int)));

		} else {
            bindAndDrawTexture(texture0, shaderProgramID);
		}



		//clean up


		glDisableVertexAttribArray(0);

		glUseProgram(0);

		glfwSwapBuffers(window);
		glFlush();

	}


	glfwTerminate();

	return 0;
}





bool init() {
	if (glfwInit() == false) {
		cout << "\nCould not init GLFW" << endl;
		return false;
	}
	cout << "\nGLFW initialized" << endl;
	window = glfwCreateWindow(WIDTH, HEIGHT, "Klotski - Group #6", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		cout << "\nCould not init GLEW" << endl;
		return false;
	}
	cout << "\nGLEW initialized" << endl;

	return true;
}

void displayVersion() {
	const unsigned char* version = glGetString(GL_VERSION);
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);

	cout << "\nOpenGL Version: " << version
		<< "\nOpenGL Renderer: " << renderer
		<< "\nOpenGL Vendor: " << vendor << endl;
}
string readShaderSource(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

bool compileShader(GLuint shaderID) {
	int result = -1;
	int maxLengh = 2048;
	int realLength = 0;
	char errLog[2048];

	cout << "Compiling shader " << shaderID << "..." << endl;
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		cout << "Shader " << shaderID << "compiled fail!" << endl;
		glGetShaderInfoLog(shaderID, maxLengh, &realLength, errLog);
		cout << errLog << endl;
		return false;
	}
	cout << "Shader " << shaderID << " compiled successful!" << endl;
	return true;
}

glm::vec3 translate(glm::vec3 vertex, GLfloat x, GLfloat y, GLfloat z) {
	glm::vec4 translatedVertex = glm::vec4(vertex, 1.0);
	translatedVertex = translatedVertex * glm::mat4(1.0f, 0.0f, 0.0f, x,
		0.0f, 1.0f, 0.0f, y,
		0.0f, 0.0f, 1.0f, z,
		0.0f, 0.0f, 0.0f, 1.0f);
	return glm::vec3(translatedVertex[0], translatedVertex[1], translatedVertex[2]);
}

glm::vec3 scale(glm::vec3 vertex, GLfloat x, GLfloat y, GLfloat z) {
	glm::vec4 scaledVertex = glm::vec4(vertex, 1.0);
	scaledVertex = scaledVertex * glm::mat4(x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	return glm::vec3(scaledVertex[0], scaledVertex[1], scaledVertex[2]);
}

glm::vec3 rotate(glm::vec3 vertex, GLfloat degree, GLfloat x, GLfloat y, GLfloat z) {
	GLfloat radians = glm::radians(degree);
	glm::vec4 rotatedVertex = glm::vec4(vertex, 1.0);

	glm::mat4 rotateX = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(radians), -sin(radians), 0.0f,
		0.0f, sin(radians), cos(radians), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 rotateY = glm::mat4(cos(radians), 0.0f, sin(radians), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sin(radians), 0.0f, cos(radians), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 rotateZ = glm::mat4(cos(radians), -sin(radians), 0.0f, 0.0f,
		sin(radians), cos(radians), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	if (x == 1.0f)
		rotatedVertex = rotatedVertex * rotateX;
	if (y == 1.0f)
		rotatedVertex = rotatedVertex * rotateY;
	if (z == 1.0f)
		rotatedVertex = rotatedVertex * rotateZ;
	return glm::vec3(rotatedVertex[0], rotatedVertex[1], rotatedVertex[2]);
}
