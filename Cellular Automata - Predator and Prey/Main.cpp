#include <iostream>
#include "renderer.h"

int main()
{
	if (graphicInit() != 0)
	{
		std::cerr << "Graphich initialization failed" << std::endl;
		std::cin.get();
		return -1;
	}
	
	while (true)
	{
		render();
	}

	return 0;
}