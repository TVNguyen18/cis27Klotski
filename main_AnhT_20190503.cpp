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

int initialFlag = 1;

void movingObj(int* posMatrix, Vertex* vertices, Vertex* cellVertices, int startCell, int endCell) {
	
	int objSelected = *(posMatrix + startCell);
	if (objSelected == -1) // clicked on the empty cell
		return;
	if (*(posMatrix + endCell) != -1) //endCell is not empty => do nothing
		return;

	// looking for the first cell which contains the objSelected
	for(int i = 0; i < 20; i++)
		if ((*posMatrix + i) == objSelected) {
			startCell = i;
			i = 20;
		}
	cout << "\nStartCell = " << startCell;	

	switch (objSelected) // which kind of object selected
	{
	case 0:
	case 2:
	case 3:
	case 5: //the green obj
		if ((endCell == startCell + 1) || (endCell == startCell + 5)) //moving right
		{
			if (startCell % 4 == 3) return; // last column
			if((startCell + 1 != -1) || (startCell + 5 != -1)) //destination cells are not empty
				return;
			//commit the move
				//move 1st cell
			*(vertices + startCell * 4) = *(cellVertices + (startCell + 1) * 4);
			*(vertices + startCell * 4 + 1) = *(cellVertices + (startCell + 1) * 4 + 1);
			*(vertices + startCell * 4 + 2) = *(cellVertices + (startCell + 1) * 4 + 2);
			*(vertices + startCell * 4 + 3) = *(cellVertices + (startCell + 1) * 4 + 3);
				//move 2nd cell
			*(vertices + (startCell + 4) * 4) = *(cellVertices + (startCell + 5) * 4);
			*(vertices + (startCell + 4) * 4 + 1) = *(cellVertices + (startCell + 5) * 4 + 1);
			*(vertices + (startCell + 4) * 4 + 2) = *(cellVertices + (startCell + 5) * 4 + 2);
			*(vertices + (startCell + 4) * 4 + 3) = *(cellVertices + (startCell + 5) * 4 + 3);
			
			//update posMatrix
			*(posMatrix + startCell) = *(posMatrix + startCell + 4) = -1;
			*(posMatrix + startCell + 1) = *(posMatrix + startCell + 5) = objSelected;
			return;
		}
		if ((endCell == startCell - 1) || (endCell == startCell + 3)) //moving left
		{
			if (startCell % 4 == 0) return; // first column
			if ((startCell - 1 != -1) || (startCell + 3 != -1)) //destination cells are not empty
				return;
				//commit the move
					//move 1st cell
				*(vertices + startCell * 4) = *(cellVertices + (startCell - 1) * 4);
				*(vertices + startCell * 4 + 1) = *(cellVertices + (startCell - 1) * 4 + 1);
				*(vertices + startCell * 4 + 2) = *(cellVertices + (startCell - 1) * 4 + 2);
				*(vertices + startCell * 4 + 3) = *(cellVertices + (startCell - 1) * 4 + 3);
				//move 2nd cell
				*(vertices + (startCell + 4) * 4) = *(cellVertices + (startCell + 3) * 4);
				*(vertices + (startCell + 4) * 4 + 1) = *(cellVertices + (startCell + 3) * 4 + 1);
				*(vertices + (startCell + 4) * 4 + 2) = *(cellVertices + (startCell + 3) * 4 + 2);
				*(vertices + (startCell + 4) * 4 + 3) = *(cellVertices + (startCell + 3) * 4 + 3);
				//update posMatrix
				*(posMatrix + startCell) = *(posMatrix + startCell + 4) = -1;
				*(posMatrix + startCell - 1) = *(posMatrix + startCell + 3) = objSelected;
			return;
		}
		if ((endCell == startCell - 4) || (endCell == startCell - 8)) //moving up
		{
			if (startCell < 4) return; // first row
			if ((startCell - 4 != -1) || (startCell - 8 != -1)) //destination cells are not empty
				return;
				//commit the move
					//move 1st cell
				*(vertices + startCell * 4) = *(cellVertices + (startCell - 8) * 4);
				*(vertices + startCell * 4 + 1) = *(cellVertices + (startCell - 8) * 4 + 1);
				*(vertices + startCell * 4 + 2) = *(cellVertices + (startCell - 8) * 4 + 2);
				*(vertices + startCell * 4 + 3) = *(cellVertices + (startCell - 8) * 4 + 3);
				//move 2nd cell
				*(vertices + (startCell + 4) * 4) = *(cellVertices + (startCell - 4) * 4);
				*(vertices + (startCell + 4) * 4 + 1) = *(cellVertices + (startCell - 4) * 4 + 1);
				*(vertices + (startCell + 4) * 4 + 2) = *(cellVertices + (startCell - 4) * 4 + 2);
				*(vertices + (startCell + 4) * 4 + 3) = *(cellVertices + (startCell - 4) * 4 + 3);
				//update posMatrix
				*(posMatrix + startCell) = *(posMatrix + startCell + 4) = -1;
				*(posMatrix + startCell - 4) = *(posMatrix + startCell - 8) = objSelected;
			return;
		}
		if ((endCell == startCell + 8) || (endCell == startCell + 12)) //moving down
		{
			if (startCell > 15) return; // last row
			if ((startCell + 8 != -1) || (startCell + 12 != -1)) //destination cells are not empty
				return;
			//commit the move
				//move 1st cell
			*(vertices + startCell * 4) = *(cellVertices + (startCell + 8) * 4);
			*(vertices + startCell * 4 + 1) = *(cellVertices + (startCell + 8) * 4 + 1);
			*(vertices + startCell * 4 + 2) = *(cellVertices + (startCell + 8) * 4 + 2);
			*(vertices + startCell * 4 + 3) = *(cellVertices + (startCell + 8) * 4 + 3);
			//move 2nd cell
			*(vertices + (startCell + 4) * 4) = *(cellVertices + (startCell + 12) * 4);
			*(vertices + (startCell + 4) * 4 + 1) = *(cellVertices + (startCell + 12) * 4 + 1);
			*(vertices + (startCell + 4) * 4 + 2) = *(cellVertices + (startCell + 12) * 4 + 2);
			*(vertices + (startCell + 4) * 4 + 3) = *(cellVertices + (startCell + 12) * 4 + 3);
			//update posMatrix
			*(posMatrix + startCell) = *(posMatrix + startCell + 4) = -1;
			*(posMatrix + startCell + 8) = *(posMatrix + startCell + 12) = objSelected;
			return;
		}
		break;
	case 6: // blue obj
	case 7:
	case 8:
	case 9:
		cout << "\nCase 6, 7, 8, 9";
		if (endCell == startCell + 1) //moving right
		{
			if (startCell % 4 == 3) return; // last column
			if (startCell + 1 != -1) //destination cells are not empty
				return;
			//commit the move
				//move 1st cell
			*(vertices + startCell * 4) = *(cellVertices + (startCell + 1) * 4);
			*(vertices + startCell * 4 + 1) = *(cellVertices + (startCell + 1) * 4 + 1);
			*(vertices + startCell * 4 + 2) = *(cellVertices + (startCell + 1) * 4 + 2);
			*(vertices + startCell * 4 + 3) = *(cellVertices + (startCell + 1) * 4 + 3);			

			//update posMatrix
			*(posMatrix + startCell) = -1;
			*(posMatrix + startCell + 1) = objSelected;
			return;
		}
		if (endCell == startCell - 1) //moving left
		{
			if (startCell % 4 == 0) return; // first column
			if (startCell - 1 != -1)  //destination cells are not empty
				return;
			//commit the move
				//move 1st cell
			*(vertices + startCell * 4) = *(cellVertices + (startCell - 1) * 4);
			*(vertices + startCell * 4 + 1) = *(cellVertices + (startCell - 1) * 4 + 1);
			*(vertices + startCell * 4 + 2) = *(cellVertices + (startCell - 1) * 4 + 2);
			*(vertices + startCell * 4 + 3) = *(cellVertices + (startCell - 1) * 4 + 3);
			
			//update posMatrix
			*(posMatrix + startCell) = -1;
			*(posMatrix + startCell - 1) = objSelected;
			return;
		}
		if (endCell == startCell - 4)  //moving up
		{
			if (startCell < 4) return; // first row
			if (startCell - 4 != -1) //destination cells are not empty
				return;
			//commit the move
				//move 1st cell
			*(vertices + startCell * 4) = *(cellVertices + (startCell - 8) * 4);
			*(vertices + startCell * 4 + 1) = *(cellVertices + (startCell - 4) * 4 + 1);
			*(vertices + startCell * 4 + 2) = *(cellVertices + (startCell - 4) * 4 + 2);
			*(vertices + startCell * 4 + 3) = *(cellVertices + (startCell - 4) * 4 + 3);
			
			//update posMatrix
			*(posMatrix + startCell) = -1;
			*(posMatrix + startCell - 4) = objSelected;
			return;
		}
		if (endCell == startCell + 4) //moving down
		{
			if (startCell > 15) return; // last row
			if (startCell + 8 != -1) //destination cells are not empty
				return;
			//commit the move
				//move 1st cell
			*(vertices + startCell * 4) = *(cellVertices + (startCell + 4) * 4);
			*(vertices + startCell * 4 + 1) = *(cellVertices + (startCell + 4) * 4 + 1);
			*(vertices + startCell * 4 + 2) = *(cellVertices + (startCell + 4) * 4 + 2);
			*(vertices + startCell * 4 + 3) = *(cellVertices + (startCell + 4) * 4 + 3);
			
			//update posMatrix
			*(posMatrix + startCell) = -1;
			*(posMatrix + startCell + 4) = objSelected;
			return;
		}
		break;
	default:
		break;
	}
}

