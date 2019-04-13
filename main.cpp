#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

static unsigned int compileShader(unsigned int type, const string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	int result;
	int length;
	char* message;
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << 
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
			<< " shader!" << endl
			<< message << endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int createShader(const string& vertexShader, const string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main() {
	GLFWwindow* window;
	unsigned int buffer;
	unsigned int ibo;
	unsigned int shader;

	// shader specification

	string vertexShader = "#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;"
		"\n"
		"\nvoid main() {"
		"\n    gl_Position = position;"
		"\n}";

	string fragmentShader = "#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;"
		"\n"
		"\nvoid main() {"
		"\n    color = vec4(1.0, 1.0, 0.25, 1.0);"
		"\n}";

	
	//for square
	float positions[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};

	// linked to above, helps draw square
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	// troubleshooting
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(400, 400, "Hello World", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		cout << "\nERROR!" << endl;

	cout << glGetString(GL_VERSION) << endl;
	

	// generate buffer for triangle
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

	// attach buffer to GPU
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	// generate buffer for square
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices,
		GL_STATIC_DRAW);


	// generate shader
	shader = createShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//draw
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // DRAWING SQUARE

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
}