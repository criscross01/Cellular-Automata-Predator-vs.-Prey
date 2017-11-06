#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <string>

class Window
{
public:
	Window(int width, int height, const char* title);
	~Window();
	void renderMain();
	bool windowShouldClose();
//	GLFWwindow* getWindow(void);

private:
	void processInput();
	void shaderProgram(void);
	std::string getShaderSource(std::string);

	GLFWwindow* window;
	unsigned int VBO, VAO, EBO;
	unsigned int shaderPrgrm;
	
};