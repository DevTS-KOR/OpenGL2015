#include "stdafx.h"
#include "BitmapMgr.h"


GLubyte * CBitmapMgr::LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	fopen_s(&fp, filename, "rb");
	if (fp == NULL){
		printf("File Open Error! Please Check filename");
		return NULL;
	}
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		printf("File Read Error");
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		printf("This is not Bitmap File");
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof (BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		printf("Memory Allocation Error");
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		printf("Cannot Read Bitmap Info Header");
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		printf("Memory Allocation Error2");
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
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
