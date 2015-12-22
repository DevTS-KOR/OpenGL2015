#pragma once
#include "Common.h"

class CBitmapMgr
{
	GLuint	g_ivTextures[2][4];
	GLubyte*    m_pBytes[2][4];
	BITMAPINFO* m_pInfo[2][4];
	const char* m_pszFilename[2][4];
public:
	GLuint*	GetTexture(SceneList _eScene);
	void	Initialize();
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
	void TextureInit();
public:
	CBitmapMgr();
	~CBitmapMgr();

private:
	
};


