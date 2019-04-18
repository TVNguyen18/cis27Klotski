#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "vertexBuffer.h"
#include "indexBuffer.h"
using namespace std;

//test

// Note: many tutorials and videos use GLuint.
// GLuint is the OpenGl equivalent of unsigned int.

struct ShaderProgramSource {
	string VertexSource;
	string FragmentSource;
};

static ShaderProgramSource parseShader(const string& filePath) {
	ifstream stream(filePath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	string line;
	stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos) {
				type = ShaderType::VERTEX;
			} else {
				if (line.find("fragment") != string::npos) {
					type = ShaderType::FRAGMENT;
				}
			}
		} else {
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

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
	int location;
	float increment = 0.05f;
	float r = 0.0;
	ShaderProgramSource source = parseShader("shader.shader");
	float positions[] = {
		-0.25f, 0.5f,
		0.25f, 0.5f,
		0.25f, 1.0f,
		-0.25f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	float positions2[] = {
		-0.75f, 0.5f,
		-0.5f, 0.5f,
		-0.5f, 1.0f,
		-0.75f, 1.0f
	};
	unsigned int vao;
	VertexBuffer* vb = nullptr;
	IndexBuffer* ib = nullptr;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(400, 400, "Hello World", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		cout << "\nERROR!" << endl;

	cout << glGetString(GL_VERSION) << endl;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// generate buffer for triangle
	vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));
	// attach buffer to GPU
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);

	// generate buffer for square
	ib = new IndexBuffer(indices, 6);

	// generate shader
	shader = createShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);
	location = glGetUniformLocation(shader, "uColor");
	//glUniform4f(location, 1.0, 0.0, 1.0, 1.0);

	//unbind
	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT);

		glUniform4f(location, r, 0.3, 0.8, 1.0);
		glUseProgram(shader);
		glBindVertexArray(vao); // instead of having to use 
		                        //glBindBuffer(GL_ARRAY_BUFFER, buffer) 
		                        //and the glVertexAttribPointer 
		                        //& glEnableVertexAttribArray
		ib->bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		if (r > 1.0f)
			increment = -0.05f;
		else
			if (r < 0.0)
				increment = 0.05f;

		r += increment;

		glfwSwapBuffers(window);

		glfwPollEvents();

		glDeleteProgram(shader);
	}

	glfwTerminate();
}
