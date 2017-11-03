#include <iostream>
#include "window.h"

int main()
{

	Window window(800, 600, "Cellular Automata - Predator and Prey");

	while (window.windowShouldClose())
	{
		window.renderMain();

		std::cout << "LOOP!" << std::endl;
	}

	glfwTerminate();
	return 0;
}