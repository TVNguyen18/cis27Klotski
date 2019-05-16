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

double currentX;
double currentY;

double currentXR;
double currentYR;

int initialFlag = 1;

int getCellNumber(int xpos, int ypos) {

	if (xpos > -41 && xpos < 37 && ypos> -201 && ypos < -123)
		return 16;
	if (xpos > 41 && xpos < 119 && ypos > -201 && ypos < -123)
		return 17;
	if (xpos > 121 && xpos < 199 && ypos> -201 && ypos < -123)
		return 18;
	if (xpos > 281 && xpos < 203 && ypos > -201 && ypos < -123)
		return 19;
}

int isBelongTo(int xpos, int ypos, int cellNumber) {
	switch (cellNumber) {
	case 0:
		
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
	case 13:
		break;
	case 14:
		break;
	case 15:
		break;
	case 16:
		if (xpos > -41 && xpos < 37 && ypos> -201 && ypos < -123)
			return 1;
		break;
	case 17:
		if (xpos > 41 && xpos < 119 && ypos > -201 && ypos < -123)
			return 1;
		break;
	case 18:
		if (xpos > 121 && xpos < 199 && ypos > -199 && ypos < -121)
			return 1;
		break;
	case 19:
		break;
	case 20:
		break;
	default:
		break;
	}
	return 0;
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

	Vertex vertices[] = {
		glm::vec3(-0.131f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.131f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.119f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.119f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		
		glm::vec3(0.125f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.125f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.625f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.625f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		
		glm::vec3(0.631f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.631f, 0.175f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.881f, 0.842f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.881f, 0.175f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		
		glm::vec3(-0.131f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.131f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.119f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.119f, -0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		
		glm::vec3(0.125f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.125f, -0.167f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.625f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.625f, -0.167f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		
		glm::vec3(0.631f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.631f, -0.5f, 0.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.881f, 0.167f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.881f, -0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		
		glm::vec3(0.128f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.128f, -0.5f, 0.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.372f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.372f, -0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		
		glm::vec3(0.378f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.378f, -0.5f, 0.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.622f, -0.175f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.622f, -0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		
		glm::vec3(-0.128f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.128f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.116f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.116f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
		
		glm::vec3(0.634f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(0.634f, -0.838f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(0.878f, -0.513f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(0.878f, -0.838f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

		glm::vec3(-0.844f, 0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.844f, 0.333f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(-0.281f, 0.833f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(-0.281f, 0.333f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

		glm::vec3(-0.813f, 0.313f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.813f, -0.021f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(-0.313f, 0.313f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(-0.313f, -0.021f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

		glm::vec3(-0.813f, -0.083f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.813f, -0.417f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(-0.313f, -0.083f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(-0.313f, -0.417f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),

		glm::vec3(-0.813f, -0.479f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0),		glm::vec2(0.0f, 1.0f),
		glm::vec3(-0.813f, -0.813f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),
		glm::vec3(-0.313f, -0.479f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),
		glm::vec3(-0.313f, -0.813f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f),
	};
	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
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

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			
			//if (currentX > -41 && currentX < 37 && currentY> -201 && currentY < -123)
			if(isBelongTo(currentX, currentY, 16))
			{

				if (isBelongTo(currentXR, currentYR, 17))
				{
					vertices[32] = { glm::vec3(0.128f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
					vertices[33] = { glm::vec3(0.128f, -0.838f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
					vertices[34] = { glm::vec3(0.372f, -0.513f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
					vertices[35] = { glm::vec3(0.372f, -0.838f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

					glBindBuffer(GL_ARRAY_BUFFER, VBO);
					glBufferData(GL_ARRAY_BUFFER,
						sizeof(vertices),
						&vertices[0],
						GL_STATIC_DRAW);
				}

			}
			if (isBelongTo(currentX, currentY, 17))
			{

				if (isBelongTo(currentXR, currentYR, 18))
				{
					vertices[32] = { glm::vec3(0.378f, -0.504f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0), glm::vec2(0.0f, 1.0f) };
					vertices[33] = { glm::vec3(0.378f, -0.829f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
					vertices[34] = { glm::vec3(0.622f, -0.504f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) };
					vertices[35] = { glm::vec3(0.622f, -0.829f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };
					
					glBindBuffer(GL_ARRAY_BUFFER, VBO);
					glBufferData(GL_ARRAY_BUFFER,
						sizeof(vertices),
						&vertices[0],
						GL_STATIC_DRAW);
						
				}

			}
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
