#pragma once
#include <gl/glut.h>
#include <windows.h>
#include <stdio.h>

typedef struct OutBox
{
	float fX[4];
	float fY[4];
	float fZ[4];
}OutBox;

class OutSkybox
{
public:
	OutBox box[5];
	void SetupRC();
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
	GLubyte *pBytes[1];
	BITMAPINFO *info;
	GLuint* textures;

public:
	OutSkybox();
	void Init();
	void Draw();
	~OutSkybox();
};