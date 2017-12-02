#include "Simulation.h"

using namespace std;



void framebufferResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

Simulation::Simulation(int width, int height, const char* title)
{
	screenWidth = width;
	screenHeight = height;

	if (!glfwInit())
	{
		cerr << "GLFW failed to initialize" << endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3.0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3.0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
	if (window == NULL)
	{
		cerr << "Window is NULL" << endl;
		return;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cerr << "GLAD loading failed" << endl;
		return;
	}
	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(window, framebufferResize);

	getShaderProgram("vertexShader.txt", "fragmentShader.txt");
		
	unsigned int VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square.vertices), square.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square.indices), square.indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
/*
void Simulation::render()
{
	processInput(window);
	
	useShader();
	glBindVertexArray(VAO);

	for (int x = 0; x < screenWidth; x++)
	{
		for (int y = 0; y, screenHeight; y++)
		{
			glm::mat4 model;
			model = glm::translate(model, glm::vec3(x, y, 0));
			model = glm::scale(model,glm::vec3(0.004f,0.004f,0));
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniform3f(glGetUniformLocation(shaderID, "color"), 1.0f, 0.0f, 0.0f);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}

	glfwSwapBuffers(window);
	glfwPollEvents();
}
*/


//Shader Stuff
void Simulation::getShaderProgram(string vertexPath,string fragmentPath)
{
	ifstream vertexFile, fragmentFile;
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	stringstream vertexData, fragmentData;
	vertexData << vertexFile.rdbuf();
	fragmentData << fragmentFile.rdbuf();

	string vertexBuffer = vertexData.str();
	string fragmentBuffer = fragmentData.str();

	const char* vertexSource = vertexBuffer.c_str();
	const char* fragmentSource = fragmentBuffer.c_str();

	unsigned int vertex{ glCreateShader(GL_VERTEX_SHADER) }, fragment{glCreateShader(GL_FRAGMENT_SHADER)};

	glShaderSource(vertex, 1, &vertexSource, NULL);
	glShaderSource(fragment, 1, &fragmentSource, NULL);

	glCompileShader(vertex);
	glCompileShader(fragment);

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glLinkProgram(shaderID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Simulation::useShader()
{
	glUseProgram(shaderID);
}




//Simulation Stuff
void Simulation::run()
{
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			switch (rand() % 3)
			{
			case 0:
				gameBoard[x][y].empty = new Empty;
				break;
			
			case 1:
				gameBoard[x][y].prey = new Prey;
				break;

			case 2:
				gameBoard[x][y].predator = new Predator;
				break;
			}
		}
	}
}

void Simulation::Step()
{
	
}


Simulation::~Simulation()
{
	glfwTerminate();
}