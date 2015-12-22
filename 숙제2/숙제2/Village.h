#pragma once
#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

class Village
{
public:
	float fRed[10];
	float fGreen[10];
	float fBlue[10];
	float fColor;

	float fX[10];
	float fY[10];
	float fZ[10];

	float fScale_Y[10];



public:
	void Init();
	int randomRange(int n1, int n2);
	void Draw();
	void SetupRC();
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
	GLubyte *pBytes[1];
	BITMAPINFO *info;
	GLuint* textures;

	
public:
	Village();
	~Village();
};

