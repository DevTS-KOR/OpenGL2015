#pragma once
#include <gl/glut.h>
#include <windows.h>
#include <stdio.h>

typedef struct Box
{
	float fX[4];
	float fY[4];
	float fZ[4];
}Box;

class Skybox
{
public:
	Box box[4];
	void SetupRC();
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
	GLubyte *pBytes[4];
	BITMAPINFO *info;
	GLuint* textures;

public:
	Skybox();
	void Init();
	void Draw();
	~Skybox();
};

