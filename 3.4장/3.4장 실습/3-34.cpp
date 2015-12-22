#pragma warning (disable:4996)
#include <gl/glut.h>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

typedef struct strGround
{
	float fX[60][60];
	float fY[60][60];
	float fZ[60][60];
}strGround;

typedef struct Crash
{
	float fCenter_X[4];
	float fCenter_Y[4];
	float fCenter_Z[4];
	float fRadius[4];
	float fCrash[4];
}Crash;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void TimerFunc(int value);
double randomDouble(void)
{
	return (double)rand() / RAND_MAX;
}

void Road();
void First_Rect();
void Second_Rect();
void Third_Rect();
void fourth_Rect();
void fifth_Rect();
void sixth_Rect();
void seventh_Rect();
void RoundBox();
void Player();


float yyy = 0.0f;
float yyy1 = 10.f;
strGround Ground;
Crash strCrash;


float fZoom = 800.f;
float fZoom_Plus = 10.f;
float fRotate_X = 0.0f;
float fRotate_Y = 0.0f;
float fRotate_Plus_X = 10.f;
float fRotate_Plus_Y = 10.f;
float fPlayer_X = 0.0f;
float fPlayer_Z = 0.f;
float fPlayer_Plus_X = 5.f;
float fPlayer_Plus_Z = 5.f;

float fPlayer_Center_X = 0.0f;
float fPlayer_Center_Y = 0.0f;
float fPlayer_Center_Z = 0.0f;
float fPlayer_Radius = 0.0f;
float fPlayer_to_Rect_Radius[4];
bool bCrash = false;

float fAmbient_Light = 3.0f;
float fAmbient_Light2 = 3.0f;
float fAmbient_Light3 = 3.0f;
float fDiffuse_Light = 0.8f;
float fDiffuse_Light2 = 0.8f;
float fDiffuse_Light3 = 0.8f;
float fSpecre_f = 0.2f;
float fAmbient_Plus = 0.1f;
float fDiffuse_Plus = 0.1f;


GLvoid SetupRC();
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

GLubyte *pBytes[4];
BITMAPINFO *info;
GLuint* textures;

void main()
{
	//초기화 함수들
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			Ground.fX[i][j] = -300.0f + (10 * j);
			Ground.fY[i][j] = -500.0f + (10 * i);
			Ground.fZ[i][j] = 0.0f;
		}
	}
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-34");
	SetupRC();
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutTimerFunc(100, TimerFunc, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glLoadIdentity();
	gluLookAt(0.0, yyy, fZoom, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

	glRotatef(fRotate_X, 1.0f, 0.0f, 0.0f);
	glRotatef(fRotate_Y, 0.0f, 1.0f, 0.0f);

	GLfloat diffuseLight[] = { fDiffuse_Light, fDiffuse_Light2, fDiffuse_Light3, 1.0f };
	GLfloat ambientLight[] = { fAmbient_Light, fAmbient_Light2, fAmbient_Light3, 1.0f };
	GLfloat specref[] = { fSpecre_f, fSpecre_f, fSpecre_f, 1.0f };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);

	GLfloat lightPos[] = { 0, 300.f, 0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//텍스처 설정 정의를 한다.	--- (3)
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);

	//텍스처 파라미터 설정 --- (4)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	
	glTranslatef(0.0f, -300.f, 0.0f);
	RoundBox();
	glRotatef(-90.f, 1.0f, 0.0f, 0.0f);
	Road();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-250.f, -175.0f, 100.0f);
	First_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslated(270.f, -255.0f, 300.0f);
	Second_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250.f, -250.f, 150.f);
	Third_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-250.f, -250.f, 200.f);
	fourth_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100.f, -200.f, 0.f);
	fifth_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, -100.f, 0.f);
	sixth_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100.f, -200.f, 0.f);
	seventh_Rect();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, -250.f, 0.f);
	glTranslatef(fPlayer_X, 0.0f, fPlayer_Z);
	Player();
	glPopMatrix();
	//glFlush();
	glutSwapBuffers();		//결과 출력
}

