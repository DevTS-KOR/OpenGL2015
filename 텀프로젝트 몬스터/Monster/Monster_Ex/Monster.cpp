#include "stdafx.h"
#include "Monster.h"


Monster::Monster()
{
	init();
	SetupRC();

}


Monster::~Monster()
{
}

void Monster::init()
{
	Monster_Vec.fX = 0.0f;
	Monster_Vec.fY = 0.0f;
	Monster_Vec.fZ = 0.0f;
	fZ_left_arm = 0.0f;
	fZ_right_arm = 0.0f;
	fZ_left_leg = 0.0f;
	fZ_right_leg = 0.0f;
	fArm_move = 10.0f;
	fLeg_move = 5.0f;

}

void Monster::draw()
{


	glPushMatrix();
	//3���� �簢���� ����� �Լ�(x, y, z, �ʺ�, ����, ����, �׸��迭, �׸�x��, �׸�y��)
	glPushMatrix();
	//�Ӹ�
	Monster::Rect(0, 30, 0, 30, 30, 30, pFace, 64, 64);
	glPopMatrix();

	glPushMatrix();
	//����
	Monster::Rect(0, 0, 0, 30, 40, 15, pBody, 64, 64);
	glPopMatrix();

	glPushMatrix();
	//����
	glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_left_arm, 1, 0, 0);
	glTranslatef(0.f, -20.f, 0.0f);
	Monster::Rect(-22.5, 0, 0, 15, 40, 15, pLarm, 21, 64);

	glPopMatrix();

	glPushMatrix();
	//������
	glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_right_arm, 1, 0, 0);
	glTranslatef(0.f, -20.f, 0.0f);
	Monster::Rect(22.5, 0, 0, 15, 40, 15, pRarm, 21, 64);
	glPopMatrix();

	glPushMatrix();
	//�޴ٸ�
	//glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_left_leg, 1, 0, 0);
	//glTranslatef(0.f, -20.f, 0.0f);
	Monster::Rect(-7.5, -30, 0, 15, 40, 15, pLleg, 21, 64);
	glPopMatrix();

	glPushMatrix();
	//�����ٸ�
	//glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_right_leg, 1, 0, 0);
	//glTranslatef(0.f, -20.f, 0.0f);
	Monster::Rect(7.5, -30, 0, 15, 40, 15, pRleg, 21, 64);
	glPopMatrix();
	

	glPopMatrix();
	
}

GLubyte* Monster::LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// ���̳ʸ� �б� ���� ������ ����
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ���Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� ����.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
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
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

GLvoid Monster::SetupRC()
{
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);

	pFace[0] = Monster::LoadDIBitmap("skin\\�����_�󱼾���.bmp", &info);
	pFace[1] = Monster::LoadDIBitmap("skin\\�����_�󱼿�����.bmp", &info);
	pFace[2] = Monster::LoadDIBitmap("skin\\�����_�󱼵���.bmp", &info);
	pFace[3] = Monster::LoadDIBitmap("skin\\�����_�󱼿���.bmp", &info);
	pFace[4] = Monster::LoadDIBitmap("skin\\�����_�󱼾Ʒ���.bmp", &info);
	pFace[5] = Monster::LoadDIBitmap("skin\\�����_������.bmp", &info);
	pBody[0] = Monster::LoadDIBitmap("skin\\�����_�������.bmp", &info);
	pBody[1] = Monster::LoadDIBitmap("skin\\�����_���������.bmp", &info);
	pBody[2] = Monster::LoadDIBitmap("skin\\�����_�������.bmp", &info);
	pBody[3] = Monster::LoadDIBitmap("skin\\�����_�������.bmp", &info);
	pBody[4] = Monster::LoadDIBitmap("skin\\�����_����Ʒ���.bmp", &info);
	pBody[5] = Monster::LoadDIBitmap("skin\\�����_��������.bmp", &info);
	pLarm[0] = Monster::LoadDIBitmap("skin\\�����_���Ⱦ���.bmp", &info);
	pLarm[1] = Monster::LoadDIBitmap("skin\\�����_���ȿ�����.bmp", &info);
	pLarm[2] = Monster::LoadDIBitmap("skin\\�����_���ȵ���.bmp", &info);
	pLarm[3] = Monster::LoadDIBitmap("skin\\�����_���ȿ���.bmp", &info);
	pLarm[4] = Monster::LoadDIBitmap("skin\\�����_���ȾƷ���.bmp", &info);
	pLarm[5] = Monster::LoadDIBitmap("skin\\�����_��������.bmp", &info);
	pRarm[0] = Monster::LoadDIBitmap("skin\\�����_�����Ⱦ���.bmp", &info);
	pRarm[1] = Monster::LoadDIBitmap("skin\\�����_�����ȿ�����.bmp", &info);
	pRarm[2] = Monster::LoadDIBitmap("skin\\�����_�����ȵ���.bmp", &info);
	pRarm[3] = Monster::LoadDIBitmap("skin\\�����_�����ȿ���.bmp", &info);
	pRarm[4] = Monster::LoadDIBitmap("skin\\�����_�����ȾƷ���.bmp", &info);
	pRarm[5] = Monster::LoadDIBitmap("skin\\�����_����������.bmp", &info);
	pLleg[0] = Monster::LoadDIBitmap("skin\\�����_�޹߾���.bmp", &info);
	pLleg[1] = Monster::LoadDIBitmap("skin\\�����_�޹߿�����.bmp", &info);
	pLleg[2] = Monster::LoadDIBitmap("skin\\�����_�޹ߵ���.bmp", &info);
	pLleg[3] = Monster::LoadDIBitmap("skin\\�����_�޹߿���.bmp", &info);
	pLleg[4] = Monster::LoadDIBitmap("skin\\�����_�޹߾Ʒ���.bmp", &info);
	pLleg[5] = Monster::LoadDIBitmap("skin\\�����_�޹�����.bmp", &info);
	pRleg[0] = Monster::LoadDIBitmap("skin\\�����_�����߾���.bmp", &info);
	pRleg[1] = Monster::LoadDIBitmap("skin\\�����_�����߿�����.bmp", &info);
	pRleg[2] = Monster::LoadDIBitmap("skin\\�����_�����ߵ���.bmp", &info);
	pRleg[3] = Monster::LoadDIBitmap("skin\\�����_�����߿���.bmp", &info);
	pRleg[4] = Monster::LoadDIBitmap("skin\\�����_�����߾Ʒ���.bmp", &info);
	pRleg[5] = Monster::LoadDIBitmap("skin\\�����_����������.bmp", &info);
}


void Monster::Rect(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize)
{

	//�ո����
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glEnd();

	//������ ����
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[1]);
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glEnd();

	//�޸�
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[2]);
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glEnd();

	//���� ����
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[3]);
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glEnd();

	//�ظ����
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[4]);
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fX + (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fX - (fWidth / 2), fY - (fHigh / 2), fZ - (fDepth / 2));
	glEnd();

	//�������
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[5]);
	glColor3f(1.0f, 1.f, 1.f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ + (fDepth / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(fX + (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(fX - (fWidth / 2), fY + (fHigh / 2), fZ - (fDepth / 2));
	glEnd();
}
