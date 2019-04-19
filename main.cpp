#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"
using namespace std;

//test

// Note: many tutorials and videos use GLuint.
// GLuint is the OpenGl equivalent of unsigned int.

// main
int main() {
	GLFWwindow* window;
	unsigned int buffer;
	unsigned int ibo;
	int location;
	float increment = 0.05f;
	float r = 0.0;
	float positions[] = { // vertices of square
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
	VertexArray* va = nullptr;
	VertexBufferLayout layout;
	Shader* shader = nullptr;

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

	// makes blinking slower
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		cout << "\nERROR!" << endl;

	cout << glGetString(GL_VERSION) << endl;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// generate buffer for triangle

	vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));

	
	// attach buffer to GPU
	va = new VertexArray();
	layout.push<float>(2);
	va->addBuffer(*vb, layout);

	// generate buffer for square
	ib = new IndexBuffer(indices, 6);
	
	// generate shader
	shader = new Shader("shader.shader");
	shader->bind();

	shader->setUniform4F("uColor", 1.0, 0.0, 1.0, 1.0);

	//unbind
	va->unbind();
	shader->unbind();
	vb->unbind();
	ib->unbind();

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT);

		shader->bind();

		shader->setUniform4F("uColor", r, 0.8, 0.9, 1.0);
		va->bind(); // instead of having to use 
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
	}

	glfwTerminate();

	delete vb;
	delete ib;
	delete va;
	vb = nullptr;
	ib = nullptr;
	va = nullptr;
}