GLvoid Reshape(int w, int h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);	
	gluPerspective(60.0, 1.0, 1.0, 3000.0);
	//gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	//glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'x')
		fRotate_X += fRotate_Plus_X;

	else if (key == 'X')
		fRotate_X -= fRotate_Plus_X;

	else if (key == 'y')
		fRotate_Y += fRotate_Plus_Y;

	else if (key == 'Y')
		fRotate_Y -= fRotate_Plus_Y;

	else if (key == 'Z')
		fZoom -= fZoom_Plus;

	else if (key == 'z')
		fZoom += fZoom_Plus;

	else if (key == 'q')
		yyy -= yyy1;

	else if (key == 'Q')
		yyy += yyy1;


	glutPostRedisplay();

}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		fPlayer_X -= fPlayer_Plus_X;

	}
	else if (key == GLUT_KEY_RIGHT)
	{
		fPlayer_X += fPlayer_Plus_X;

	}

	else if (key == GLUT_KEY_UP)
	{
		fPlayer_Z -= fPlayer_Plus_Z;
	}

	else if (key == GLUT_KEY_DOWN)
	{
		fPlayer_Z += fPlayer_Plus_Z;
	}

	glutPostRedisplay();

}

void TimerFunc(int value)
{

	//if (fAmbient_Light >= 1.0f || fAmbient_Light <= 0.0f)
		//fAmbient_Plus *= -1;

	//fAmbient_Light += fAmbient_Plus;
	//fAmbient_Light2 += fAmbient_Plus;
	//fAmbient_Light3 += fAmbient_Plus;

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

void Road()
{
	//glColor3f(0.2f, 0.2f, 0.2f);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 692, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(Ground.fX[i][j], Ground.fY[i][j], 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(Ground.fX[i][j] + 10.f, Ground.fY[i][j], 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(Ground.fX[i][j] + 10.f, Ground.fY[i][j] + 10.f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(Ground.fX[i][j], Ground.fY[i][j] + 10.f, 0.0f);

		}
	}
	glEnd();
}

void First_Rect()
{
	glColor3f(0.f, 0.f, 0.8f);
	glScalef(1.0f, 5.f, 1.f);
	glutSolidCube(50);

	//glTranslated(0.f, -100.0f, 0.0f);
	glScalef(1.0f, 0.2f, 1.f);
	glLineWidth(3);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-25.f, -125.f, 25.f);
	glVertex3f(25.f, -125.f, 25.f);
	glVertex3f(25.f, 125.f, 25.f);
	glVertex3f(-25.f, 125.f, 25.f);
	glVertex3f(-25.f, -125.f, 25.f);
	glVertex3f(-25.f, -125.f, -25.f);
	glVertex3f(25.f, -125.f, -25.f);
	glVertex3f(25.f, -125.f, 25.f);
	glVertex3f(25.f, -125.f, -25.f);
	glVertex3f(25.f, 125.f, -25.f);
	glVertex3f(25.f, 125.f, 25.f);
	glVertex3f(25.f, 125.f, -25.f);
	glVertex3f(-25.f, 125.f, -25.f);
	glVertex3f(-25.f, 125.f, 25.f);
	glVertex3f(-25.f, 125.f, -25.f);
	glVertex3f(-25.f, -125.f, -25.f);
	glEnd();

}

void Second_Rect()
{
	glColor3f(0.9f, 0.2f, 0.2f);
	glScalef(2.0f, 3.0f, 2.0f);
	glutSolidCube(30);

	glScalef(0.5f, 0.333f, 0.5f);
	glLineWidth(3);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-30.f, -45.f, 30.f);
	glVertex3f(30.f, -45.f, 30.f);
	glVertex3f(30.f, -45.f, -30.f);
	glVertex3f(-30.f, -45.f, -30.f);
	glVertex3f(-30.f, -45.f, 30.f);
	glVertex3f(-30.f, 45.f, 30.f);
	glVertex3f(-30.f, 45.f, -30.f);
	glVertex3f(-30.f, -45.f, -30.f);
	glVertex3f(-30.f, -45.f, 30.f);
	glVertex3f(-30.f, -45.f, -30.f);
	glVertex3f(30.f, -45.f, -30.f);
	glVertex3f(30.f, 45.f, -30.f);
	glVertex3f(-30.f, 45.f, -30.f);
	glVertex3f(-30.f, 45.f, 30.f);
	glVertex3f(30.f, 45.f, 30.f);
	glVertex3f(30.f, 45.f, -30.f);
	glEnd();
}

