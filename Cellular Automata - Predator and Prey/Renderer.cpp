#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

using namespace std;

int windowWidth = 800;
int windowHeight = 600;

void frameBufferSize(GLFWwindow* window, int width, int height);

void processInputs(GLFWwindow* window);

const char *vertexShaderSource = "# version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"\n"
"void main()\n"
"{\n"
"	gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}";

char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}";

int graphicInit()
{
	//Initializes GLFW
	if (!glfwInit())
	{
		cerr << "Failed to initialize glfw" << endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight , "Predator And Prey", NULL, NULL);
	if (window == NULL)
	{
		cerr << "Window failed to be created" << endl;
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cerr << "Glad was not able to be instantiated" << endl;
		return -1;
	}
	glViewport(0, 0, windowWidth, windowHeight);

	glfwSetFramebufferSizeCallback(window, frameBufferSize);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(VAO);
	glBindVertexArray(0);

	return 0;
}

void frameBufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}