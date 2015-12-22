#include "Weather.h"


Snow::Snow()
{

}

Rain::Rain()
{

}


Snow::~Snow()
{
}

Rain::~Rain()
{
}


Weather::Weather()
{
	init();
}

Weather::~Weather()
{

}

void Weather::init()
{
	for (int i = 0; i < 60; i++)
	{
		snow.fX[i] = randomRange(-300, 300);
		snow.fY[i] = rand() % 600 - 300;
		snow.fZ[i] = randomRange(-500, -100);

		rain.fX[i] = randomRange(-300, 300);
		rain.fY[i] = rand() % 600 - 300;
		rain.fZ[i] = randomRange(-500, -100);
	}
}

void Weather::Snow_Draw()
{
	for (int i = 0; i < 60; i++)
	{
		glTranslatef(snow.fX[i], snow.fY[i], snow.fZ[i] + 300.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glutSolidSphere(5, 5, 5);
		glTranslatef(-snow.fX[i], -snow.fY[i], -snow.fZ[i] - 300.0f);
	}
}

void Weather::Rain_Draw()
{
	for (int i = 0; i < 60; i++)
	{
		glTranslatef(rain.fX[i], rain.fY[i], rain.fZ[i] + 300.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glScalef(0.2f, 2.f, 0.2f);
		glutSolidCube(10);
		glScalef(5.0f, 0.5f, 5.0f);
		glTranslatef(-rain.fX[i], -rain.fY[i], -rain.fZ[i] - 300.0f);
	}
}

int Weather::randomRange(int n1, int n2)
{
	return (int)(rand() % (n2 - n1 + 1)) + n1;
}