#include "include.h"

#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"
#include "renderer.h"
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
	return 0;  // avoid unexpected error
	
}

void printVertexPos(glm::vec3 src) {
	cout << src.s << " , " << src.t;
}

int getObjNumber(int* posMatrix, int cellNumber) {
	return *(posMatrix + cellNumber);
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

int main() {

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

/*
	Vertex cellVertices[] = {
		glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.125f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.125f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.375f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.375f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.375f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.375f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.625f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.625f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.631f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.631f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.881f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.881f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(-0.131f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.119f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.125f, 0.508f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.125f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.375f, 0.508f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.375f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.375f, 0.508f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.375f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.625f, 0.508f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.625f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.631f, 0.508f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.631f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.881f, 0.508f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.881f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(-0.131f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(-0.131f, -0.167f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.119f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.119f, -0.167f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.125f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.125f, -0.167f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.375f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.375f, -0.167f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.375f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.375f, -0.167f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.625f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.625f, -0.167f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.631f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.631f, -0.167f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.881f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.881f, -0.167f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(-0.131f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(-0.131f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.119f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.119f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.125f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.125f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.375f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.375f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.375f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.375f, -0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.625f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.625f, -0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.631f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.631f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.881f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.881f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(-0.131f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(-0.131f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.119f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.119f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.125f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.125f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.375f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.375f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.375f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.375f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.625f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.625f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

glm::vec3(0.631f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.631f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.881f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.881f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

	};

	Vertex vertices[] = {
		// obj 0		
glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(-0.131f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.119f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 1		
glm::vec3(0.125f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.125f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.625f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.625f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 2		
glm::vec3(0.631f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.631f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.881f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.881f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 3		
glm::vec3(-0.131f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(-0.131f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.119f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.119f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 4		
glm::vec3(0.125f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.125f, -0.167f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.625f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.625f, -0.167f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 5		
glm::vec3(0.631f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.631f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.881f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.881f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 6		
glm::vec3(0.128f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.128f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.372f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.372f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 7		
glm::vec3(0.378f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.378f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.622f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.622f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 8		
glm::vec3(-0.128f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(-0.128f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.116f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.116f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 9		
glm::vec3(0.634f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(0.634f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.878f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(0.878f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 10		
glm::vec3(-0.225f, 0.958f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 0.767f),
glm::vec3(-0.225f, 0.833f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.717f),
glm::vec3(0.975f, 0.958f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.64f, 0.767f),
glm::vec3(0.975f, 0.833f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(0.64f, 0.717f),

// obj 11		
glm::vec3(-0.225f, 0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 0.717f),
glm::vec3(-0.225f, -0.833f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.05f),
glm::vec3(-0.131f, 0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.05f, 0.717f),
glm::vec3(-0.131f, -0.833f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(0.05f, 0.05f),

// obj 12		
glm::vec3(0.881f, 0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.59f, 0.717f),
glm::vec3(0.881f, -0.833f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.59f, 0.05f),
glm::vec3(0.975f, 0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.64f, 0.717f),
glm::vec3(0.975f, -0.833f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(0.64f, 0.05f),

// obj 13		
glm::vec3(-0.225f, -0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 0.05f),
glm::vec3(-0.225f, -0.958f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(0.119f, -0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.183f, 0.05f),
glm::vec3(0.119f, -0.958f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(0.183f, 0.0f),

// obj 14		
glm::vec3(0.634f, -0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.457f, 0.05f),
glm::vec3(0.634f, -0.958f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.457f, 0.0f),
glm::vec3(0.975f, -0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(0.64f, 0.05f),
glm::vec3(0.975f, -0.958f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(0.64f, 0.0f),

// obj 15 - logo		
glm::vec3(-0.844f, 0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(-0.844f, 0.333f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(-0.281f, 0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(-0.281f, 0.333f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 16 - undo		
glm::vec3(-0.813f, 0.313f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(-0.813f, -0.021f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(-0.313f, 0.313f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(-0.313f, -0.021f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 17 - reset		
glm::vec3(-0.813f, -0.083f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(-0.813f, -0.417f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(-0.313f, -0.083f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(-0.313f, -0.417f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
// obj 18 - exit	
glm::vec3(-0.813f, -0.479f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f),
glm::vec3(-0.813f, -0.813f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
glm::vec3(-0.313f, -0.479f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
glm::vec3(-0.313f, -0.813f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

	};

*/
Vertex vertices[19 * 4];
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

		// obj 14
		64, 65, 66,
		65, 66, 67,

		// obj 14
		68, 69, 70,
		69, 70, 71,

		// obj 14
		72, 73, 74,
		73, 74, 75,
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
	unsigned char* image0 = SOIL_load_image("../images/0_texture.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	
	GLuint texture0[10];

	glGenTextures(10, texture0);
	glBindTexture(GL_TEXTURE_2D, texture0[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (image0) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image0);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "ERROR::TEXTURE_LOADING_FAIL!" << endl;
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0[0]);
	SOIL_free_image_data(image0);

	unsigned char* image1 = SOIL_load_image("../images/1_texture.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, texture0[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (image1) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "ERROR::TEXTURE_LOADING_FAIL!" << endl;
	}	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture0[1]);
	SOIL_free_image_data(image1);


	unsigned char* image2 = SOIL_load_image("../images/2_texture.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, texture0[2]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (image2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "ERROR::TEXTURE_LOADING_FAIL!" << endl;
	}
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture0[2]);
	SOIL_free_image_data(image2);

	unsigned char* image3 = SOIL_load_image("../images/3_texture.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, texture0[3]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (image3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image3);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "ERROR::TEXTURE_LOADING_FAIL!" << endl;
	}
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture0[3]);
	SOIL_free_image_data(image3);

	unsigned char* image4 = SOIL_load_image("../images/4_texture.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, texture0[4]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (image4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image4);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "ERROR::TEXTURE_LOADING_FAIL!" << endl;
	}
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture0[4]);
	SOIL_free_image_data(image4);

	unsigned char* image5 = SOIL_load_image("../images/logo.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, texture0[5]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (image5) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image5);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "ERROR::TEXTURE_LOADING_FAIL!" << endl;
	}
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture0[5]);
	SOIL_free_image_data(image5);



	unsigned char* image6 = SOIL_load_image("../images/undo_button.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, texture0[6]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (image6) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image6);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "ERROR::TEXTURE_LOADING_FAIL!" << endl;
	}
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture0[6]);
	SOIL_free_image_data(image6);

	unsigned char* image7 = SOIL_load_image("../images/reset_button.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, texture0[7]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (image7) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image7);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "ERROR::TEXTURE_LOADING_FAIL!" << endl;
	}
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, texture0[7]);
	SOIL_free_image_data(image7);

	unsigned char* image8 = SOIL_load_image("../images/exit_button.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, texture0[8]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (image8) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image8);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "ERROR::TEXTURE_LOADING_FAIL!" << endl;
	}
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture0[8]);
	SOIL_free_image_data(image8);
	
	
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
			
			//start testing			

			cout << "\nstartCell = " << startCell;
			cout << "\nendCell = " << endCell;
			cout << "\nObjSelected = " << objNumber;

			if (objNumber == -1) // clicked on the empty cell
			{
				//  do something				
			}
				
			if (*(posMatrix + endCell) != -1) //endCell is not empty => do nothing
			{
				// so something
			}
				

			// looking for the first cell which contains the objSelected
			for (int i = 0; i < 20; i++) {				
				if (*(posMatrix + i) == objNumber) {
					startCell = i;
					cout << "\nstartCell updated to = " << startCell;
					i = 20;
				}
			}
				
			
			cout << "\n\nOld Position of Object " << objNumber << " is: ";
			printVertexPos(vertices[objNumber * 4].position);

			switch (objNumber) // which kind of object selected
			{
			case 1: //the red
				cout << "\nRed object Selected!";
				if (endCell == startCell + 2 || endCell == startCell + 6) //moving right
				{
					if (startCell % 4 == 2) break; // last column
					if (*(posMatrix + startCell + 2) != -1 || *(posMatrix + startCell + 6) != -1) //destination cells are not empty
						break;
					//commit the move
						//update 2 top corners
					vertices[objNumber * 4] = cellVertices[(startCell + 1) * 4];

					vertices[objNumber * 4 + 2] = cellVertices[(startCell + 2) * 4 + 2];

					//update 2 bottom corners

					vertices[objNumber * 4 + 1] = cellVertices[(startCell + 5) * 4 + 1];

					vertices[objNumber * 4 + 3] = cellVertices[(startCell + 6) * 4 + 3];

					//update posMatrix
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
					//commit the move
						//move 2 top corners
					vertices[objNumber * 4] = cellVertices[(startCell - 1) * 4];

					vertices[objNumber * 4 + 2] = cellVertices[startCell * 4 + 2];

					//move 2 bottom corners

					vertices[objNumber * 4 + 1] = cellVertices[(startCell + 3) * 4 + 1];

					vertices[objNumber * 4 + 3] = cellVertices[(startCell + 4) * 4 + 3];
					//update posMatrix
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

					//commit the move
						//move 2 top corners

					vertices[objNumber * 4] = cellVertices[(startCell - 4) * 4];

					vertices[objNumber * 4 + 2] = cellVertices[(startCell - 3) * 4 + 2];

					//move 2 bottom corners

					vertices[objNumber * 4 + 1] = cellVertices[startCell * 4 + 1];

					vertices[objNumber * 4 + 3] = cellVertices[(startCell + 1) * 4 + 3];
					//update posMatrix
					*(posMatrix + startCell + 4) = *(posMatrix + startCell + 5) = -1;
					*(posMatrix + startCell - 4) = *(posMatrix + startCell - 3) = objNumber;
					break;
				}
				if ((endCell == startCell + 8) || (endCell == startCell + 9)) //moving down
				{
					cout << "\nMoving down!";

					if (*(posMatrix + startCell + 8) != -1 || *(posMatrix + startCell + 9) != -1) //destination cells are not empty
						break;
					//commit the move
						//move 2 top corners
					vertices[objNumber * 4] = cellVertices[(startCell + 4) * 4];

					vertices[objNumber * 4 + 2] = cellVertices[(startCell + 5) * 4 + 2];

					//move 2 bottom corners

					vertices[objNumber * 4 + 1] = cellVertices[(startCell + 8) * 4 + 1];

					vertices[objNumber * 4 + 3] = cellVertices[(startCell + 9) * 4 + 3];
					//update posMatrix
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
					//commit the move
						//update 2 top corners
					vertices[objNumber * 4] = cellVertices[(startCell + 1) * 4];

					vertices[objNumber * 4 + 2] = cellVertices[(startCell + 2) * 4 + 2];

					//update 2 bottom corners

					vertices[objNumber * 4 + 1] = cellVertices[(startCell + 1) * 4 + 1];

					vertices[objNumber * 4 + 3] = cellVertices[(startCell + 2) * 4 + 3];

					//update posMatrix
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
					//commit the move
						//move 2 top corners
					vertices[objNumber * 4] = cellVertices[(startCell - 1) * 4];

					vertices[objNumber * 4 + 2] = cellVertices[startCell * 4 + 2];

					//move 2 bottom corners

					vertices[objNumber * 4 + 1] = cellVertices[(startCell - 1) * 4 + 1];

					vertices[objNumber * 4 + 3] = cellVertices[startCell * 4 + 3];
					//update posMatrix
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

					//commit the move
						//move 2 top corners

					vertices[objNumber * 4] = cellVertices[(startCell - 4) * 4];

					vertices[objNumber * 4 + 2] = cellVertices[(startCell - 3) * 4 + 2];

					//move 2 bottom corners

					vertices[objNumber * 4 + 1] = cellVertices[(startCell - 4) * 4 + 1];

					vertices[objNumber * 4 + 3] = cellVertices[(startCell - 3) * 4 + 3];
					//update posMatrix
					*(posMatrix + startCell) = *(posMatrix + startCell + 1) = -1;
					*(posMatrix + startCell - 4) = *(posMatrix + startCell - 3) = objNumber;
					break;
				}
				if ((endCell == startCell + 4) || (endCell == startCell + 5)) //moving down
				{
					cout << "\nMoving down!";
					
					if (*(posMatrix + startCell + 4) != -1 || *(posMatrix + startCell + 5) != -1) //destination cells are not empty
						break;
					//commit the move
						//move 2 top corners
					vertices[objNumber * 4] = cellVertices[(startCell + 4) * 4];

					vertices[objNumber * 4 + 2] = cellVertices[(startCell + 5) * 4 + 2];

					//move 2 bottom corners

					vertices[objNumber * 4 + 1] = cellVertices[(startCell + 4) * 4 + 1];

					vertices[objNumber * 4 + 3] = cellVertices[(startCell + 5) * 4 + 3];
					//update posMatrix
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
					//commit the move
						//update 2 top corners
					vertices[objNumber * 4] = cellVertices[(startCell + 1) * 4];
					
					vertices[objNumber * 4 + 2] = cellVertices[(startCell + 1) * 4 + 2];
					
					//update 2 bottom corners
					
					vertices[objNumber * 4 + 1] = cellVertices[(startCell + 5) * 4 + 1];
					
					vertices[objNumber * 4 + 3] = cellVertices[(startCell + 5) * 4 + 3];

					//update posMatrix
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
					//commit the move
						//move 2 top corners
					vertices[objNumber * 4] = cellVertices[(startCell - 1) * 4];
					
					vertices[objNumber * 4 + 2] = cellVertices[(startCell - 1) * 4 + 2];
					
					//move 2 bottom corners
					
					vertices[objNumber * 4 + 1] = cellVertices[(startCell + 3) * 4 + 1];
					
					vertices[objNumber * 4 + 3] = cellVertices[(startCell + 3) * 4 + 3];
					//update posMatrix
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

					//commit the move
						//move 2 top corners
					
					vertices[objNumber * 4] = cellVertices[(startCell - 4) * 4];
					
					vertices[objNumber * 4 + 2] = cellVertices[(startCell - 4) * 4 + 2];
					
					//move 2 bottom corners
					
					vertices[objNumber * 4 + 1] = cellVertices[startCell * 4 + 1];
					
					vertices[objNumber * 4 + 3] = cellVertices[startCell * 4 + 3];
					//update posMatrix
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
					//commit the move
						//move 2 top corners
					vertices[objNumber * 4] = cellVertices[(startCell + 4) * 4];
					
					vertices[objNumber * 4 + 2] = cellVertices[(startCell + 4) * 4 + 2];
					
					//move 2 bottom corners
					
					vertices[objNumber * 4 + 1] = cellVertices[(startCell + 8) * 4 + 1];
					
					vertices[objNumber * 4 + 3] = cellVertices[(startCell + 8) * 4 + 3];
					//update posMatrix
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
					
					if (*(posMatrix + startCell + 1 ) != -1) //destination cells are not empty
						break;
					
					//commit the move
					
					vertices[objNumber * 4] = cellVertices[(startCell + 1) * 4];
					vertices[objNumber * 4 + 1] = cellVertices[(startCell + 1) * 4 + 1];
					vertices[objNumber * 4 + 2] = cellVertices[(startCell + 1) * 4 + 2];
					vertices[objNumber * 4 + 3] = cellVertices[(startCell + 1) * 4 + 3];					

					//update posMatrix
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
					//commit the move
						//move 1st cell
					vertices[objNumber * 4] = cellVertices[(startCell - 1) * 4];
					vertices[objNumber * 4 + 1] = cellVertices[(startCell - 1) * 4 + 1];
					vertices[objNumber * 4 + 2] = cellVertices[(startCell - 1) * 4 + 2];
					vertices[objNumber * 4 + 3] = cellVertices[(startCell - 1) * 4 + 3];

					//update posMatrix
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
					//commit the move
						//move 1st cell
					vertices[objNumber * 4] = cellVertices[(startCell - 4) * 4];
					vertices[objNumber * 4 + 1] = cellVertices[(startCell - 4) * 4 + 1];
					vertices[objNumber * 4 + 2] = cellVertices[(startCell - 4) * 4 + 2];
					vertices[objNumber * 4 + 3] = cellVertices[(startCell - 4) * 4 + 3];

					//update posMatrix
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
					//commit the move
						//move 1st cell
					vertices[objNumber * 4] = cellVertices[(startCell + 4) * 4];
					vertices[objNumber * 4 + 1] = cellVertices[(startCell + 4) * 4 + 1];
					vertices[objNumber * 4 + 2] = cellVertices[(startCell + 4) * 4 + 2];
					vertices[objNumber * 4 + 3] = cellVertices[(startCell + 4) * 4 + 3];

					//update posMatrix
					posMatrix[startCell] = -1;
					posMatrix[startCell + 4] = objNumber;
					break;
				}
				break;
			default:
				break;
			}

			cout << "\n\nNew Position of Object " << objNumber << " is: ";
			printVertexPos(vertices[objNumber * 4].position);
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

		// draw	obj 0	

		// activate texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0[0]);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//draw obj 1
		glActiveTexture(1);
		glBindTexture(GL_TEXTURE_2D, texture0[1]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);
				
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(6 * sizeof(int)));

		//draw obj 2
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0[0]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(12 * sizeof(int)));


		//draw obj 3
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0[0]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(18 * sizeof(int)));

		//draw obj 4
		glActiveTexture(2);
		glBindTexture(GL_TEXTURE_2D, texture0[2]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(24 * sizeof(int)));

		//draw obj 5
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0[0]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(30 * sizeof(int)));

		//draw obj 6
		glActiveTexture(3);
		glBindTexture(GL_TEXTURE_2D, texture0[3]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(36 * sizeof(int)));

		//draw obj 7
		glActiveTexture(3);
		glBindTexture(GL_TEXTURE_2D, texture0[3]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(42 * sizeof(int)));

		//draw obj 8
		glActiveTexture(3);
		glBindTexture(GL_TEXTURE_2D, texture0[3]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(48 * sizeof(int)));

		//draw obj 9
		glActiveTexture(3);
		glBindTexture(GL_TEXTURE_2D, texture0[3]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(54 * sizeof(int)));

		//draw obj 10
		glActiveTexture(4);
		glBindTexture(GL_TEXTURE_2D, texture0[4]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(60 * sizeof(int)));

		//draw obj 11
		glActiveTexture(4);
		glBindTexture(GL_TEXTURE_2D, texture0[4]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(66 * sizeof(int)));

		//draw obj 12
		glActiveTexture(4);
		glBindTexture(GL_TEXTURE_2D, texture0[4]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(72 * sizeof(int)));

		//draw obj 13
		glActiveTexture(4);
		glBindTexture(GL_TEXTURE_2D, texture0[4]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(78 * sizeof(int)));

		//draw obj 14
		glActiveTexture(4);
		glBindTexture(GL_TEXTURE_2D, texture0[4]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(84 * sizeof(int)));

		//draw obj 15 - logo
		glActiveTexture(5);
		glBindTexture(GL_TEXTURE_2D, texture0[5]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(90 * sizeof(int)));

		//draw obj 16 - undo_button
		glActiveTexture(5);
		glBindTexture(GL_TEXTURE_2D, texture0[6]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(96 * sizeof(int)));

		//drawobj 17 - reset_button
		glActiveTexture(6);
		glBindTexture(GL_TEXTURE_2D, texture0[7]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(102 * sizeof(int)));

		//draw reset_button
		glActiveTexture(8);
		glBindTexture(GL_TEXTURE_2D, texture0[8]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(108 * sizeof(int)));


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
