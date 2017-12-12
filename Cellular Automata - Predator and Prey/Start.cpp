#include <iostream>
#include "Simulation.h"

using namespace std;

int main()
{
	Simulation simulation(400, 300, "Cellular Automata(Predator and Prey)");
	simulation.run();

	return 0;
}