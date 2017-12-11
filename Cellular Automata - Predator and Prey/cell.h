#pragma once
#include <glm\glm.hpp>
#include <string>
#include "random.h"
#include "Simulation.h"

class Cell
{
public:
	Cell(Simulation*);
	~Cell();

	enum cellType {
		Empty = 0,
		Predator = 1,
		Prey = 2
	}celltype;

	void setEmpty();
	void setPrey();
	void setPredator();
	
	glm::vec3 color;

	int health;

	int threshold = 10;
private:
	Random random;
};