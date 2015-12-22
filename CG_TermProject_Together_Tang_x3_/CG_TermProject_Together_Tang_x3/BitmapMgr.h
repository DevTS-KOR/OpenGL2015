#pragma once
#include "Common.h"

class CBitmapMgr
{
	GLuint	g_ivTextures[3][4];
	GLuint	g_ivMonsterTextures[5][36];
	GLubyte*    m_pBytes[3][4];
	GLubyte*    m_pMonsterBytes[5][36];
	GLubyte*	m_pBrick[3];
	GLubyte*	m_pSkyBox[5];
	GLubyte*	m_pContainer[2];

	BITMAPINFO* m_pInfo[2][4];
	BITMAPINFO* m_pInfo2;
	const char* m_pszFilename[3][4];
	const char* m_pszBuildingFilename[2][4];
	const char* m_pszMonsterFilename[5][36];
public:
	GLuint*	GetTexture(SceneList _eScene);
	GLubyte*	GetTexture(int _Type,int _Texture);
	GLubyte**	GetTexture(MonsterList _eMonster);
	void	Initialize();
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
	void TextureInit();
public:
	CBitmapMgr();
	~CBitmapMgr();

private:
	
};


