#pragma once
#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
class Snow
{
public:
	float fX[60];
	float fY[60];
	float fZ[60];

public:
	Snow();
	~Snow();

};

class Rain
{
public:
	float fX[60];
	float fY[60];
	float fZ[60];

public:
	Rain();
	~Rain();

};

class Weather
{
public:
	Snow snow;
	Rain rain;

public:
	Weather();
	~Weather();
	void init();
	void Snow_Draw();
	void Rain_Draw();
	int randomRange(int n1, int n2);
};

