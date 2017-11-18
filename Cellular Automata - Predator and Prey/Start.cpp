#include <iostream>
#include "renderer.h"

using namespace std;

int main()
{
	Renderer renderer(800, 600, "Cellular Automata(Predator and Prey)");

	while (renderer.getWindowShouldCLose())
	{
		renderer.render();
	}

	return 0;
}