int getCellNumber(int xpos, int ypos) {
	if (xpos > 41 && xpos < 119 && ypos> -120 && ypos < -42)
		return 13;
	if (xpos > 121 && xpos < 199 && ypos > -120 && ypos < -42)
		return 14;

	if (xpos > -41 && xpos < 37 && ypos> -201 && ypos < -123)
		return 16;
	if (xpos > 41 && xpos < 119 && ypos > -201 && ypos < -123)
		return 17;
	if (xpos > 121 && xpos < 199 && ypos > -199 && ypos < -121)
		return 18;
	if (xpos > 203 && xpos < 281 && ypos > -199 && ypos < -121)
		return 19;
	
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
int canMove(int* posMatrix, int startCell, int endCell) {
	int movDirection = getMovingDirection(startCell, endCell);
	if (movDirection == 0)
		return 0;
	if (getObjNumber(posMatrix, endCell) != -1) // end cell is not empty
		return 0;
	
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 4; j++) {
			if ((i * 4 + j) == startCell) {
				switch (movDirection) {
				case 2: //move down
					if (i == 4) return 0;	//last row				
					return 1;
					break;

				case 4: //moving to the left
					if (j == 0) return 0; //fisrt column
					return 1;					
					break;

				case 6: //moving to the right
					if (j == 3) return 0; //last column
					return 1;					
					break;
				
				case 8: //move up
					if (i == 0) return 0; //first row
					return 1;
					break;				
				}
			}
		}
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
	Vertex* cellVertices = new Vertex[14 * 4];
	*(cellVertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.131f, 0.508f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.508f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.131f, 0.508f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.508f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.131f, 0.508f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.508f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.131f, 0.508f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.508f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.131f, 0.508f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.508f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.131f, 0.508f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.508f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.131f, 0.508f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.508f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.131f, 0.508f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.508f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.131f, 0.508f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.508f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.131f, 0.508f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.508f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.131f, 0.508f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.508f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.131f, 0.508f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.119f, 0.508f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(0.128f, -0.175f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.128f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.372f, -0.175f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.372f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(0.378f, -0.175f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.378f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.622f, -0.175f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.622f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(0.244f, 0.508f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.344f, 0.442f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.444f, 0.375f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.544f, 0.308f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(-0.128f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(-0.128f, -0.838f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.116f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.116f, -0.838f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(0.128f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.128f, -0.838f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.372f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.372f, -0.838f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(0.378f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.378f, -0.838f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.622f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.622f, -0.838f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	*(cellVertices) = { glm::vec3(0.634f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.634f, -0.838f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	*(cellVertices) = { glm::vec3(0.878f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
	*(cellVertices) = { glm::vec3(0.878f, -0.838f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };


	/*
		{glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//1
	{glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//2
	{glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//3
	{glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//4
	{glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//5
	{glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//6
	{glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//7
	{glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//8
	{glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//9
	{glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//10
	{glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//11
	{glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(-0.131f, 0.508f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.119f, 0.508f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//12
	{glm::vec3(0.128f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(0.128f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.372f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.372f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},


		//13
	{glm::vec3(0.128f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(0.128f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.372f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.372f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},


		//14
	{glm::vec3(0.378f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(0.378f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.622f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.622f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},


		//15
	{glm::vec3(0.458f, 0.365f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{glm::vec3(0.503f, 0.336f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f)},
	{glm::vec3(0.547f, 0.306f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	{glm::vec3(0.591f, 0.277f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f)},

		//16
		{glm::vec3(-0.128f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f)},
	{ glm::vec3(-0.128f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(0.116f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(0.116f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f) },

		//17
	{ glm::vec3(0.128f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(0.128f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(0.372f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(0.372f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f) },

	{ glm::vec3(0.378f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(0.378f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(0.622f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(0.622f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f) },

	{ glm::vec3(0.634f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),	glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(0.634f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(0.878f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(0.878f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f) }

	};
	*/
Vertex* vertices = new Vertex[20 * 4];
*(vertices) = { glm::vec3(-0.131f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(-0.131f, 0.175f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(0.119f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(0.119f, 0.175f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(0.125f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(0.125f, 0.175f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(0.625f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(0.625f, 0.175f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(0.631f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(0.631f, 0.175f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(0.881f, 0.842f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(0.881f, 0.175f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(-0.131f, 0.167f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(-0.131f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(0.119f, 0.167f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(0.119f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(0.125f, 0.167f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(0.125f, -0.167f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(0.625f, 0.167f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(0.625f, -0.167f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(0.631f, 0.167f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(0.631f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(0.881f, 0.167f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(0.881f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(0.128f, -0.175f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(0.128f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(0.372f, -0.175f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(0.372f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(0.378f, -0.175f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(0.378f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(0.622f, -0.175f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(0.622f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(-0.128f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(-0.128f, -0.838f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(0.116f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(0.116f, -0.838f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(0.634f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(0.634f, -0.838f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(0.878f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(0.878f, -0.838f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(-0.844f, 0.833f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(-0.844f, 0.333f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(-0.281f, 0.833f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(-0.281f, 0.333f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(-0.813f, 0.313f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(-0.813f, -0.021f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(-0.313f, 0.313f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(-0.313f, -0.021f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(-0.813f, -0.083f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(-0.813f, -0.417f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(-0.313f, -0.083f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(-0.313f, -0.417f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };

*(vertices) = { glm::vec3(-0.813f, -0.479f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f), };
*(vertices) = { glm::vec3(-0.813f, -0.813f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), };
*(vertices) = { glm::vec3(-0.313f, -0.479f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), };
*(vertices) = { glm::vec3(-0.313f, -0.813f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), };


/*
{
		//obj0
		glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.131f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.119f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj1
		glm::vec3(0.125f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.125f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.625f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.625f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj2
		glm::vec3(0.631f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.631f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.881f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.881f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj3
		glm::vec3(-0.131f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.131f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.119f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.119f, -0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj4
		glm::vec3(0.125f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.125f, -0.167f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.625f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.625f, -0.167f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj5
		glm::vec3(0.631f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.631f, -0.5f, 0.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.881f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.881f, -0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj6
		glm::vec3(0.128f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.128f, -0.5f, 0.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.372f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.372f, -0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj7
		glm::vec3(0.378f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.378f, -0.5f, 0.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.622f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.622f, -0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj8
		glm::vec3(-0.128f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.128f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.116f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.116f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj9
		glm::vec3(0.634f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.634f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.878f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.878f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj10 - logo
		glm::vec3(-0.844f, 0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.844f, 0.333f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(-0.281f, 0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(-0.281f, 0.333f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj11 - undo
		glm::vec3(-0.813f, 0.313f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.813f, -0.021f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(-0.313f, 0.313f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(-0.313f, -0.021f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj12 - reset
		glm::vec3(-0.813f, -0.083f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.813f, -0.417f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(-0.313f, -0.083f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(-0.313f, -0.417f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		//obj13 - exit
		glm::vec3(-0.813f, -0.479f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.813f, -0.813f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(-0.313f, -0.479f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(-0.313f, -0.813f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
	};
	*/
	
	GLuint indices[] = {
		// obj 1
		0, 1, 2,
		1, 2, 3,

		// obj 2
		4, 5, 6,
		5, 6, 7,

		// obj 3
		8, 9, 10,
		9, 10, 11,

		// obj 4
		12, 13, 14,
		13, 14, 15,

		// obj 5
		16, 17, 18,
		17, 18, 19,

		// obj 6
		20, 21, 22,
		21, 22, 23,

		// obj 7
		24, 25, 26,
		25, 26, 27,

		// obj 8
		28, 29, 30,
		29, 30, 31,

		// obj 9
		32, 33, 34,
		33, 34, 35,

		// obj 10
		36, 37, 38,
		37, 38, 39,

		// obj 11
		40, 41, 42,
		41, 42, 43,

		// obj 12
		44, 45, 46,
		45, 46, 47,

		// obj 13
		48, 49, 50,
		49, 50, 51,

		// obj 12
		52, 53, 54,
		53, 54, 55,
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
		56 * sizeof(Vertex),
		vertices,
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

	unsigned char* image4 = SOIL_load_image("../images/logo.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
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
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture0[4]);
	SOIL_free_image_data(image4);

	unsigned char* image5 = SOIL_load_image("../images/undo_button.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
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
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture0[5]);
	SOIL_free_image_data(image5);

	unsigned char* image6 = SOIL_load_image("../images/reset_button.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
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
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, texture0[6]);
	SOIL_free_image_data(image6);

	unsigned char* image7 = SOIL_load_image("../images/exit_button.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
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
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture0[7]);
	SOIL_free_image_data(image7);
	
	
	while (!glfwWindowShouldClose(window)) {

		// Update input
		glfwPollEvents();

		glfwSetMouseButtonCallback(window, mouse_button_callback);	

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && currentX != -1) {
			
			int startCell = getCellNumber(currentX, currentY);
			int endCell = getCellNumber(currentXR, currentYR);
			int objNumber = getObjNumber(posMatrix, startCell);
			movingObj(posMatrix, vertices, cellVertices, startCell, endCell);
			/*
			if(canMove(posMatrix, startCell, endCell))
			{				
				int movDirection = getMovingDirection(startCell, endCell);
				cout << "\n\nStartCell = " << startCell
					<< "\nEndCell = " << endCell
					<< "\nObject Selected = " << objNumber;
				switch (movDirection) {
				case 2:
					cout << "\nMoving direction: down";
					break;
				case 4:
					cout << "\nMoving direction: left";
					break;
				case 6:
					cout << "\nMoving direction: right";
					break;
				case 8:
					cout << "\nMoving direction: up";
					break;
				default:
					cout << "\nMoving out of range";
					break;
				}
				//move object to a new position
				cout << "\n\nOld Position of Object " << objNumber << " is: ";
				printVertexPos(vertices[objNumber * 4].position);
				cout << "\n\nNew Position of Object " << objNumber << " is: ";
				printVertexPos(cellVertices[endCell * 4].position);
	
				vertices[objNumber * 4] = cellVertices[endCell * 4];
				vertices[objNumber * 4 + 1] = cellVertices[endCell * 4 + 1];
				vertices[objNumber * 4 + 2] = cellVertices[endCell * 4 + 2];
				vertices[objNumber * 4 + 3] = cellVertices[endCell * 4 + 3];

				//update vertex buffer
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER,
					sizeof(vertices),
					&vertices[0],
					GL_STATIC_DRAW);

				//update position matrix
				// set 0 for the empty cell
				for (int i = 0; i < 20; i++)
					if (*(posMatrix + i) == objNumber)
						*(posMatrix + i) = -1;
				// set objNumber for endCell							
				*(posMatrix + endCell) = objNumber;

				for (int i = 0; i < 5; i++) {
					cout << "\n";
					for (int j = 0; j < 4; j++) {
						cout << *(posMatrix + i * 4 + j) << " ";
					}
				}

			}
			*/
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

		// draw	1st obj	

		// activate texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0[0]);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//draw 2nd obj
		glActiveTexture(1);
		glBindTexture(GL_TEXTURE_2D, texture0[1]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);
				
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(6 * sizeof(int)));

		//draw 3rd obj
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0[0]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(12 * sizeof(int)));


		//draw 4th obj
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0[0]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(18 * sizeof(int)));

		//draw 5th obj
		glActiveTexture(2);
		glBindTexture(GL_TEXTURE_2D, texture0[2]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(24 * sizeof(int)));

		//draw 6th obj
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0[0]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(30 * sizeof(int)));

		//draw 7th obj
		glActiveTexture(3);
		glBindTexture(GL_TEXTURE_2D, texture0[3]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(36 * sizeof(int)));

		//draw 8th obj
		glActiveTexture(3);
		glBindTexture(GL_TEXTURE_2D, texture0[3]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(42 * sizeof(int)));

		//draw 9th obj
		glActiveTexture(3);
		glBindTexture(GL_TEXTURE_2D, texture0[3]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(48 * sizeof(int)));

		//draw 10th obj
		glActiveTexture(3);
		glBindTexture(GL_TEXTURE_2D, texture0[3]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(54 * sizeof(int)));

		//draw logo
		glActiveTexture(4);
		glBindTexture(GL_TEXTURE_2D, texture0[4]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(60 * sizeof(int)));

		//draw undo_button
		glActiveTexture(5);
		glBindTexture(GL_TEXTURE_2D, texture0[5]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(66 * sizeof(int)));

		//draw reset_button
		glActiveTexture(6);
		glBindTexture(GL_TEXTURE_2D, texture0[6]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(72 * sizeof(int)));

		//draw reset_button
		glActiveTexture(7);
		glBindTexture(GL_TEXTURE_2D, texture0[7]);

		glUniform1i(glGetUniformLocation(shaderProgramID, "my_Texture"), 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(78 * sizeof(int)));


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
