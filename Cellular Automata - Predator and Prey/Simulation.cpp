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

	window = glfwCreateWindow(width, height, title, NULL, NULL);
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

void Simulation::render()
{
	processInput(window);
	
	useShader();
	glBindVertexArray(VAO);
	
	renderTimeStart = clock();
	for (int y = 0; y < screenHeight; y++)
	{
		for (int x = 0; x < screenWidth; x++)
		{
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrices[y*screenWidth + x]));
			glUniform3fv(glGetUniformLocation(shaderID, "color"), 1, glm::value_ptr(gameBoard[y*screenWidth + x]->color));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	cout << "Complete render: " << float(clock() - renderTimeStart) << endl;

	glfwSwapBuffers(window);
	glfwPollEvents();
}

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

	for (int i = 0; i < (screenWidth * screenHeight); i++)
	{
		gameBoard.push_back(new Cell(this));
	}

	glm::mat4 scaleModel;
	scaleModel = glm::scale(scaleModel, glm::vec3((float)2 / screenWidth,(float)2 / screenHeight, 0.0f));
	for (int y = 0; y < screenHeight; y++)
	{
		for (int x = 0; x < screenWidth; x++)
		{
			glm::mat4 model{ scaleModel };
			model = glm::translate(model, glm::vec3((float)x - (screenWidth / 2),(float)y - (screenHeight / 2), 0.0f));
			modelMatrices.push_back(model);
		}
	}

	while (!glfwWindowShouldClose(window))
	{
		this->Step();

		this->render();
	}
}

void Simulation::Step()
{
	for (int y = 0; y < screenHeight; y++)
	{
		for (int x = 0; x < screenWidth; x++)
		{
			Cell* thisCell = gameBoard[y * screenWidth + x];
			
			int xMov;
			int yMov;

			if (x != 0 && x != (screenWidth-1))
			{
				xMov = random.getRandomInt(-1, 1);
			}

			else if (x == 0)
			{
				xMov = random.getRandomInt(0, 1);
			}
			
			else if (x == (screenWidth-1))
			{
				xMov = random.getRandomInt(-1, 0);
			}


			if (y != 0 && y != (screenHeight-1))
			{
				yMov = random.getRandomInt(-1, 1);
			}

			else if (y == 0)
			{
				yMov = random.getRandomInt(0, 1);
			}

			else if (y == (screenHeight-1))
			{
				yMov = random.getRandomInt(-1, 1);
			}

			Cell* otherCell = gameBoard[(y + yMov)*screenWidth + (x + xMov)];



			if( thisCell->celltype == 1) //If cell is predator
			{
				if (otherCell->celltype == 0) //If other cell is empty
				{
					otherCell->setPredator();
					otherCell->health = thisCell->health;
					thisCell->health = 1;
				}

				else if (otherCell->celltype == 2) //If other cell is prey
				{
					otherCell->setPredator();
					otherCell->health += thisCell->health;
					thisCell->health = thisCell->threshold;
				}


				thisCell->health -= 1;
				if (thisCell->health <= 0) //Called when predator is "dead"
				{
					thisCell->setEmpty();
					thisCell->health = 0;
				}
			}

			else if (thisCell->celltype == 2) //If cell is prey
			{
				if (otherCell->celltype == 0) //If other cell is predator
				{

				}

				else if (otherCell->celltype == 1)//If other cell is predator
				{

				}

				else if (otherCell->celltype == 2) //If other cell is prey
				{

				}
			}
		}
	}
}


Simulation::~Simulation()
{
	glfwTerminate();
}