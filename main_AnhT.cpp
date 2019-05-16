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
		
	GLuint textureVBO;
	vector<glm::vec2> texturePosition{
		glm::vec2(-1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f)
	};
	GLuint textureIndices[] = {
		0, 1, 2,
		1, 2, 3
	};

	vector<glm::vec3> position{
		// obj 1
		glm::vec3(-0.131f, 0.842f, 0.0f),
		glm::vec3(-0.131f, 0.175f, 0.0f),
		glm::vec3(0.119f, 0.842f, 0.0f),
		glm::vec3(0.119f, 0.175f, 0.0f),

		// obj 2
		glm::vec3(0.125f, 0.842f, 0.0f),
		glm::vec3(0.125f, 0.175f, 0.0f),
		glm::vec3(0.625f, 0.842f, 0.0f),
		glm::vec3(0.625f, 0.175f, 0.0f),

		// obj 3
		glm::vec3(0.631f, 0.842f, 0.0f),
		glm::vec3(0.631f, 0.175f, 0.0f),
		glm::vec3(0.881f, 0.842f, 0.0f),
		glm::vec3(0.881f, 0.175f, 0.0f),

		// obj 4
		glm::vec3(-0.131f, 0.167f, 0.0f),
		glm::vec3(-0.131f, -0.5f, 0.0f),
		glm::vec3(0.119f, 0.167f, 0.0f),
		glm::vec3(0.119f, -0.5f, 0.0f),

		// obj 5
		glm::vec3(0.125f, 0.167f, 0.0f),
		glm::vec3(0.125f, -0.167f, 0.0f),
		glm::vec3(0.625f, 0.167f, 0.0f),
		glm::vec3(0.625f, -0.167f, 0.0f),

		// obj 6
		glm::vec3(0.631f, 0.167f, 0.0f),
		glm::vec3(0.631f, -0.5f, 0.0f),
		glm::vec3(0.881f, 0.167f, 0.0f),
		glm::vec3(0.881f, -0.5f, 0.0f),

		// obj 7
		glm::vec3(0.128f, -0.175f, 0.0f),
		glm::vec3(0.128f, -0.5f, 0.0f),
		glm::vec3(0.372f, -0.175f, 0.0f),
		glm::vec3(0.372f, -0.5f, 0.0f),

		// obj 8
		glm::vec3(0.378f, -0.175f, 0.0f),
		glm::vec3(0.378f, -0.5f, 0.0f),
		glm::vec3(0.622f, -0.175f, 0.0f),
		glm::vec3(0.622f, -0.5f, 0.0f),

		// obj 9
		glm::vec3(-0.128f, -0.513f, 0.0f),
		glm::vec3(-0.128f, -0.838f, 0.0f),
		glm::vec3(0.116f, -0.513f, 0.0f),
		glm::vec3(0.116f, -0.838f, 0.0f),

		// obj 10
		glm::vec3(0.634f, -0.513f, 0.0f),
		glm::vec3(0.634f, -0.838f, 0.0f),
		glm::vec3(0.878f, -0.513f, 0.0f),
		glm::vec3(0.878f, -0.838f, 0.0f),		
	};
	
	GLuint indices1[] = {
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
		37, 38, 39
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
		position.size() * sizeof(glm::vec3),
		&position[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices1),
		indices1,
		GL_STATIC_DRAW);
		
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	

	/*
	// texture 1
	int imageWidth = 0;
	int imageHeight = 0;
	unsigned char* image = SOIL_load_image("../images/1_texture.png", &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);
	GLuint texture0;

	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "ERROR::TEXTURE_LOADING_FAIL!" << endl;
	}	
	
	

	// Activate texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	//Update uniform
	uniformLocation = glGetUniformLocation(shaderProgramID, "texture0");
	

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);	
	*/

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgramID);		
		
		uniformLocation = glGetUniformLocation(shaderProgramID, "my_Color");
		
		// draw 1st obj		

		glUniform4f(uniformLocation, 0.0f, 1.0f, 0.0f, 1.0f);						

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	

	
		//draw 2nd obj
		
		glUniform4f(uniformLocation, 1.0f, 0.0f, 0.0f, 1.0f);		

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(6*sizeof(int)));

		//draw 3rd obj

		glUniform4f(uniformLocation, 0.0f, 1.0f, 0.0f, 1.0f);		

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(12 * sizeof(int)));

		//draw 4th obj

		glUniform4f(uniformLocation, 0.0f, 1.0f, 0.0f, 1.0f);			

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(18 * sizeof(int)));

		//draw 5th obj

		glUniform4f(uniformLocation, 1.0f, 1.0f, 0.0f, 1.0f);		

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(24 * sizeof(int)));

		//draw 6th obj

		glUniform4f(uniformLocation, 0.0f, 1.0f, 0.0f, 1.0f);		

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(30 * sizeof(int)));

		//draw 7th obj

		glUniform4f(uniformLocation, 0.0f, 1.0f, 1.0f, 1.0f);				

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(36 * sizeof(int)));

		//draw 8th obj

		glUniform4f(uniformLocation, 0.0f, 1.0f, 1.0f, 1.0f);		

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(42 * sizeof(int)));

		//draw 9th obj

		glUniform4f(uniformLocation, 0.0f, 1.0f, 1.0f, 1.0f);		

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(48 * sizeof(int)));


		//draw 10th obj

		glUniform4f(uniformLocation, 0.0f, 1.0f, 1.0f, 1.0f);		

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(54 * sizeof(int)));		
	

		//clean up
		

		glDisableVertexAttribArray(0);

		glUseProgram(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
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
