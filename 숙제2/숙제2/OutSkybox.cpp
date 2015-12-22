#include "OutSkybox.h"
#pragma warning (disable:4996)

OutSkybox::OutSkybox()
{
	Init();
}


OutSkybox::~OutSkybox()
{
}

void OutSkybox::Init()
{

	////////////////////////////////////
	//앞면
	box[0].fX[0] = 400.f;
	box[0].fY[0] = -400.f;
	box[0].fZ[0] = 100.0f;
	box[0].fX[1] = -400.f;
	box[0].fY[1] = -400.f;
	box[0].fZ[1] = 100.f;
	box[0].fX[2] = -400.f;
	box[0].fY[2] = 400.f;
	box[0].fZ[2] = 100.0f;
	box[0].fX[3] = 400.f;
	box[0].fY[3] = 400.f;
	box[0].fZ[3] = 100.0f;


	//////////////////////////////////////
	//오른쪽 면
	box[1].fX[0] = 400.f;
	box[1].fY[0] = -400.f;
	box[1].fZ[0] = 100.0f;
	box[1].fX[1] = 400.f;
	box[1].fY[1] = 400.f;
	box[1].fZ[1] = 100.0f;
	box[1].fX[2] = 400.f;
	box[1].fY[2] = 400.f;
	box[1].fZ[2] = -700.f;
	box[1].fX[3] = 400.f;
	box[1].fY[3] = -400.f;
	box[1].fZ[3] = -700.f;
	///////////////////////////////////////
	//뒷면
	box[2].fX[0] = 400.f;
	box[2].fY[0] = -400.f;
	box[2].fZ[0] = -700.f;
	box[2].fX[1] = 400.f;
	box[2].fY[1] = 400.f;
	box[2].fZ[1] = -700.f;
	box[2].fX[2] = -400.f;
	box[2].fY[2] = 400.f;
	box[2].fZ[2] = -700.f;
	box[2].fX[3] = -400.f;
	box[2].fY[3] = -400.f;
	box[2].fZ[3] = -700.f;


	///////////////////////////////////////
	//왼쪽
	box[3].fX[0] = -400.f;
	box[3].fY[0] = -400.f;
	box[3].fZ[0] = -700.f;
	box[3].fX[1] = -400.f;
	box[3].fY[1] = 400.f;
	box[3].fZ[1] = -700.f;
	box[3].fX[2] = -400.f;
	box[3].fY[2] = 400.f;
	box[3].fZ[2] = 100.0f;
	box[3].fX[3] = -400.f;
	box[3].fY[3] = -400.f;
	box[3].fZ[3] = 100.0f;

	/////////////////////////////////////////
	//밑면
	box[4].fX[0] = 400.f;
	box[4].fY[0] = -400.f;
	box[4].fZ[0] = 100.0f;
	box[4].fX[1] = 400.f;
	box[4].fY[1] = -400.f;
	box[4].fZ[1] = -700.f;
	box[4].fX[2] = -400.f;
	box[4].fY[2] = -400.f;
	box[4].fZ[2] = -700.f;
	box[4].fX[3] = -400.f;
	box[4].fY[3] = -400.f;
	box[4].fZ[3] = 100.0f;

}

void OutSkybox::Draw()
{
	//텍스처 파라미터 설정 --- (4)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
	glEnable(GL_TEXTURE_2D);

	glTranslatef(0.0f, 0.f, 300.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 768, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(box[0].fX[0], box[0].fY[0], box[0].fZ[0]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(box[0].fX[1], box[0].fY[1], box[0].fZ[1]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(box[0].fX[2], box[0].fY[2], box[0].fZ[2]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(box[0].fX[3], box[0].fY[3], box[0].fZ[3]);
	glEnd();

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 768, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(box[1].fX[0], box[1].fY[0], box[1].fZ[0]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(box[1].fX[1], box[1].fY[1], box[1].fZ[1]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(box[1].fX[2], box[1].fY[2], box[1].fZ[2]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(box[1].fX[3], box[1].fY[3], box[1].fZ[3]);
	glEnd();

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 768, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(box[2].fX[0], box[2].fY[0], box[2].fZ[0]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(box[2].fX[1], box[2].fY[1], box[2].fZ[1]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(box[2].fX[2], box[2].fY[2], box[2].fZ[2]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(box[2].fX[3], box[2].fY[3], box[2].fZ[3]);
	glEnd();

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 768, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(box[3].fX[0], box[3].fY[0], box[3].fZ[0]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(box[3].fX[1], box[3].fY[1], box[3].fZ[1]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(box[3].fX[2], box[3].fY[2], box[3].fZ[2]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(box[3].fX[3], box[3].fY[3], box[3].fZ[3]);
	glEnd();

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 768, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(box[4].fX[0], box[4].fY[0], box[4].fZ[0]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(box[4].fX[1], box[4].fY[1], box[4].fZ[1]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(box[4].fX[2], box[4].fY[2], box[4].fZ[2]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(box[4].fX[3], box[4].fY[3], box[4].fZ[3]);
	glEnd();



	glTranslatef(0.0f, 0.f, -300.0f);
}


void OutSkybox::SetupRC()
{
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);

	pBytes[0] = OutSkybox::LoadDIBitmap("우주.bmp", &info);

}

GLubyte* OutSkybox::LoadDIBitmap(const char *filename, BITMAPINFO **info)
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