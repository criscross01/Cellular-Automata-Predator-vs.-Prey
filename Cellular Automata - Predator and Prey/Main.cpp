#include <iostream>
#include "window.h"

int main()
{

	Window window(800, 600, "OpenGL test");

	while (window.windowShouldClose())
	{
		window.renderMain();

		std::cout << "LOOP!" << std::endl;
	}
	
	return 0;
}