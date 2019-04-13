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

// TESTING!!!
// Another test!

int main() {
	GLFWwindow* window;
	unsigned int buffer;
	unsigned int shader;
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
		"\n    color = vec4(0.0, 1.0, 1.0, 1.0);"
		"\n}";
	float positions[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,

		0.5f, 0.5f,
		-0.5f, 0.5f,
		-0.5f, -0.5f
	};

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(480, 400, "Hello World", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		cout << "\nERROR!" << endl;

	cout << glGetString(GL_VERSION) << endl;

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	shader = createShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		/*glBegin(GL_TRIANGLES);  THIS IS THE OLD WAY OF DOING THINGS
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();*/

		glDrawArrays(GL_TRIANGLES, 0, 6); // THIS IS THE NEW WAY

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
}