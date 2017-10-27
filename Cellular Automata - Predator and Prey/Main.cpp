#include <iostream>
#include "renderer.h"


int main()
{

	GLFWwindow* window = initializeWindow(800, 600, "Your Mom Gay");
	if (window == NULL)
	{
		return -1;
	}
	gladInitialize();

	std::cin.get();
	return 0;
}