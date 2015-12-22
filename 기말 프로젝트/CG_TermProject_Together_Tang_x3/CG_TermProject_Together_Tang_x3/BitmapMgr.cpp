#include "stdafx.h"
#include "BitmapMgr.h"


GLubyte * CBitmapMgr::LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// ���̳ʸ� �б� ���� ������ ����
	fopen_s(&fp, filename, "rb");
	if (fp == NULL){
		printf("File Open Error! Please Check filename");
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		printf("File Read Error");
		return NULL;
	}
	// ������ BMP �������� Ȯ���Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		printf("This is not Bitmap File");
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� ����.
	infosize = header.bfOffBits - sizeof (BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		printf("Memory Allocation Error");
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		printf("Cannot Read Bitmap Info Header");
		return NULL;
	}
	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		printf("Memory Allocation Error2");
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		printf("Bitmap Data Save Error");
		return NULL;
	}
	fclose(fp);
	return bits;
}

void CBitmapMgr::TextureInit()
{

	glGenTextures(4, g_ivTextures[0]);
	glBindTexture(GL_TEXTURE_2D, g_ivTextures[0][0]);
	m_pBytes[0][0] = LoadDIBitmap(m_pszFilename[0][0], &m_pInfo[0][0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pBytes[0][0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(4, g_ivTextures[1]);
	glBindTexture(GL_TEXTURE_2D, g_ivTextures[1][0]);
	m_pBytes[1][0] = LoadDIBitmap(m_pszFilename[1][0], &m_pInfo[1][0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 2048, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pBytes[1][0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}


CBitmapMgr::CBitmapMgr()
{

}

CBitmapMgr::~CBitmapMgr()
{

}

void CBitmapMgr::Initialize()
{
	m_pszFilename[DRAW_LOGO][0] = "Texture/Logo.bmp";
	m_pszFilename[DRAW_LOGO][1] = "Texture/Logo.bmp";
	m_pszFilename[DRAW_LOGO][2] = "Texture/Logo.bmp";
	m_pszFilename[DRAW_LOGO][3] = "Texture/Logo.bmp";
	m_pszFilename[DRAW_LOBBY][0] = "Texture/Lobby.bmp";
	m_pszFilename[DRAW_LOBBY][1] = "Texture/Lobby.bmp";
	m_pszFilename[DRAW_LOBBY][2] = "Texture/Lobby.bmp";
	m_pszFilename[DRAW_LOBBY][3] = "Texture/Lobby.bmp";
	TextureInit();
}

GLuint* CBitmapMgr::GetTexture(SceneList _eScene)
{
	switch (_eScene)
	{
	case SCENE_LOGO:
		return g_ivTextures[DRAW_LOGO];
	case SCENE_LOBBY:
		return g_ivTextures[DRAW_LOBBY];
	case SCENE_INGAME:
		break;
	case SCENE_NONE:
		break;
	}
	return nullptr;
}
