#pragma warning (disable:4996)
#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <windows.h>
using namespace std;

#define PI 3.141592

class Bullet
{
public:
	float fX;
	float fY;
	float fZ;
	float fXrot;
	float fYrot;
	float xDir;
	float yDir;
	float zDir;

	Bullet(float _fX, float _fY, float _fZ)
	{
		fX = _fX;
		fY = _fY;
		fZ = _fZ;
	}

	Bullet(float _fX, float _fY, float _fZ, float xTar, float yTar, float zTar/* float _fXrot, float _fYrot*/)
	{
		fX = _fX;
		fY = _fY;
		fZ = _fZ;
		xDir = xTar - fX;
		yDir = yTar - fY;
		zDir = zTar - fZ;

		float len = sqrt(xDir * xDir + yDir * yDir + zDir * zDir);
		xDir /= len;
		yDir /= len;
		zDir /= len;

		fXrot = 0;//_fXrot;
		fYrot = 0;//_fYrot;
	}
	void Update()
	{
		fX += xDir * 10;
		fY += yDir * 10;
		fZ += zDir * 10;
	}
};

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void mouseMovement(int x, int y);
void Timer(int value);
void camera(void);

float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle = 0.0;

float lastx, lasty;
int diffx;
int diffy;
GLvoid SetupRC();
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
GLubyte *pGun_top[6];
GLubyte *pGun_mid[6];
GLubyte *pGun_bottom[6];
BITMAPINFO *info;
GLuint* textures;
void Rect2(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize);

bool Up_Key = false, Down_Key = false, Left_Key = false, Right_Key = false;
vector<Bullet> bullet;
float fSniper = 0.f;
float fYrotate = 0.0f;
float fZtr = 0.0f;

bool Sniper_mode = false;

float camxrotate = 0, camyrotate = -90, Viewx = 0, Viewy = 0, Viewz = -1000, Camx, Camy, Camz;
float Charx = 0, Charz = 0, Chary = 0;
float nx = 0, ny = 0, bx = 0, by = 0;
float testx = 0, texty = 0;
int Charspeed = 2, Camdistance = 0, MouseSens = 300;

void main()
{
	//초기화 함수들
	SetupRC();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("플레이어 구현부");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutTimerFunc(10, Timer, 1);
	glutPassiveMotionFunc(mouseMovement);
	glutMouseFunc(Mouse);
	glutMotionFunc(mouseMovement);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glViewport(0, 0, 800, 800);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1, 0.1, 5000.0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	//ShowCursor(FALSE);
	glLoadIdentity();


	glPushMatrix();

	//저격모드 추가
	if (Sniper_mode == true)
	{
		fSniper = -150.f;
		//gluLookAt(0.0, 0.0, fSniper, Charx + Viewx * 2, Chary + Viewy * 2, Charz + Viewz, 0.0, 1.0, 0.0);
	}

	else
		fSniper = 0.f;


	//카메라
	gluLookAt(Charx, Chary, Charz + fSniper, Charx + Viewx * 2, Chary + Viewy * 2, Charz + Viewz + fSniper, 0.0, 1.0, 0.0);

	glPushMatrix();
	//움직임 확인 육면체
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -200.f);
	glutSolidCube(10);
	glTranslatef(0.0f, -25.f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(10);
	glTranslatef(0.0f, 25.f, 200.0f);
	glPopMatrix();



	glPushMatrix();
	//총알의 날아가는 좌표
	for (auto iter = bullet.begin(); iter != bullet.end(); ++iter)
	{
		glPushMatrix();

		glRotatef(-iter->fXrot, 1, 0, 0);
		glRotatef(-iter->fYrot, 0, 1, 0);
		glTranslatef(iter->fX, iter->fY, iter->fZ);

		glColor3f(0.0f, 1.0f, 0.0f);
		glutSolidCube(2);
		glPopMatrix();

	}


	glPopMatrix();
	if (Up_Key == true)
	{
		Charx += Charspeed * cos((-camxrotate - 90) * PI / 180);
		Charz += Charspeed * sin((-camxrotate - 90) * PI / 180);
	}


	if (Down_Key == true)
	{
		Charx -= Charspeed * cos((-camxrotate - 90) * PI / 180);
		Charz -= Charspeed * sin((-camxrotate - 90) * PI / 180);
	}

	if (Left_Key == true)
	{
		Charx -= Charspeed * cos((-camxrotate) * PI / 180);
		Charz -= Charspeed * sin((-camxrotate) * PI / 180);
	}

	if (Right_Key == true)
	{
		Charx += Charspeed * cos((-camxrotate) * PI / 180);
		Charz += Charspeed * sin((-camxrotate) * PI / 180);
	}
	glPopMatrix();
	


	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	glOrtho(0.0, 800.0, 0.0, 800.0, -100.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	//텍스처 파라미터 설정 --- (4)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
	glEnable(GL_TEXTURE_2D);

	//가운데 중앙 총
	if (Sniper_mode == false)
	{
		glTranslated(370, 20, 0);
		glRotatef(45.f, 1, 0, 0);
		Rect2(25, 28, 0, 75, 30, 110, pGun_top, 25, 17);
	}

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	glPushMatrix();
	if (Sniper_mode == false)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		glLineWidth(5);

		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(300, 400, 0.0);
		glVertex3f(380, 400, 0.0);
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(420, 400, 0.0);
		glVertex3f(500, 400, 0.0);
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(400, 300, 0.0);
		glVertex3f(400, 380, 0.0);
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(400, 420, 0.0);
		glVertex3f(400, 500, 0.0);
		glEnd();
	}

	else if (Sniper_mode == true)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(400.0f, 400.0f, -1.f);
		glutSolidTorus(100, 475, 400, 400);
		glTranslatef(-400.0f, -400.0f, -1.f);

		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex3f(-800.f, 400.0f, -1.0);
		glVertex3f(800.f, 400.0f, -1.0);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(400.f, -800.0f, -1.0);
		glVertex3f(400.f, 800.0f, -1.0);
		glEnd();
	}

	glPopMatrix();
	glPopMatrix();

	//glFlush();
	glutSwapBuffers();		//결과 출력
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, w / h, 0.1, 5000.0);
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{

	if (key == 'q')
	{
		xrot += 1;
		if (xrot > 360) xrot -= 360;
	}

	if (key == 'z')
	{
		xrot -= 1;
		if (xrot < -360) xrot += 360;
	}

	if (key == 'w')
		Up_Key = true;

	if (key == 's')
		Down_Key = true;

	if (key == 'a')
		Left_Key = true;

	if (key == 'd')
		Right_Key = true;

	//////////////////////////////////

	if (key == 27)
	{
		exit(0);
	}

	if (key == '7')
		fYrotate += 10.f;

	if (key == '8')
		fZtr -= 10.f;

	if (key == '0')
		glutFullScreen();

	else if (key == '9')
		glutReshapeWindow(800, 800);

	else if (key == '1')
		Sniper_mode = false;

	else if (key == '2')
		Sniper_mode = true;

	else if (key == 'b')
		fSniper -= 10.f;

	glutPostRedisplay();

}

