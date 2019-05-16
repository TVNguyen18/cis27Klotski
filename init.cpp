#include "init.h"
#include "klotski.h"
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