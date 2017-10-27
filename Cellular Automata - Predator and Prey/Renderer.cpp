#include <glad\glad.h>
#include <glfw/glfw3.h>
#include <string>
#include <iostream>

void frameBufferResize(GLFWwindow* window, int width, int height);

void gladInitialize()
{
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

GLFWwindow* initializeWindow(int width, int height, const char *title)
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Window == NULL" << std::endl;
		return window;
	}

	glViewport(0, 0, width, height);
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, frameBufferResize);
	
	return window;
}

void frameBufferResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}