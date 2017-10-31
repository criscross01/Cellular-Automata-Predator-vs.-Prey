#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	Window(int width, int height, const char* title);
	void renderMain();
	bool windowShouldClose();
	GLFWwindow* getWindow(void);

private:
	GLFWwindow* window;
	void processInput();
	unsigned int shaderProgram(void);
	unsigned int VBO;
	unsigned int VAO;
	unsigned int shaderPrgrm;
};