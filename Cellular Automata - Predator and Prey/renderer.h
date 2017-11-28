#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "empty.h"
#include "prey.h"
#include "predator.h"

using namespace std;

class Renderer
{
public:
	Renderer(int,int,const char*);
	~Renderer();

	void render(void);

	bool getWindowShouldCLose();

private:

	int screenWidth, screenHeight;

	const struct squareRenderInfo
	{
		float vertices[12] = {
			-0.5f,-0.5f,0.0f, //Bottom Left
			0.5f,-0.5f,0.0f,  //Bottom Right
			0.5f, 0.5f,0.0f,  //Top Right
			-0.5f, 0.5f,0.0f  //Top Left
		};
		unsigned int indices[6] = {
			0,1,2,
			0,3,2
		};
	}square;


	enum cellType {
		Predator,
		Prey,
		Empty
	};

	unsigned int VBO, VAO, EBO;

	GLFWwindow* window;

	//Shader stuff
	unsigned int shaderID;

	void getShaderProgram(string vertexPath, string fragmentPath);
	void useShader(void);
};