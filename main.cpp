#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

// TESTING!!!

int main() {
	GLFWwindow* window;
	unsigned int buffer;
	float positions[6] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

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
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		/*glBegin(GL_TRIANGLES);  THIS IS THE OLD WAY OF DOING THINGS
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();*/

		glDrawArrays(GL_TRIANGLES, 0, 3); // THIS IS THE NEW WAY

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
}