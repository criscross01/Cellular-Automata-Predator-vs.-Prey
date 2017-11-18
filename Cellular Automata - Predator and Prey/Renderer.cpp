#include "renderer.h"

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

Renderer::Renderer(int width, int height, const char* title)
{
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

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareRenderer.vertex), squareRenderer.vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareRenderer.indices), squareRenderer.indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Renderer::render() {
	processInput(window);

	//glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	useShader();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}


//Shader Stuff
void Renderer::getShaderProgram(string vertexPath,string fragmentPath)
{
	ifstream vertexFile, fragmentFile;
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	stringstream vertexData, fragmentData;
	vertexData << vertexFile.rdbuf();
	fragmentData << fragmentFile.rdbuf();

	const char* vertexSource = vertexData.str().c_str();
	const char* fragmentSource = fragmentData.str().c_str();

	unsigned int vertex{ glCreateShader(GL_VERTEX_SHADER) }, fragment{glCreateShader(GL_FRAGMENT_SHADER)};

	glShaderSource(vertex, 1, &vertexSource, 0);
	glShaderSource(fragment, 1, &fragmentSource, 0);

	glCompileShader(vertex);
	glCompileShader(fragment);

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glLinkProgram(shaderID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Renderer::useShader()
{
	glUseProgram(shaderID);
}

bool Renderer::getWindowShouldCLose()
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

Renderer::~Renderer()
{
	glfwTerminate();
}