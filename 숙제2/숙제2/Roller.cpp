#include "Roller.h"


Roller::Roller()
{
	init();
}


Roller::~Roller()
{
}

void Roller::init()
{
	fX = 0.0f;
	fY = 0.0f;
	fZ = 0.0f;
}

void Roller::draw()
{
	glColor3f(0.5f, 0.0f, 0.5f);
	glutSolidCube(50);
}
