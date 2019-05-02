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
#include "renderer.h"
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
		/*0.078f, 0.1f,
		0.31f, 0.1f,
		0.31f, 0.42f,
		0.078f, 0.42f*/
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
		-0.5f, 0.5f,
		-0.25f, 0.5f,
		-0.25f, 1.0f,
		-0.5f, 1.0f
	};
	unsigned int vao;
	VertexBuffer* vb = nullptr;
	IndexBuffer* ib = nullptr;
	VertexArray* va = nullptr;
	VertexBufferLayout layout;
	Shader* shader = nullptr;
	unsigned int vao2;
	VertexBuffer* vb2 = nullptr;
	VertexArray* va2 = nullptr;
	VertexBufferLayout layout2;
	Shader* shader2 = nullptr;
	Renderer renderer;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

	//shader->setUniform4F("uColor", 1.0, 0.0, 1.0, 1.0);

	//unbind
	va->unbind();
	shader->unbind();
	vb->unbind();
	ib->unbind();

	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);

	// generate buffer for triangle

	vb2 = new VertexBuffer(positions2, 4 * 2 * sizeof(float));

	// attach buffer to GPU
	va2 = new VertexArray();
	layout2.push<float>(2);
	va2->addBuffer(*vb2, layout2);

	// generate buffer for square
	//ib2 = new IndexBuffer(indices, 6);

	// generate shader
	shader2 = new Shader("shader.shader");
	shader2->bind();

	//shader->setUniform4F("uColor", 1.0, 0.0, 1.0, 1.0);

	//unbind
	va2->unbind();
	shader2->unbind();
	vb2->unbind();
	//ib2->unbind();

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT);

		shader->bind();

		shader->setUniform4F("uColor", r, 0.0, 0.5, 1.0);
		//shader2->setUniform4F("uColor", 1.0, 1.0, 0.0, 1.0);

		renderer.draw(*va, *ib, *shader);

		shader2->bind();

		shader2->setUniform4F("uColor", 0.2, 0.4, 0.5, 1.0);


		renderer.draw(*va2, *ib, *shader2);

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
