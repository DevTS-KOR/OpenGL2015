#pragma once
#include "stdafx.h"
#include "Common.h"
#pragma warning (disable:4996)

class Monster
{
public:
	Vec3 Monster_Vec;
	float fZ_left_arm;
	float fZ_right_arm;
	float fZ_left_leg;
	float fZ_right_leg;
	float fArm_move;
	float fLeg_move;


public:
	Monster();
	~Monster();
	void init();
	GLvoid SetupRC();
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
	GLubyte *pFace[6];
	GLubyte *pBody[6];
	GLubyte *pLarm[6];
	GLubyte *pRarm[6];
	GLubyte *pLleg[6];
	GLubyte *pRleg[6];
	BITMAPINFO *info;
	GLuint* textures;
	void draw();
	//3���� �簢���� ����� �Լ�(x, y, z, �ʺ�, ����, ����, R, G, B)
	void Rect(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize);


};

