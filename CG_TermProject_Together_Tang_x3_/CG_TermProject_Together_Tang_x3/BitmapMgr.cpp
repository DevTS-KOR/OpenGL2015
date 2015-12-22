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

	glGenTextures(4, g_ivTextures[DRAW_LOGO]);
	glBindTexture(GL_TEXTURE_2D, g_ivTextures[DRAW_LOGO][0]);
	m_pBytes[DRAW_LOGO][0] = LoadDIBitmap(m_pszFilename[DRAW_LOGO][0], &m_pInfo[DRAW_LOGO][0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pBytes[0][0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(4, g_ivTextures[DRAW_LOBBY]);
	glBindTexture(GL_TEXTURE_2D, g_ivTextures[DRAW_LOBBY][0]);
	m_pBytes[DRAW_LOBBY][0] = LoadDIBitmap(m_pszFilename[DRAW_LOBBY][0], &m_pInfo[DRAW_LOBBY][0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 2048, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pBytes[DRAW_LOBBY][0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glGenTextures(4, g_ivTextures[2]);
	glBindTexture(GL_TEXTURE_2D, g_ivTextures[2][0]);
	m_pBytes[2][0] = LoadDIBitmap(m_pszFilename[2][0], &m_pInfo[2][0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 800, 800, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pBytes[2][0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glGenTextures(4, g_ivTextures[DRAW_MONSTER]);
	//glBindTexture(GL_TEXTURE_2D, g_ivTextures[DRAW_MONSTER][0]);
	//m_pBytes[DRAW_MONSTER][0] = LoadDIBitmap(m_pszFilename[DRAW_MONSTER][0], &m_pInfo[DRAW_MONSTER][0]);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 2048, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pBytes[DRAW_MONSTER][0]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 36; j++)
		{
			//if (m_pMonsterBytes[i][j] == NULL)
				//continue; 

			m_pMonsterBytes[i][j] = LoadDIBitmap(m_pszMonsterFilename[i][j], &m_pInfo2);
		}
	}
	m_pBrick[0] = LoadDIBitmap("Texture/etc/_Brick.bmp", &m_pInfo2);
	m_pBrick[1] = LoadDIBitmap("Texture/etc/kpu_brick.bmp", &m_pInfo2);
	m_pBrick[2] = LoadDIBitmap("Texture/etc/clock.bmp", &m_pInfo2);

	m_pContainer[0] = LoadDIBitmap("Texture/Building/Container/side.bmp", &m_pInfo2);
	m_pContainer[1] = LoadDIBitmap("Texture/Building/Container/front.bmp", &m_pInfo2);

	m_pSkyBox[0] = LoadDIBitmap("Texture/etc/_left.bmp", &m_pInfo2);
	m_pSkyBox[1] = LoadDIBitmap("Texture/etc/_right.bmp", &m_pInfo2);
	m_pSkyBox[2] = LoadDIBitmap("Texture/etc/sky2.bmp", &m_pInfo2);
	m_pSkyBox[3] = LoadDIBitmap("Texture/etc/grass.bmp", &m_pInfo2);
	m_pSkyBox[4] = LoadDIBitmap("Texture/etc/_back.bmp", &m_pInfo2);

	//�ؽ�ó �Ķ���� ���� --- (4)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ؽ�ó ��� ����
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
	m_pszFilename[2][0] = "Texture/_result.bmp";
	m_pszFilename[2][1] = "Texture/_result.bmp";
	m_pszFilename[2][2] = "Texture/_result.bmp";
	m_pszFilename[2][3] = "Texture/_result.bmp";


	#pragma region MonsterTexture
m_pszMonsterFilename[MONSTER_SPIDER][0] = "Texture/Monster/Spider/��.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][1] = "Texture/Monster/Spider/�󱼿�����.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][2] = "Texture/Monster/Spider/�󱼵���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][3] = "Texture/Monster/Spider/�󱼿���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][4] = "Texture/Monster/Spider/�󱼾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][5] = "Texture/Monster/Spider/������.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][6] = "Texture/Monster/Spider/�������.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][7] = "Texture/Monster/Spider/���������.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][8] = "Texture/Monster/Spider/�������.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][9] = "Texture/Monster/Spider/�������.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][10] = "Texture/Monster/Spider/����Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][11] = "Texture/Monster/Spider/��������.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][12] = "Texture/Monster/Spider/���Ⱦ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][13] = "Texture/Monster/Spider/���ȿ�����.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][14] = "Texture/Monster/Spider/���ȵ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][15] = "Texture/Monster/Spider/���ȿ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][16] = "Texture/Monster/Spider/���ȾƷ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][17] = "Texture/Monster/Spider/��������.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][18] = "Texture/Monster/Spider/�����Ⱦ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][19] = "Texture/Monster/Spider/�����ȿ�����.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][20] = "Texture/Monster/Spider/�����ȵ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][21] = "Texture/Monster/Spider/�����ȿ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][22] = "Texture/Monster/Spider/�����ȾƷ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][23] = "Texture/Monster/Spider/����������.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][24] = "Texture/Monster/Spider/�޹߾���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][25] = "Texture/Monster/Spider/�޹߿�����.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][26] = "Texture/Monster/Spider/�޹ߵ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][27] = "Texture/Monster/Spider/�޹߿���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][28] = "Texture/Monster/Spider/�޹߾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][29] = "Texture/Monster/Spider/�޹�����.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][30] = "Texture/Monster/Spider/�����߾���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][31] = "Texture/Monster/Spider/�����߿�����.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][32] = "Texture/Monster/Spider/�����ߵ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][33] = "Texture/Monster/Spider/�����߿���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][34] = "Texture/Monster/Spider/�����߾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_SPIDER][35] = "Texture/Monster/Spider/����������.bmp";

	m_pszMonsterFilename[MONSTER_IRON][0] = "Texture/Monster/Iron/���̾��_�󱼾���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][1] = "Texture/Monster/Iron/���̾��_�󱼿�����.bmp";
	m_pszMonsterFilename[MONSTER_IRON][2] = "Texture/Monster/Iron/���̾��_�󱼵���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][3] = "Texture/Monster/Iron/���̾��_�󱼿���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][4] = "Texture/Monster/Iron/���̾��_�󱼾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][5] = "Texture/Monster/Iron/���̾��_������.bmp";
	m_pszMonsterFilename[MONSTER_IRON][6] = "Texture/Monster/Iron/���̾��_�������.bmp";
	m_pszMonsterFilename[MONSTER_IRON][7] = "Texture/Monster/Iron/���̾��_���������.bmp";
	m_pszMonsterFilename[MONSTER_IRON][8] = "Texture/Monster/Iron/���̾��_�������.bmp";
	m_pszMonsterFilename[MONSTER_IRON][9] = "Texture/Monster/Iron/���̾��_�������.bmp";
	m_pszMonsterFilename[MONSTER_IRON][10] = "Texture/Monster/Iron/���̾��_����Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][11] = "Texture/Monster/Iron/���̾��_��������.bmp";
	m_pszMonsterFilename[MONSTER_IRON][12] = "Texture/Monster/Iron/���̾��_���Ⱦ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][13] = "Texture/Monster/Iron/���̾��_���ȿ�����.bmp";
	m_pszMonsterFilename[MONSTER_IRON][14] = "Texture/Monster/Iron/���̾��_���ȵ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][15] = "Texture/Monster/Iron/���̾��_���ȿ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][16] = "Texture/Monster/Iron/���̾��_���ȾƷ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][17] = "Texture/Monster/Iron/���̾��_��������.bmp";
	m_pszMonsterFilename[MONSTER_IRON][18] = "Texture/Monster/Iron/���̾��_�����Ⱦ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][19] = "Texture/Monster/Iron/���̾��_�����ȿ�����.bmp";
	m_pszMonsterFilename[MONSTER_IRON][20] = "Texture/Monster/Iron/���̾��_�����ȵ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][21] = "Texture/Monster/Iron/���̾��_�����ȿ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][22] = "Texture/Monster/Iron/���̾��_�����ȾƷ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][23] = "Texture/Monster/Iron/���̾��_����������.bmp";
	m_pszMonsterFilename[MONSTER_IRON][24] = "Texture/Monster/Iron/���̾��_�޹߾���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][25] = "Texture/Monster/Iron/���̾��_�޹߿�����.bmp";
	m_pszMonsterFilename[MONSTER_IRON][26] = "Texture/Monster/Iron/���̾��_�޹ߵ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][27] = "Texture/Monster/Iron/���̾��_�޹߿���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][28] = "Texture/Monster/Iron/���̾��_�޹߾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][29] = "Texture/Monster/Iron/���̾��_�޹�����.bmp";
	m_pszMonsterFilename[MONSTER_IRON][30] = "Texture/Monster/Iron/���̾��_�����߾���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][31] = "Texture/Monster/Iron/���̾��_�����߿�����.bmp";
	m_pszMonsterFilename[MONSTER_IRON][32] = "Texture/Monster/Iron/���̾��_�����ߵ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][33] = "Texture/Monster/Iron/���̾��_�����߿���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][34] = "Texture/Monster/Iron/���̾��_�����߾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_IRON][35] = "Texture/Monster/Iron/���̾��_����������.bmp";

	m_pszMonsterFilename[MONSTER_SUPER][0] = "Texture/Monster/Super/���۸�_�󱼾���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][1] = "Texture/Monster/Super/���۸�_�󱼿�����.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][2] = "Texture/Monster/Super/���۸�_�󱼵���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][3] = "Texture/Monster/Super/���۸�_�󱼿���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][4] = "Texture/Monster/Super/���۸�_�󱼾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][5] = "Texture/Monster/Super/���۸�_������.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][6] = "Texture/Monster/Super/���۸�_�������.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][7] = "Texture/Monster/Super/���۸�_���������.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][8] = "Texture/Monster/Super/���۸�_�������.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][9] = "Texture/Monster/Super/���۸�_�������.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][10] = "Texture/Monster/Super/���۸�_����Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][11] = "Texture/Monster/Super/���۸�_��������.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][12] = "Texture/Monster/Super/���۸�_���Ⱦ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][13] = "Texture/Monster/Super/���۸�_���ȿ�����.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][14] = "Texture/Monster/Super/���۸�_���ȵ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][15] = "Texture/Monster/Super/���۸�_���ȿ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][16] = "Texture/Monster/Super/���۸�_���ȾƷ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][17] = "Texture/Monster/Super/���۸�_��������.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][18] = "Texture/Monster/Super/���۸�_�����Ⱦ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][19] = "Texture/Monster/Super/���۸�_�����ȿ�����.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][20] = "Texture/Monster/Super/���۸�_�����ȵ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][21] = "Texture/Monster/Super/���۸�_�����ȿ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][22] = "Texture/Monster/Super/���۸�_�����ȾƷ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][23] = "Texture/Monster/Super/���۸�_����������.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][24] = "Texture/Monster/Super/���۸�_�޹߾���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][25] = "Texture/Monster/Super/���۸�_�޹߿�����.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][26] = "Texture/Monster/Super/���۸�_�޹ߵ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][27] = "Texture/Monster/Super/���۸�_�޹߿���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][28] = "Texture/Monster/Super/���۸�_�޹߾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][29] = "Texture/Monster/Super/���۸�_�޹�����.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][30] = "Texture/Monster/Super/���۸�_�����߾���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][31] = "Texture/Monster/Super/���۸�_�����߿�����.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][32] = "Texture/Monster/Super/���۸�_�����ߵ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][33] = "Texture/Monster/Super/���۸�_�����߿���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][34] = "Texture/Monster/Super/���۸�_�����߾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_SUPER][35] = "Texture/Monster/Super/���۸�_����������.bmp";

	m_pszMonsterFilename[MONSTER_CAT][0] = "Texture/Monster/Cat/�����_�󱼾���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][1] = "Texture/Monster/Cat/�����_�󱼿�����.bmp";
	m_pszMonsterFilename[MONSTER_CAT][2] = "Texture/Monster/Cat/�����_�󱼵���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][3] = "Texture/Monster/Cat/�����_�󱼿���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][4] = "Texture/Monster/Cat/�����_�󱼾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][5] = "Texture/Monster/Cat/�����_������.bmp";
	m_pszMonsterFilename[MONSTER_CAT][6] = "Texture/Monster/Cat/�����_�������.bmp";
	m_pszMonsterFilename[MONSTER_CAT][7] = "Texture/Monster/Cat/�����_���������.bmp";
	m_pszMonsterFilename[MONSTER_CAT][8] = "Texture/Monster/Cat/�����_�������.bmp";
	m_pszMonsterFilename[MONSTER_CAT][9] = "Texture/Monster/Cat/�����_�������.bmp";
	m_pszMonsterFilename[MONSTER_CAT][10] = "Texture/Monster/Cat/�����_����Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][11] = "Texture/Monster/Cat/�����_��������.bmp";
	m_pszMonsterFilename[MONSTER_CAT][12] = "Texture/Monster/Cat/�����_���Ⱦ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][13] = "Texture/Monster/Cat/�����_���ȿ�����.bmp";
	m_pszMonsterFilename[MONSTER_CAT][14] = "Texture/Monster/Cat/�����_���ȵ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][15] = "Texture/Monster/Cat/�����_���ȿ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][16] = "Texture/Monster/Cat/�����_���ȾƷ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][17] = "Texture/Monster/Cat/�����_��������.bmp";
	m_pszMonsterFilename[MONSTER_CAT][18] = "Texture/Monster/Cat/�����_�����Ⱦ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][19] = "Texture/Monster/Cat/�����_�����ȿ�����.bmp";
	m_pszMonsterFilename[MONSTER_CAT][20] = "Texture/Monster/Cat/�����_�����ȵ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][21] = "Texture/Monster/Cat/�����_�����ȿ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][22] = "Texture/Monster/Cat/�����_�����ȾƷ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][23] = "Texture/Monster/Cat/�����_����������.bmp";
	m_pszMonsterFilename[MONSTER_CAT][24] = "Texture/Monster/Cat/�����_�޹߾���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][25] = "Texture/Monster/Cat/�����_�޹߿�����.bmp";
	m_pszMonsterFilename[MONSTER_CAT][26] = "Texture/Monster/Cat/�����_�޹ߵ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][27] = "Texture/Monster/Cat/�����_�޹߿���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][28] = "Texture/Monster/Cat/�����_�޹߾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][29] = "Texture/Monster/Cat/�����_�޹�����.bmp";
	m_pszMonsterFilename[MONSTER_CAT][30] = "Texture/Monster/Cat/�����_�����߾���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][31] = "Texture/Monster/Cat/�����_�����߿�����.bmp";
	m_pszMonsterFilename[MONSTER_CAT][32] = "Texture/Monster/Cat/�����_�����ߵ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][33] = "Texture/Monster/Cat/�����_�����߿���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][34] = "Texture/Monster/Cat/�����_�����߾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_CAT][35] = "Texture/Monster/Cat/�����_����������.bmp";

	m_pszMonsterFilename[MONSTER_SOLDIER][0] = "Texture/Monster/Soldier/����_�󱼾���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][1] = "Texture/Monster/Soldier/����_�󱼿�����.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][2] = "Texture/Monster/Soldier/����_�󱼵���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][3] = "Texture/Monster/Soldier/����_�󱼿���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][4] = "Texture/Monster/Soldier/����_�󱼾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][5] = "Texture/Monster/Soldier/����_������.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][6] = "Texture/Monster/Soldier/����_�������.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][7] = "Texture/Monster/Soldier/����_���������.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][8] = "Texture/Monster/Soldier/����_�������.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][9] = "Texture/Monster/Soldier/����_�������.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][10] = "Texture/Monster/Soldier/����_����Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][11] = "Texture/Monster/Soldier/����_��������.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][12] = "Texture/Monster/Soldier/����_���Ⱦ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][13] = "Texture/Monster/Soldier/����_���ȿ�����.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][14] = "Texture/Monster/Soldier/����_���ȵ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][15] = "Texture/Monster/Soldier/����_���ȿ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][16] = "Texture/Monster/Soldier/����_���ȾƷ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][17] = "Texture/Monster/Soldier/����_��������.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][18] = "Texture/Monster/Soldier/����_�����Ⱦ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][19] = "Texture/Monster/Soldier/����_�����ȿ�����.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][20] = "Texture/Monster/Soldier/����_�����ȵ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][21] = "Texture/Monster/Soldier/����_�����ȿ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][22] = "Texture/Monster/Soldier/����_�����ȾƷ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][23] = "Texture/Monster/Soldier/����_����������.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][24] = "Texture/Monster/Soldier/����_�޹߾���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][25] = "Texture/Monster/Soldier/����_�޹߿�����.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][26] = "Texture/Monster/Soldier/����_�޹ߵ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][27] = "Texture/Monster/Soldier/����_�޹߿���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][28] = "Texture/Monster/Soldier/����_�޹߾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][29] = "Texture/Monster/Soldier/����_�޹�����.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][30] = "Texture/Monster/Soldier/����_�����߾���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][31] = "Texture/Monster/Soldier/����_�����߿�����.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][32] = "Texture/Monster/Soldier/����_�����ߵ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][33] = "Texture/Monster/Soldier/����_�����߿���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][34] = "Texture/Monster/Soldier/����_�����߾Ʒ���.bmp";
	m_pszMonsterFilename[MONSTER_SOLDIER][35] = "Texture/Monster/Soldier/����_����������.bmp";
#pragma endregion MonsterTexture


	//MONSTER_IRON
	TextureInit();
}

GLuint* CBitmapMgr::GetTexture(SceneList _eScene)
{
		return g_ivTextures[_eScene];
}

GLubyte** CBitmapMgr::GetTexture(MonsterList _eMonster)
{
	return m_pMonsterBytes[_eMonster];

}

GLubyte* CBitmapMgr::GetTexture(int _Type, int _Texture)
{
	switch (_Type)
	{
	case 1:
		return m_pBrick[_Texture];
		break;
	case 2:
		return m_pSkyBox[_Texture];
		break;
	case 3:
		return m_pContainer[_Texture];
		break;
	default:
		break;
	}
	
}