void Third_Rect()
{
	//glColor3f(0.2f, 0.9f, 0.2f);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[1]);
	// 자동 매핑 설정
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	// 구 매핑
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glutSolidCube(100);
	// 자동 매핑 해제
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	

	glLineWidth(3);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(50.f, -50.f, 50.f);
	glVertex3f(50.f, 50.f, 50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(50.f, 50.f, 50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(50.f, -50.f, -50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glEnd();
}

void fourth_Rect()
{
	//glColor3f(0.0f, 0.8f, 1.0f);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[1]);
	// 자동 매핑 설정
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	// 구 매핑
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glScalef(2.0f, 2.0f, 2.0f);
	glutSolidCube(50);
	// 자동 매핑 해제
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glScalef(0.5f, 0.5, 0.5f);
	glLineWidth(3);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(50.f, -50.f, 50.f);
	glVertex3f(50.f, 50.f, 50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(50.f, 50.f, 50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(50.f, -50.f, -50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glEnd();
}

void fifth_Rect()
{
	glColor3f(1.0f, 0.5f, 0.5f);
	glScalef(1.0f, 4.0f, 1.0f);
	glutSolidCube(50);
}

void sixth_Rect()
{
	glColor3f(1.0f, 0.5f, 0.5f);
	glScalef(5.0f, 1.0f, 1.0f);
	glutSolidCube(50);
}

void seventh_Rect()
{
	glColor3f(1.0f, 0.5f, 0.5f);
	glScalef(1.0f, 4.0f, 1.0f);
	glutSolidCube(50);
}

void Player()
{
	glColor3f(1.0f, 0.3f, 0.7f);
	glutSolidSphere(50, 25, 25);

	//sqrt(((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) + (z2 - z1)*(z2 - z1)));
	fPlayer_Center_X = fPlayer_X;
	fPlayer_Center_Y = -250.0f;
	fPlayer_Center_Z = fPlayer_Z;
	fPlayer_Radius = 50.f;
	cout << "1 : " << fPlayer_Center_X << ", " << fPlayer_Center_Y << ", " << fPlayer_Center_Z << endl;

	/*strCrash.fCenter_X[0] = -275.f;
	strCrash.fCenter_Y[0] = -250.f;
	strCrash.fCenter_Z[0] = 100.f;
	strCrash.fRadius[0] = 25.f;

	cout << "2 : " << strCrash.fCenter_X[0] << ", " << strCrash.fCenter_Y[0] << ", " << strCrash.fCenter_Z[0] << endl;
	fPlayer_to_Rect_Radius[0] = fPlayer_Radius + strCrash.fRadius[0];

	strCrash.fCrash[0] = sqrt(((strCrash.fCenter_X[0] - fPlayer_Center_X) * (strCrash.fCenter_X[0] - fPlayer_Center_X)
	+ (strCrash.fCenter_Y[0] - fPlayer_Center_Y)*(strCrash.fCenter_Y[0] - fPlayer_Center_Y)
	+ (strCrash.fCenter_Z[0] - fPlayer_Center_Z)*(strCrash.fCenter_Z[0] - fPlayer_Center_Z)));

	if (fPlayer_to_Rect_Radius[0] > strCrash.fCrash[0])
	cout << "충돌" << endl;*/

	if (fPlayer_Center_X < -175.f && fPlayer_Center_Z < 175.f && fPlayer_Center_Z > 25.f)
	{
		cout << "충돌" << endl;
		if (fPlayer_Center_Z <= 30.f)
			fPlayer_Z -= 5.f;
		else if (fPlayer_Center_Z >= 170.f)
			fPlayer_Z += 5.f;
		else if (fPlayer_Center_Z > 30.f && fPlayer_Center_Z < 170.f && fPlayer_Center_X <= -175.f)
			fPlayer_X += 5.f;

	}
	//300   30+50 -30-50
	else if (fPlayer_Center_X > 195.f && fPlayer_Center_Z < 380.f && fPlayer_Center_Z > 220.f)
	{
		cout << "충돌" << endl;
		if (fPlayer_Center_Z <= 225.f)
			fPlayer_Z -= 5.f;
		else if (fPlayer_Center_Z >= 375.f)
			fPlayer_Z += 5.f;
		else if (fPlayer_Center_Z > 225.f && fPlayer_Center_Z < 375.f && fPlayer_Center_X >= 195.f)
			fPlayer_X -= 5.f;

	}
	//150  50+50	-50-50
	else if (fPlayer_Center_X > 150.f && fPlayer_Center_Z < 250.f && fPlayer_Center_Z > 50.f)
	{
		cout << "충돌" << endl;
		if (fPlayer_Center_Z <= 55.f)
			fPlayer_Z -= 5.f;
		else if (fPlayer_Center_Z >= 245.f)
			fPlayer_Z += 5.f;
		else if (fPlayer_Center_Z > 55.f && fPlayer_Center_Z < 245.f && fPlayer_Center_X >= 150.f)
			fPlayer_X -= 5.f;

	}
	//200 50+50 -50-50
	else if (fPlayer_Center_X < -150.f && fPlayer_Center_Z < 300.f && fPlayer_Center_Z > 100.f)
	{
		cout << "충돌" << endl;
		if (fPlayer_Center_Z <= 105.f)
			fPlayer_Z -= 5.f;
		else if (fPlayer_Center_Z >= 295.f)
			fPlayer_Z += 5.f;
		else if (fPlayer_Center_Z > 105.f && fPlayer_Center_Z < 295.f && fPlayer_Center_X <= -155.f)
			fPlayer_X += 5.f;
	}

	else if (fPlayer_Center_X < -25.f && fPlayer_Center_X > -175.f && fPlayer_Center_Z < 75.f && fPlayer_Center_Z > -75.f)
	{
		cout << "충돌" << endl;
		if (fPlayer_Center_X >= -30.f && fPlayer_Center_Z <= 75.f && fPlayer_Center_Z >= -75.f)
			fPlayer_X += 5.f;
		else if (fPlayer_Center_X <= -170.f && fPlayer_Center_Z <= 75.f && fPlayer_Center_Z >= -75.f)
			fPlayer_X -= 5.f;
		else if (fPlayer_Center_X < -30.f && fPlayer_Center_X > -170.f && fPlayer_Center_Z <= 75.f && fPlayer_Center_Z >= 70.f)
			fPlayer_Z += 5.f;
		else if (fPlayer_Center_X < -30.f && fPlayer_Center_X > -170.f && fPlayer_Center_Z >= -75.f && fPlayer_Center_Z <= -70.f)
			fPlayer_Z -= 5.f;
	}

	else if (fPlayer_Center_X > 25.f && fPlayer_Center_X < 175.f && fPlayer_Center_Z < 75.f && fPlayer_Center_Z > -75.f)
	{
		cout << "충돌" << endl;
		if (fPlayer_Center_X >= 30.f && fPlayer_Center_X <= 35.f && fPlayer_Center_Z <= 75.f && fPlayer_Center_Z >= -75.f)
			fPlayer_X -= 5.f;
		else if (fPlayer_Center_X <= 170.f && fPlayer_Center_X >= 165.f && fPlayer_Center_Z <= 75.f && fPlayer_Center_Z >= -75.f)
			fPlayer_X += 5.f;
		else if (fPlayer_Center_X > 30.f && fPlayer_Center_X < 170.f && fPlayer_Center_Z <= 75.f && fPlayer_Center_Z >= 70.f)
			fPlayer_Z += 5.f;
		else if (fPlayer_Center_X > 30.f && fPlayer_Center_X < 170.f && fPlayer_Center_Z >= -75.f && fPlayer_Center_Z <= -70.f)
			fPlayer_Z -= 5.f;
	}

	else if (fPlayer_X > -75.f && fPlayer_X < 75.f && fPlayer_Z < 10.f && fPlayer_Z > -10.f)
	{
		fDiffuse_Light = randomDouble();
		fDiffuse_Light2 = randomDouble();
		fDiffuse_Light3 = randomDouble();
	}

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

	pBytes[0] = LoadDIBitmap("3-34 바닥.bmp", &info);
	pBytes[1] = LoadDIBitmap("3-34 꽃.bmp", &info);
	pBytes[2] = LoadDIBitmap("3-34 하늘.bmp", &info);
	pBytes[3] = LoadDIBitmap("3-34 태극기.bmp", &info);

}

void RoundBox()
{
	//glEnable(GL_CULL_FACE);
	//앞쪽 벽
	//glColor3f(0.3f, 0.3f, 1.0f);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 426, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[2]);
	glBegin(GL_QUADS);
	//glFrontFace(GL_CW);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-300.f, 0.0f, 500.f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-300.f, 600.0f, 500.f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(300.f, 600.0f, 500.f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(300.f, 0.0f, 500.f);
	glEnd();



	//오른쪽 벽
	//glColor3f(1.0f, 1.0f, 0.0f);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 341, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(300.f, 0.0f, -100.f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(300.f, 0.0f, 500.f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(300.f, 600.f, 500.f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(300.f, 600.f, -100.f);
	glEnd();


	//뒷쪽 벽
	//glColor3f(1.0f, 0.0f, 1.0f);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 426, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(300.f, 0.0f, -100.f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(300.f, 600.0f, -100.f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-300.f, 600.0f, -100.f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-300.f, 0.0f, -100.f);
	glEnd();

	//왼쪽 벽
	//glColor3f(0.0f, 1.0f, 1.0f);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 341, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-300.f, 0.0f, -100.f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-300.f, 600.0f, -100.f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-300.f, 600.0f, 500.f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-300.f, 0.0f, 500.f);
	glEnd();




}
