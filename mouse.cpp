#include "mouse.h"

Mouse::Mouse() : currentX(0), currentY(0), currentXR(0), currentYR(0), initialFlag(-1) { }

Mouse::~Mouse()
{
	currentX = currentY = currentXR = currentYR = 0;
}

int Mouse::getinitialFlag(void)
{
	return initialFlag;
}

void Mouse::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	double tempCurrentX;
	double tempCurrentY;
	double tempCurrentXR;
	double tempCurrentYR;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		cout << "\nLeft click!";
		glfwGetCursorPos(window, &tempCurrentX, &tempCurrentY);
		cout << "\n" << tempCurrentX << "," << tempCurrentY;
		tempCurrentX -= 320;
		tempCurrentY = -tempCurrentY + 240;
		cout << " => " << currentX << "," << currentY;
		initialFlag = 1;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		cout << "\nLeft release!";
		glfwGetCursorPos(window, &tempCurrentXR, &tempCurrentYR);
		cout << "\n" << tempCurrentXR << "," << tempCurrentYR;
		tempCurrentXR -= 320;
		tempCurrentYR = -tempCurrentYR + 240;
		cout << " => " << tempCurrentXR << "," << tempCurrentYR;
	}
	currentX = tempCurrentX;
	currentY = tempCurrentY;
	currentXR = tempCurrentXR;
	currentYR = tempCurrentYR;
}

void Mouse::set_mouse_button_callback(GLFWwindow* window)
{
	void (Mouse::* functionPtr)() = &mouse_button_callback;
	glfwSetMouseButtonCallback(window, functionPtr);
}
