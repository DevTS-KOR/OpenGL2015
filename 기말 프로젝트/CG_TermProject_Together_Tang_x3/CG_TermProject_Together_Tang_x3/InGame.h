#pragma once
#include "Scene.h"
class CInGame : public CScene
{
public:
	CInGame();
	~CInGame();

	virtual GLvoid Initialize(CBitmapMgr* _pBitmapMgr);
	virtual GLvoid Render(GLvoid);
	virtual GLvoid Keyboard(unsigned char key, int x, int y);
	virtual GLvoid SpecialKeyboard(int key, int x, int y);
	virtual GLvoid Update(int value);
	virtual GLvoid Mouse(int button, int state, int x, int y);
	virtual GLvoid MouseMotionFunc(int x, int y);
	virtual GLvoid Release(GLvoid);

};

