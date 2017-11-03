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
	void shaderProgram(void);
	unsigned int VBO, VAO, EBO;
	unsigned int shaderPrgrm;
};