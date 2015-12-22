#pragma once
#include <gl/glut.h>

class Roller
{
public:
	float fX;
	float fY;
	float fZ;

public:
	void init();
	void draw();

public:
	Roller();
	~Roller();
};

