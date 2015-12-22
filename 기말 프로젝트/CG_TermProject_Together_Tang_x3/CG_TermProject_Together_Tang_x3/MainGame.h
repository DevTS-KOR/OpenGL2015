#pragma once
#include "stdafx.h"
class CBitmapMgr;
class CMainGame
{
	CBitmapMgr*		m_pBitmapMgr;
	

public:
	GLvoid	Initialize();
	GLvoid	Render(GLvoid);
	GLvoid	Keyboard(unsigned char key, int x, int y);
	GLvoid	SpecialKeyboard(int key, int x, int y);
	GLvoid	Update(int value);
	GLvoid	Mouse(int button, int state, int x, int y);
	GLvoid	MouseMotionFunc(int x, int y);
	GLvoid	Release();
public:
	CMainGame();
	~CMainGame();
};

