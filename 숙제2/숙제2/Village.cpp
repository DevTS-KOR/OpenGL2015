#include "Village.h"
#pragma warning (disable:4996)

Village::Village()
{
	Init();
}


Village::~Village()
{
}


void Village::Init()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		fColor = 32767;
		fRed[i] = rand() / fColor;
		fBlue[i] = rand() / fColor;
		fGreen[i] = rand() / fColor;

		//��ǥ ���� �ʱ�ȭ
		fX[i] = rand() % 500 - 250;
		fY[i] = -300.f;
		fZ[i] = randomRange(-450, -150);

		
		for (int j = 0; j < i; j++)
		{
			if (fX[j] + 25 > fX[i] - 25 && fX[j] - 25 < fX[i] + 25 && fZ[j] + 25 > fZ[i] - 25 && fZ[j] - 25 < fZ[i] + 25)
			{
				i = 0;
			}
		}

		//ť�� ����ũ�� �ʱ�ȭ
		fScale_Y[i] = rand() % 4 + 1;
	}
}

int Village::randomRange(int n1, int n2)
{
	return (int)(rand() % (n2 - n1 + 1)) + n1;
}


void Village::Draw()
{
	//�ؽ�ó �Ķ���� ���� --- (4)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
	glEnable(GL_TEXTURE_2D);


	glTranslatef(0.0f, 0.f, 300.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 446, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-300.f, -300.0f, -100.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(300.f, -300.0f, -100.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(300.f, -300.0f, -500.f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-300.f, -300.0f, -500.f);
	glEnd();
	glTranslatef(0.0f, 0.f, -300.0f);
	

	for (int i = 0; i < 10; i++)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.f, 300.0f);
		glTranslatef(fX[i], fY[i], fZ[i]);
		glScalef(1, fScale_Y[i], 1);
		glColor3f(fRed[i], fGreen[i], fBlue[i]);
		glutSolidCube(50);
		glScalef(1, -fScale_Y[i], 1);
		glTranslatef(0.0f, 0.f, -300.0f);
		glPopMatrix();
	}



}

void Village::SetupRC()
{
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);

	pBytes[0] = Village::LoadDIBitmap("�ܵ�.bmp", &info);

}

GLubyte* Village::LoadDIBitmap(const char *filename, BITMAPINFO **info)
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