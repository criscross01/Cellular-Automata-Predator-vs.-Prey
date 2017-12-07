#include "cell.h"
#include <cstdlib>
#include <time.h>

Cell::Cell()
{
	srand((unsigned)time(0));
	switch (rand() % 3)
	{
	case 0:
		celltype = Empty;
		color = glm::vec3(0.0f, 0.0f, 0.0f);
		break;

	case 1:
		celltype = Predator;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		break;

	case 2:
		celltype = Prey;
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	}
}

void Cell::setEmpty()
{
	celltype = Empty;
}
void Cell::setPredator()
{
	celltype = Predator;
}
void Cell::setPrey()
{
	celltype = Prey;
}

Cell::~Cell()
{
}
