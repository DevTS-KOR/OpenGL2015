#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#pragma warning (disable:4996)


typedef struct Vertex
{
	float fX;
	float fY;
	float fZ;
}Vertex;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void init();

Vertex One_Vertex[4];
Vertex Two_Vertex[4];
Vertex Three_Vertex[4];
Vertex Four_Vertex[4];
Vertex Five_Vertex[4];
Vertex Six_Vertex[4];

bool Depth = true;
bool Culling = true;
bool Shade = true;
bool TopQuads = true;
bool FrontQuads = true;

GLint SubMenu1, SubMenu2, SubMenu3, SubMenu4, SubMenu5, MainMenu;
void MenuFunc(int button);
float fRotate = 0.f;
void TimerFunc(int value);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid SetupRC();
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);


GLubyte *pBytes[6];
BITMAPINFO *info;
GLuint* textures;

void main()
{
	//초기화 함수들
	init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-32");
	SetupRC();
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutTimerFunc(100, TimerFunc, 1);
	glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);

	if (Depth == true)
		glEnable(GL_DEPTH_TEST);
	else if (Depth == false)
		glDisable(GL_DEPTH_TEST);

	if (Culling == true)
		glEnable(GL_CULL_FACE);
	else if (Culling == false)
		glDisable(GL_CULL_FACE);

	if (Shade == true)
		glShadeModel(GL_SMOOTH);
	else if (Shade == false)
		glShadeModel(GL_FLAT);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 500.0f, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

	glRotatef(30.f, 1.f, 0.f, 0.f);
	glRotatef(-45.f, 0.f, 1.f, 0.f);

	glRotatef(fRotate, 0.f, 1.f, 0.f);

	//6개의 텍스처 만들고 이미지 결합하기
	//glGenTextures(6, *textures);

	//6개의 이미지 텍스처 매핑을 한다.
	//glGenTextures(6, textures);

	//텍스처와 객체를 결합한다.	--- (1)
	//glGenTextures(GL_TEXTURE_2D, textures[0]);

	//이미지 로딩을 한다.		--- (2)
	//SetupRC()
	
	//텍스처 설정 정의를 한다.	--- (3)
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 336, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);

	//텍스처 파라미터 설정 --- (4)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
	glEnable(GL_TEXTURE_2D);
	// 텍스처를 객체에 맵핑
	//glBindTexture(GL_TEXTURE_2D, name[0]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(One_Vertex[0].fX, One_Vertex[0].fY, One_Vertex[0].fZ);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(One_Vertex[1].fX, One_Vertex[1].fY, One_Vertex[1].fZ);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(One_Vertex[2].fX, One_Vertex[2].fY, One_Vertex[2].fZ);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(One_Vertex[3].fX, One_Vertex[3].fY, One_Vertex[3].fZ);
	glEnd();


	
	if (FrontQuads == true)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 341, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[1]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(Two_Vertex[0].fX, Two_Vertex[0].fY, Two_Vertex[0].fZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(Two_Vertex[0].fX, Two_Vertex[1].fY, Two_Vertex[1].fZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(Two_Vertex[0].fX, Two_Vertex[2].fY, Two_Vertex[2].fZ);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(Two_Vertex[0].fX, Two_Vertex[3].fY, Two_Vertex[3].fZ);
		glEnd();
	}

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 341, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[2]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(Three_Vertex[0].fX, Three_Vertex[0].fY, Three_Vertex[0].fZ);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(Three_Vertex[1].fX, Three_Vertex[1].fY, Three_Vertex[1].fZ);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(Three_Vertex[2].fX, Three_Vertex[2].fY, Three_Vertex[2].fZ);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(Three_Vertex[3].fX, Three_Vertex[3].fY, Three_Vertex[3].fZ);
	glEnd();

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 343, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(Four_Vertex[0].fX, Four_Vertex[0].fY, Four_Vertex[0].fZ);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(Four_Vertex[1].fX, Four_Vertex[1].fY, Four_Vertex[1].fZ);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(Four_Vertex[2].fX, Four_Vertex[2].fY, Four_Vertex[2].fZ);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(Four_Vertex[3].fX, Four_Vertex[3].fY, Four_Vertex[3].fZ);
	glEnd();

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 341, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(Five_Vertex[0].fX, Five_Vertex[0].fY, Five_Vertex[0].fZ);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(Five_Vertex[1].fX, Five_Vertex[1].fY, Five_Vertex[1].fZ);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(Five_Vertex[2].fX, Five_Vertex[2].fY, Five_Vertex[2].fZ);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(Five_Vertex[3].fX, Five_Vertex[3].fY, Five_Vertex[3].fZ);
	glEnd();

	if (TopQuads == true)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 341, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[5]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(Six_Vertex[0].fX, Six_Vertex[0].fY, Six_Vertex[0].fZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(Six_Vertex[1].fX, Six_Vertex[1].fY, Six_Vertex[1].fZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(Six_Vertex[2].fX, Six_Vertex[2].fY, Six_Vertex[2].fZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(Six_Vertex[3].fX, Six_Vertex[3].fY, Six_Vertex[3].fZ);
		glEnd();
	}

	//glFlush();
	glutSwapBuffers();		//결과 출력
}

GLvoid Reshape(int w, int h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);	
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	//gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	//glMatrixMode(GL_MODELVIEW);
}

void init()
{
	One_Vertex[3] = { -50.f, -50.f, 50.f };
	One_Vertex[2] = { 50.f, -50.f, 50.f };
	One_Vertex[1] = { 50.f, -50.f, -50.f };
	One_Vertex[0] = { -50.f, -50.f, -50.f };

	Two_Vertex[0] = { 50.f, -50.f, 50.f };
	Two_Vertex[1] = { 50.f, -50.f, -50.f };
	Two_Vertex[2] = { 50.f, 50.f, -50.f };
	Two_Vertex[3] = { 50.f, 50.f, 50.f };

	Three_Vertex[0] = { 50.f, -50.f, -50.f };
	Three_Vertex[1] = { -50.f, -50.f, -50.f };
	Three_Vertex[2] = { -50.f, 50.f, -50.f };
	Three_Vertex[3] = { 50.f, 50.f, -50.f };

	Four_Vertex[0] = { -50.f, -50.f, -50.f };
	Four_Vertex[1] = { -50.f, -50.f, 50.f };
	Four_Vertex[2] = { -50.f, 50.f, 50.f };
	Four_Vertex[3] = { -50.f, 50.f, -50.f };

	Five_Vertex[0] = { -50.f, -50.f, 50.f };
	Five_Vertex[1] = { 50.f, -50.f, 50.f };
	Five_Vertex[2] = { 50.f, 50.f, 50.f };
	Five_Vertex[3] = { -50.f, 50.f, 50.f };

	Six_Vertex[0] = { -50.f, 50.f, 50.f };
	Six_Vertex[1] = { 50.f, 50.f, 50.f };
	Six_Vertex[2] = { 50.f, 50.f, -50.f };
	Six_Vertex[3] = { -50.f, 50.f, -50.f };

}
GLvoid Mouse(int button, int state, int x, int y)
{
	SubMenu1 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);
	SubMenu2 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("On", 3);
	glutAddMenuEntry("Off", 4);
	SubMenu3 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("On", 5);
	glutAddMenuEntry("Off", 6);
	SubMenu4 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("On", 7);
	glutAddMenuEntry("Off", 8);
	SubMenu5 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("On", 9);
	glutAddMenuEntry("Off", 10);

	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("은면제거", SubMenu1);
	glutAddSubMenu("컬링", SubMenu2);
	glutAddSubMenu("쉐이딩", SubMenu3);
	glutAddSubMenu("윗면", SubMenu4);
	glutAddSubMenu("앞면", SubMenu5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutPostRedisplay();
}

void MenuFunc(int button)
{


	switch (button)
	{
	case 1:
		Depth = true;
		break;
	case 2:
		Depth = false;
		break;
	case 3:
		Culling = true;
		break;
	case 4:
		Culling = false;
		break;
	case 5:
		Shade = true;
		break;
	case 6:
		Shade = false;
		break;
	case 7:
		TopQuads = true;
		break;
	case 8:
		TopQuads = false;
		break;
	case 9:
		FrontQuads = true;
		break;
	case 10:
		FrontQuads = false;
		break;
	}

	glutPostRedisplay();
}

void TimerFunc(int value)
{
	fRotate += 10.f;

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info)
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

GLvoid SetupRC()
{
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);

	pBytes[0] = LoadDIBitmap("3-32 네덜란드기.bmp", &info);
	pBytes[1] = LoadDIBitmap("3-32 일장기.bmp", &info);
	pBytes[2] = LoadDIBitmap("3-32 중국기.bmp", &info);
	pBytes[3] = LoadDIBitmap("3-32 성조기.bmp", &info);
	pBytes[4] = LoadDIBitmap("3-32 태극기.bmp", &info);
	pBytes[5] = LoadDIBitmap("3-32 영국기.bmp", &info);
}
