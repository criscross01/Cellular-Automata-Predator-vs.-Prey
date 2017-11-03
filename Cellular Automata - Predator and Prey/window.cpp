#include "window.h"
#include <iostream>
#include <fstream>
#include <cstring>

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

const char* Window::getShaderSource(std::string shaderSource)
{
	std::string line;
	std::string text;
	std::ifstream file;
	file.open(shaderSource);

	while (getline(file,line))
	{
		text += line + "\n";
	}
	file.close();

	return text.c_str();
}

void Window::shaderProgram(void)
{
	const char *vertexShaderSource{getShaderSource("vertexShader.txt")};
	
	const char *fragmentShaderSource{ getShaderSource("fragmentShader.txt") };
	
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;
		std::cin.get();
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderPrgrm = glCreateProgram();

	glAttachShader(shaderPrgrm,vertexShader);
	glAttachShader(shaderPrgrm, fragmentShader);
	glLinkProgram(shaderPrgrm);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Window::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

Window::Window(int width, int height, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Window initialization failed" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Glad initialization failed" << std::endl;
		return;
	}

	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glfwSetWindowShouldClose(window, false);

	this->shaderProgram();
	
	float vertices[] = {
		-0.5f,-0.5f,0.0f, //Bottom Left
		 0.5f,-0.5f,0.0f, //Bottom Right
		-0.5f,0.5f,0.0f,  //Top Left
		 0.5f, 0.5f, -0.0f//Top Right
	};

	int indices[] = {
		0,1,3,
		0,2,3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Window::renderMain()
{
	//Input
	this->processInput();
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderPrgrm, "ourColor");

	//Render
//	glClearColor(0.5f, 0.0f,0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderPrgrm);
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Window::windowShouldClose(void)
{
	if (glfwWindowShouldClose(window))
	{
		return false;
	}
	else
	{
		return true;
	}
}

Window::~Window() {}

/*
GLFWwindow* Window::getWindow(void)
{
	return window;
}
*/