void KeyboardUp(unsigned char key, int x, int y)
{

	if (key == 'w')
		Up_Key = false;

	if (key == 's')
		Down_Key = false;

	if (key == 'a')
		Left_Key = false;

	if (key == 'd')
		Right_Key = false;

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		/*float sz = -10 * sin((camyrotate)* PI / 180) *cos((camxrotate)* PI / 180);
		float sx = 10 * cos((camyrotate)* PI / 180) * sin((camxrotate)* PI / 180);
		float sy = -10 * cos((camyrotate)* PI / 180);*/
		//cout << Charx << "// " << Chary << "// " << Charz << endl;
		//cout << Charx + Viewx * 2 <<  " // " << Chary + Viewy * 2 << " // " << Charz + Viewz << endl;
		bullet.push_back(Bullet(Charx + Viewx , Chary + Viewy , Charz + Viewz/2, Charx + Viewx * 2, Chary + Viewy * 2 , Charz + Viewz));

	}

}


void Timer(int value)
{

	for (auto iter = bullet.begin(); iter != bullet.end(); ++iter)
	{
		iter->Update();
	}

	glutTimerFunc(10, Timer, 1);
	glutPostRedisplay();
}



void mouseMovement(int x, int y)
{
	float mx = 400 - x;
	float my = 400 - y;

	nx = (mx);
	ny = (my);

	if ((abs(nx) < 100 && abs(ny) < 100))
	{
		nx = 0, ny = 0;
	}

	camxrotate = camxrotate + (nx*0.5 / MouseSens);
	camyrotate = camyrotate + (ny*0.5 / MouseSens);

	Viewz = 10 * sin((camyrotate)* PI / 180) * cos((camxrotate)* PI / 180);
	Viewx = 10 * sin((camyrotate)* PI / 180) * sin((camxrotate)* PI / 180);
	Viewy = 10 * cos((camyrotate)* PI / 180);


	Camz = -Camdistance * sin((camyrotate)* PI / 180) * cos((camxrotate)* PI / 180);
	Camx = -Camdistance * sin((camyrotate)* PI / 180) * sin((camxrotate)* PI / 180);
	Camy = -Camdistance * cos((camyrotate)* PI / 180);


	if (camxrotate <= -360 || camxrotate >= 360)
		camxrotate = 0;

	if (camyrotate < -179)
		camyrotate = -179;
	else if (camyrotate > -1)
		camyrotate = -1;

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

	pGun_top[0] = LoadDIBitmap("skin\\탑총_뒤쪽.bmp", &info);
	pGun_top[1] = LoadDIBitmap("skin\\탑총_오른쪽.bmp", &info);
	pGun_top[2] = LoadDIBitmap("skin\\탑총_뒤쪽.bmp", &info);
	pGun_top[3] = LoadDIBitmap("skin\\탑총_왼쪽.bmp", &info);
	pGun_top[4] = LoadDIBitmap("skin\\탑총_아래쪽.bmp", &info);
	pGun_top[5] = LoadDIBitmap("skin\\탑총_위쪽.bmp", &info);
}

//x좌표, y좌표, z좌표, 너비, 높이, 깊이, 텍스처배열, 텍스처x사이즈, 텍스처y사이즈
void Rect2(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize)
{
	//앞면생성
	glTexImage2D(GL_TEXTURE_2D, 0, 3, fXsize, fYsize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glColor3f(0.0f, 0.8f, 1.0f);
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
	glColor3f(0.0f, 0.8f, 1.0f);
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
	glColor3f(0.0f, 0.8f, 1.0f);
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
	glColor3f(0.0f, 0.8f, 1.0f);
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
	glColor3f(0.0f, 0.8f, 1.0f);
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
	glColor3f(0.0f, 0.8f, 1.0f);
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
