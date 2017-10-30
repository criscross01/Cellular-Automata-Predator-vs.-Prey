#include <iostream>
#include "window.h"

int main()
{
	Window window(800, 600, "YourMOM");

	while (window.windowShouldClose())
	{
		window.renderMain();

		std::cout << "Gone throug loop" << std::endl;
	}
	
	return 0;
}