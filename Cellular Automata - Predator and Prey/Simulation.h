#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "prey.h"
#include "predator.h"
#include "empty.h"

class Simulation
{
public:
	Simulation(int,int,const char*);
	~Simulation();

	void run(void);
private:
	//Rendering
	int screenWidth, screenHeight;

	void render(void);

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

	unsigned int VAO, EBO;

	GLFWwindow* window;

	//Shader stuff
	unsigned int shaderID;

	void getShaderProgram(std::string vertexPath, std::string fragmentPath);
	void useShader(void);


	//Simulation stuff
	void Step(void);

	struct Cells {
		Empty* empty;
		Predator* predator;
		Prey* prey;
	};

	Cells gameBoard[2][1];
};