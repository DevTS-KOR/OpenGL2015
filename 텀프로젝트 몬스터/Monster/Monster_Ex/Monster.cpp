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
	//3차원 사각형을 만드는 함수(x, y, z, 너비, 높이, 깊이, 그림배열, 그림x값, 그림y값)
	glPushMatrix();
	//머리
	Monster::Rect(0, 30, 0, 30, 30, 30, pFace, 64, 64);
	glPopMatrix();

	glPushMatrix();
	//몸통
	Monster::Rect(0, 0, 0, 30, 40, 15, pBody, 64, 64);
	glPopMatrix();

	glPushMatrix();
	//왼팔
	glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_left_arm, 1, 0, 0);
	glTranslatef(0.f, -20.f, 0.0f);
	Monster::Rect(-22.5, 0, 0, 15, 40, 15, pLarm, 21, 64);

	glPopMatrix();

	glPushMatrix();
	//오른팔
	glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_right_arm, 1, 0, 0);
	glTranslatef(0.f, -20.f, 0.0f);
	Monster::Rect(22.5, 0, 0, 15, 40, 15, pRarm, 21, 64);
	glPopMatrix();

	glPushMatrix();
	//왼다리
	//glTranslatef(0.f, 20.f, 0.0f);
	glRotatef(fZ_left_leg, 1, 0, 0);
	//glTranslatef(0.f, -20.f, 0.0f);
	Monster::Rect(-7.5, -30, 0, 15, 40, 15, pLleg, 21, 64);
	glPopMatrix();

	glPushMatrix();
	//오른다리
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
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
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
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
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

	pFace[0] = Monster::LoadDIBitmap("skin\\고양이_얼굴앞쪽.bmp", &info);
	pFace[1] = Monster::LoadDIBitmap("skin\\고양이_얼굴오른쪽.bmp", &info);
	pFace[2] = Monster::LoadDIBitmap("skin\\고양이_얼굴뒤쪽.bmp", &info);
	pFace[3] = Monster::LoadDIBitmap("skin\\고양이_얼굴왼쪽.bmp", &info);
	pFace[4] = Monster::LoadDIBitmap("skin\\고양이_얼굴아래쪽.bmp", &info);
	pFace[5] = Monster::LoadDIBitmap("skin\\고양이_얼굴위쪽.bmp", &info);
	pBody[0] = Monster::LoadDIBitmap("skin\\고양이_몸통앞쪽.bmp", &info);
	pBody[1] = Monster::LoadDIBitmap("skin\\고양이_몸통오른쪽.bmp", &info);
	pBody[2] = Monster::LoadDIBitmap("skin\\고양이_몸통뒤쪽.bmp", &info);
	pBody[3] = Monster::LoadDIBitmap("skin\\고양이_몸통왼쪽.bmp", &info);
	pBody[4] = Monster::LoadDIBitmap("skin\\고양이_몸통아래쪽.bmp", &info);
	pBody[5] = Monster::LoadDIBitmap("skin\\고양이_몸통위쪽.bmp", &info);
	pLarm[0] = Monster::LoadDIBitmap("skin\\고양이_왼팔앞쪽.bmp", &info);
	pLarm[1] = Monster::LoadDIBitmap("skin\\고양이_왼팔오른쪽.bmp", &info);
	pLarm[2] = Monster::LoadDIBitmap("skin\\고양이_왼팔뒤쪽.bmp", &info);
	pLarm[3] = Monster::LoadDIBitmap("skin\\고양이_왼팔왼쪽.bmp", &info);
	pLarm[4] = Monster::LoadDIBitmap("skin\\고양이_왼팔아래쪽.bmp", &info);
	pLarm[5] = Monster::LoadDIBitmap("skin\\고양이_왼팔위쪽.bmp", &info);
	pRarm[0] = Monster::LoadDIBitmap("skin\\고양이_오른팔앞쪽.bmp", &info);
	pRarm[1] = Monster::LoadDIBitmap("skin\\고양이_오른팔오른쪽.bmp", &info);
	pRarm[2] = Monster::LoadDIBitmap("skin\\고양이_오른팔뒤쪽.bmp", &info);
	pRarm[3] = Monster::LoadDIBitmap("skin\\고양이_오른팔왼쪽.bmp", &info);
	pRarm[4] = Monster::LoadDIBitmap("skin\\고양이_오른팔아래쪽.bmp", &info);
	pRarm[5] = Monster::LoadDIBitmap("skin\\고양이_오른팔위쪽.bmp", &info);
	pLleg[0] = Monster::LoadDIBitmap("skin\\고양이_왼발앞쪽.bmp", &info);
	pLleg[1] = Monster::LoadDIBitmap("skin\\고양이_왼발오른쪽.bmp", &info);
	pLleg[2] = Monster::LoadDIBitmap("skin\\고양이_왼발뒤쪽.bmp", &info);
	pLleg[3] = Monster::LoadDIBitmap("skin\\고양이_왼발왼쪽.bmp", &info);
	pLleg[4] = Monster::LoadDIBitmap("skin\\고양이_왼발아래쪽.bmp", &info);
	pLleg[5] = Monster::LoadDIBitmap("skin\\고양이_왼발위쪽.bmp", &info);
	pRleg[0] = Monster::LoadDIBitmap("skin\\고양이_오른발앞쪽.bmp", &info);
	pRleg[1] = Monster::LoadDIBitmap("skin\\고양이_오른발오른쪽.bmp", &info);
	pRleg[2] = Monster::LoadDIBitmap("skin\\고양이_오른발뒤쪽.bmp", &info);
	pRleg[3] = Monster::LoadDIBitmap("skin\\고양이_오른발왼쪽.bmp", &info);
	pRleg[4] = Monster::LoadDIBitmap("skin\\고양이_오른발아래쪽.bmp", &info);
	pRleg[5] = Monster::LoadDIBitmap("skin\\고양이_오른발위쪽.bmp", &info);
}


void Monster::Rect(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize)
{

	//앞면생성
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

	//오른쪽 옆면
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

	//뒷면
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

	//왼쪽 옆면
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

	//밑면생성
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

	//윗면생성
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
